#include "kpke.h"
#include <iostream>

std::tuple<int, int, int, int> getVariant(Variants variant) {
	int k, n1, du, dv;
	switch (variant) {
		case Variants::MLKEM512:
			k = 2, n1 = 3, du = 10, dv = 4;
			break;
		case Variants::MLKEM768:
			k = 3, n1 = 2, du = 10, dv = 4;
			break;
		case Variants::MLKEM1024:
			k = 4, n1 = 2, du = 11, dv = 5;
            break;
		default:
			k = 2, n1 = 3, du = 10, dv = 4;
			break;
	}
	return {k, n1, du, dv};
}

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> kpkeKeyGen(std::vector<uint8_t> d, Variants variant) {
    int k, n, du, dv;
    
    std::tie(k, n, du, dv) = getVariant(variant);

    std::vector<uint8_t> dConcat = d;
    dConcat.push_back(static_cast<uint8_t>(k));
    std::pair<std::vector<uint8_t>, std::vector<uint8_t>> expanded = G(dConcat);

    std::vector<uint8_t> rho = expanded.first;
    std::vector<uint8_t> sigma = expanded.second;

    int N = 0;

    std::vector<std::vector<uint16_t>> A_hat(k * k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            std::vector<uint8_t> seed = rho;
            seed.push_back(static_cast<uint8_t>(j));
            seed.push_back(static_cast<uint8_t>(i));
            A_hat[i * k + j] = SampleNTT(seed);
        }
    }

    std::vector<std::vector<uint16_t>> s(k);
    for (int i = 0; i < k; ++i) {
        s[i] = samplePolyCBD(prfEta(n, sigma, N), n);
        N++;
    }

    std::vector<std::vector<uint16_t>> e(k);
    for (int i = 0; i < k; ++i) {
        e[i] = samplePolyCBD(prfEta(n, sigma, N), n);
        N++;
    }

    for (int i = 0; i < k; ++i) {
        s[i] = NTT(s[i]);
        e[i] = NTT(e[i]);
    }

    std::vector<std::vector<uint16_t>> t_hat(k, std::vector<uint16_t>(256, 0));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            for (size_t coeff = 0; coeff < 256; ++coeff) {
                t_hat[i][coeff] = (t_hat[i][coeff] + static_cast<uint32_t>(A_hat[i * k + j][coeff]) * s[j][coeff]) % q;
            }
        }
        for (size_t coeff = 0; coeff < 256; ++coeff) {
            t_hat[i][coeff] = (t_hat[i][coeff] + e[i][coeff]) % q;
        }
    }

    std::vector<uint8_t> ekPKE;
    for (int i = 0; i < k; ++i) {
        std::vector<uint8_t> encoded = byteEncode(t_hat[i], 12);
        ekPKE.insert(ekPKE.end(), encoded.begin(), encoded.end());
    }
    ekPKE.insert(ekPKE.end(), rho.begin(), rho.end());

    std::vector<uint8_t> dkPKE;
    for (int i = 0; i < k; ++i) {
        std::vector<uint8_t> encoded = byteEncode(s[i], 12);
        dkPKE.insert(dkPKE.end(), encoded.begin(), encoded.end());
    }

    return { ekPKE, dkPKE };
}

std::vector<uint8_t> kpkeEncrypt(std::vector<uint8_t> ek, std::vector<uint8_t> m, std::vector<uint8_t> r, Variants variant) {
    int k, n, du, dv;
    int n2 = 2;

    std::tie(k, n, du, dv) = getVariant(variant);

    int N = 0;

    // Step 1–2: Decode t? and extract ?
    size_t tHatBytes = (12 * 256 + 7) / 8;
    std::vector<std::vector<uint16_t>> tHat(k);
    for (int i = 0; i < k; ++i) {
        std::vector<uint8_t> enc(ek.begin() + i * tHatBytes, ek.begin() + (i + 1) * tHatBytes);
        tHat[i] = byteDecode(enc, 12);
    }
    std::vector<uint8_t> rho(ek.end() - 32, ek.end());

    // Step 3–7: Regenerate A_hat
    std::vector<std::vector<uint16_t>> Ahat(k * k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            std::vector<uint8_t> seed = rho;
            seed.push_back(static_cast<uint8_t>(j));
            seed.push_back(static_cast<uint8_t>(i));
            Ahat[i * k + j] = SampleNTT(seed);
        }
    }

    // Step 8–14: Generate y, e1, e2 using PRF
    std::vector<std::vector<uint16_t>> y(k), e1(k);
    std::vector<uint16_t> e2;
    for (int i = 0; i < k; ++i) {
        y[i] = samplePolyCBD(prfEta(n, r, N), n); N++;
    }
    for (int i = 0; i < k; ++i) {
        e1[i] = samplePolyCBD(prfEta(n2, r, N), n2); N++;
    }
    {
        std::vector<uint8_t> prf = r;
        prf.push_back((N >> 8) & 0xFF); prf.push_back(N & 0xFF);
        e2 = samplePolyCBD(prfEta(n2, r, N), n2); N++;
    }

    // Step 15–17: NTT(y), compute u? = A?·? + ê?
    for (int i = 0; i < k; ++i) y[i] = NTT(y[i]);

    std::vector<std::vector<uint16_t>> uHat(k, std::vector<uint16_t>(256, 0));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            for (int l = 0; l < 256; ++l) {
                uHat[i][l] = (uHat[i][l] + Ahat[i * k + j][l] * y[j][l]) % q;
            }
        }
        for (int l = 0; l < 256; ++l) {
            uHat[i][l] = (uHat[i][l] + e1[i][l]) % q;
        }
    }

    // Step 18: compute v? = t??·?
    std::vector<uint16_t> vHat(256, 0);
    for (int i = 0; i < k; ++i) {
        for (int l = 0; l < 256; ++l) {
            vHat[l] = (vHat[l] + tHat[i][l] * y[i][l]) % q;
        }
    }

    // Step 19: Decompress message m
    std::vector<uint8_t> messageBits = bytesToBits(m);
    std::vector<uint16_t> mu(256, 0);
    for (int i = 0; i < 256 && i < messageBits.size(); ++i) {
        mu[i] = messageBits[i] * (q / 2);
    }

    // Step 20: compute v = NTT?¹(v?) + ? + e?
    std::vector<uint16_t> v = inverseNTT(vHat);
    for (int i = 0; i < 256; ++i) {
        v[i] = (v[i] + mu[i] + e2[i]) % q;
    }

    // Step 21–23: Encode c? and c?
    std::vector<uint8_t> ciphertext;
    for (int i = 0; i < k; ++i) {
        auto compressed = Compress(uHat[i], du);
        auto encoded = byteEncode(compressed, du);
        ciphertext.insert(ciphertext.end(), encoded.begin(), encoded.end());
    }

    auto compressedV = Compress(v, dv);
    auto encodedV = byteEncode(compressedV, dv);
    ciphertext.insert(ciphertext.end(), encodedV.begin(), encodedV.end());

    return ciphertext;
}

void kpkeDecrypt() {
	std::cout << "[INFO] kpkeDecode() called\n";
}