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
        //std::vector<uint8_t> prfInput = sigma;
        //prfInput.push_back(static_cast<uint8_t>((N >> 8) & 0xFF));
        //prfInput.push_back(static_cast<uint8_t>(N & 0xFF));
        //s[i] = samplePolyCBD(prfInput, n);
        s[i] = samplePolyCBD(prfEta(n, sigma, N), n);
        N++;
    }

    std::vector<std::vector<uint16_t>> e(k);
    for (int i = 0; i < k; ++i) {
        //std::vector<uint8_t> prfInput = sigma;
        //prfInput.push_back(static_cast<uint8_t>((N >> 8) & 0xFF));
        //prfInput.push_back(static_cast<uint8_t>(N & 0xFF));
        //e[i] = samplePolyCBD(prfInput, n);
        e[i] = samplePolyCBD(prfEta(n, sigma, N), n);

        N++;
    }

    for (int i = 0; i < k; ++i) {
        s[i] = NTT(s[i]);
    }

    for (int i = 0; i < k; ++i) {
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
        std::vector<uint8_t> encoded = byteEncode(t_hat[i], du);
        ekPKE.insert(ekPKE.end(), encoded.begin(), encoded.end());
    }
    ekPKE.insert(ekPKE.end(), rho.begin(), rho.end());

    std::vector<uint8_t> dkPKE;
    for (int i = 0; i < k; ++i) {
        std::vector<uint8_t> encoded = byteEncode(s[i], dv);
        dkPKE.insert(dkPKE.end(), encoded.begin(), encoded.end());
    }

    return { ekPKE, dkPKE };
}

void kpkeEncrypt() {
	std::cout << "[INFO] kpkeEncode() called\n";
}

void kpkeDecrypt() {
	std::cout << "[INFO] kpkeDecode() called\n";
}