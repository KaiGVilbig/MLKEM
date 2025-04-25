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
	std::pair<std::vector<uint8_t>, std::vector<uint8_t>> pa = G(d);
	int N = 0, k, n1, du, dv;

	std::tie(k, n1, du, dv) = getVariant(variant);
	std::vector<std::vector<uint16_t>> Ahat;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			Ahat.push_back(SampleNTT(pa.first));
		}
	}

	std::vector<std::vector<uint16_t>> s;
	for (int i = 0; i < k; i++) {
		s.push_back(samplePolyCBD(J(pa.second, N)));
	}
}

void kpkeEncrypt() {
	std::cout << "[INFO] kpkeEncode() called\n";
}

void kpkeDecrypt() {
	std::cout << "[INFO] kpkeDecode() called\n";
}