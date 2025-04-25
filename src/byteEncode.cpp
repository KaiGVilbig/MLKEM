#include "byteEncode.h"
#include <iostream>

std::vector<uint8_t> byteEncode(const std::vector<uint8_t> F, uint8_t d) {
    std::vector<uint8_t> b(256 * d, 0);
    for (int i = 0; i < 256; i++) {
        uint16_t a = F[i];
        for (int j = 0; j < d; j++) {
            b[i * d + j] = a & 1;
            a >>= 1;
        }
    }
    return bitsToBytes(b);
}

std::vector<uint8_t> byteDecode(const std::vector<uint8_t> B, uint8_t d) {
    std::vector<uint8_t> F(256, 0);
    std::vector<uint8_t> b = bytesToBits(B);
    uint16_t m = (d < 12) ? (1 << d) : 3329;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < d; j++) {
            F[i] |= (b[i * d + j] << j);
        }
        F[i] %= m;
    }
    return F;
}

std::vector<uint8_t> bitsToBytes(std::vector<uint8_t> b) {
    size_t ell = b.size() / 8;
    std::vector<uint8_t> B(ell, 0);

    for (size_t i = 0; i < b.size(); i++) {
        B[i / 8] += b[i] << (i % 8);
    }

    return B;
}

std::vector<uint8_t> bytesToBits(std::vector<uint8_t> B) {
    size_t ell = B.size();
    std::vector<uint8_t> b(ell * 8, 0);
    std::vector<uint8_t> C = B; // Copy B into C

    for (size_t i = 0; i < ell; i++) {
        for (size_t j = 0; j < 8; j++) {
            b[8 * i + j] = C[i] % 2;
            C[i] = C[i] / 2;
        }
    }

    return b;
}

uint8_t bitRev(uint8_t ini) {
    uint8_t reversedByte = 0;
    for (int i = 0; i < 8; ++i) {
        if ((ini >> i) & 1) {
            reversedByte |= (1 << (7 - i));
        }
    }
    return reversedByte / 2;
}