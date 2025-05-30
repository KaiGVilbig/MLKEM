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
    std::pair<std::vector<uint8_t>, std::vector<uint8_t>> expanded = G(dConcat);

    std::vector<uint8_t> rho = expanded.first;
    std::vector<uint8_t> sigma = expanded.second;

    int N = 0;

    std::vector<std::vector<uint16_t>> Ahat(k * k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            std::vector<uint8_t> seed = rho;
            seed.push_back(static_cast<uint8_t>(j));
            seed.push_back(static_cast<uint8_t>(i));
            Ahat[i * k + j] = SampleNTT(seed);
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

    std::vector<std::vector<uint16_t>> tHat(k, std::vector<uint16_t>(256, 0));
    for (size_t i = 0; i < k; ++i) {
        for (size_t j = 0; j < k; ++j) {
            std::vector<uint16_t> prod = multiplyNTT(Ahat[i * k + j], s[j]);

            for (size_t idx = 0; idx < 256; ++idx) {
                tHat[i][idx] = modAdd(tHat[i][idx], prod[idx]);
            }
        }
        for (size_t idx = 0; idx < 256; ++idx) {
            tHat[i][idx] = modAdd(tHat[i][idx], e[i][idx]);
        }
    }

    std::vector<uint8_t> ekPKE;
    for (int i = 0; i < k; ++i) {
        std::vector<uint8_t> encoded = byteEncode(tHat[i], 12);
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

    size_t tHatBytes = (12 * 256 + 7) / 8;
    std::vector<std::vector<uint16_t>> tHat(k);
    for (int i = 0; i < k; ++i) {
        std::vector<uint8_t> enc(ek.begin() + i * tHatBytes, ek.begin() + (i + 1) * tHatBytes);
        tHat[i] = byteDecode(enc, 12);
    }
    std::vector<uint8_t> rho(ek.end() - 32, ek.end());

    std::vector<std::vector<uint16_t>> Ahat(k * k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            std::vector<uint8_t> seed = rho;
            seed.push_back(static_cast<uint8_t>(j));
            seed.push_back(static_cast<uint8_t>(i));
            Ahat[i * k + j] = SampleNTT(seed);
        }
    }

    std::vector<std::vector<uint16_t>> y(k), e1(k);
    std::vector<uint16_t> e2;
    for (int i = 0; i < k; i++) {
        y[i] = samplePolyCBD(prfEta(n, r, N), n); 
        N++;
    }
    for (int i = 0; i < k; i++) {
        e1[i] = samplePolyCBD(prfEta(n2, r, N), n2); 
        N++;
    }
    e2 = samplePolyCBD(prfEta(n2, r, N), n2); N++;

    for (int i = 0; i < k; ++i) y[i] = NTT(y[i]);

    std::vector<std::vector<uint16_t>> uHat(k, std::vector<uint16_t>(256, 0));

    for (int i = 0; i < k; ++i) {
        std::vector<uint16_t> acc(256, 0);

        for (int j = 0; j < k; ++j) {
            std::vector<uint16_t> prod = multiplyNTT(Ahat[j * k + i], y[j]);
            for (int l = 0; l < 256; ++l) {
                acc[l] = (acc[l] + prod[l]) % q;
            }
        }

        // Inverse NTT
        std::vector<uint16_t> u_i = inverseNTT(acc);

        for (int l = 0; l < 256; ++l) {
            uHat[i][l] = (u_i[l] + e1[i][l]) % q;
        }
    }

    std::vector<uint16_t> mu = Decompress(byteDecode(m, 1), 1);  // returns 256 0/1 values

    std::vector<uint16_t> acc(256, 0);

    for (int i = 0; i < k; ++i) {
        std::vector<uint16_t> prod = multiplyNTT(tHat[i], y[i]);
        for (int j = 0; j < 256; ++j) {
            acc[j] = (acc[j] + prod[j]) % q;
        }
    }

    std::vector<uint16_t> v = inverseNTT(acc);

    // Add e2 and mu
    for (int j = 0; j < 256; ++j) {
        v[j] = (v[j] + e2[j] + mu[j]) % q;
    }

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

std::vector<uint8_t> kpkeDecrypt(std::vector<uint8_t> dk, std::vector<uint8_t> c, Variants variant) {
    int k, n, du, dv;
    int n2 = 2;

    std::tie(k, n, du, dv) = getVariant(variant);

    size_t c1_bytes = ((du * 256 + 7) / 8) * k;
    size_t c2_bytes = (dv * 256 + 7) / 8;


    std::vector<std::vector<uint16_t>> u(k);
    for (int i = 0; i < k; ++i) {
        size_t offset = i * ((du * 256 + 7) / 8);
        std::vector<uint8_t> part(c.begin() + offset, c.begin() + offset + ((du * 256 + 7) / 8));
        auto decoded = byteDecode(part, du);
        u[i] = Decompress(decoded, du);
    }

    std::vector<uint8_t> c2(c.begin() + c1_bytes, c.end());
    auto decodedC2 = byteDecode(c2, dv);
    std::vector<uint16_t> v = Decompress(decodedC2, dv);

    std::vector<std::vector<uint16_t>> s(k);
    size_t bytesPerPoly = (12 * 256 + 7) / 8;
    for (int i = 0; i < k; ++i) {
        std::vector<uint8_t> enc(dk.begin() + i * bytesPerPoly, dk.begin() + (i + 1) * bytesPerPoly);
        s[i] = byteDecode(enc, 12);
    }

    std::vector<uint16_t> w(256, 0);
    for (int i = 0; i < k; ++i) {
        auto u_ntt = NTT(u[i]);
        auto product = multiplyNTT(s[i], u_ntt);
        for (int j = 0; j < 256; ++j) {
            w[j] = (w[j] + product[j]) % q;
        }
    }

    w = inverseNTT(w);

    for (int i = 0; i < 256; ++i) {
        w[i] = modSub(v[i], w[i]);
    }

    auto compressed = Compress(w, 1);

    return byteEncode(compressed, 1);
}