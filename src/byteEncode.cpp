#include "byteEncode.h"
#include <iostream>

std::vector<uint8_t> byteEncode(std::vector<uint16_t> F, uint8_t d) {
    size_t n = F.size(); // usually 256
    uint16_t m = (d < 12) ? (1 << d) : q;

    std::vector<uint8_t> bits(n * d, 0);

    for (size_t i = 0; i < n; ++i) {
        uint16_t a = F[i] % m;
        for (int j = 0; j < d; ++j) {
            bits[i * d + j] = a & 1;
            a >>= 1;
        }
    }

    return bitsToBytes(bits);
}

std::vector<uint16_t> byteDecode(std::vector<uint8_t> B, uint8_t d) {
    std::vector<uint8_t> b = bytesToBits(B);
    std::vector<uint16_t> F(256, 0);

    uint16_t m = (d < 12) ? (1 << d) : q;

    for (int i = 0; i < 256; ++i) {
        uint16_t value = 0;
        for (int j = 0; j < d; ++j) {
            value += static_cast<uint16_t>(b[i * d + j]) << j;
        }
        F[i] = value % m;
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

std::vector<uint16_t> Compress(std::vector<uint16_t> input, int d) {
    std::vector<uint16_t> output(input.size());
    uint16_t scale = 1 << d; // 2^d
    for (size_t i = 0; i < input.size(); ++i) {
        uint32_t temp = static_cast<uint32_t>(input[i]) * scale + q / 2;
        output[i] = static_cast<uint16_t>((temp / q) % scale);  // scale = 1 << d
    }
    return output;
}

std::vector<uint16_t> Decompress(std::vector<uint16_t> input, int d) {
    std::vector<uint16_t> output(input.size());
    uint32_t rounding = 1 << (d - 1);  // 2^{d-1}
    uint32_t scale = 1 << d;           // 2^d

    for (size_t i = 0; i < input.size(); ++i) {
        uint32_t val = static_cast<uint32_t>(input[i]) * q + rounding;
        output[i] = static_cast<uint16_t>(val / scale);
    }

    return output;
}