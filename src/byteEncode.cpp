#include "byteEncode.h"
#include <iostream>

std::vector<uint8_t> byteEncode(std::vector<uint16_t> input, size_t d) {
    if (d < 1 || d > 12) {
        throw std::invalid_argument("d must be between 1 and 12");
    }

    size_t bitLength = input.size() * d;
    size_t byteLength = (bitLength + 7) / 8;
    std::vector<uint8_t> output(byteLength, 0);

    size_t bitPos = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        uint16_t value = input[i];
        for (size_t j = 0; j < d; ++j) {
            size_t byteIndex = bitPos / 8;
            size_t bitOffset = bitPos % 8;
            output[byteIndex] |= ((value >> j) & 1) << bitOffset;
            bitPos++;
        }
    }
    return output;
}

std::vector<uint16_t> byteDecode(std::vector<uint8_t> input, size_t d, size_t numElements) {
    if (d < 1 || d > 12) {
        throw std::invalid_argument("d must be between 1 and 12");
    }

    std::vector<uint16_t> output(numElements, 0);
    size_t bitPos = 0;
    for (size_t i = 0; i < numElements; ++i) {
        uint16_t value = 0;
        for (size_t j = 0; j < d; ++j) {
            size_t byteIndex = bitPos / 8;
            size_t bitOffset = bitPos % 8;
            value |= ((input[byteIndex] >> bitOffset) & 1) << j;
            bitPos++;
        }
        output[i] = value;
    }
    return output;
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