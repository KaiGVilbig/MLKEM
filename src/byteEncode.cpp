#include "byteEncode.h"
#include <iostream>

void byteEncode() {
    std::cout << "[INFO] ByteEncode() called\n";
}

void byteDecode() {
    std::cout << "[INFO] ByteDecode() called\n";
}

uint64_t bytesToBits(const std::vector<uint8_t> bytes, size_t bitLength) {
    uint64_t bits = 0;
    size_t byteLength = (bitLength + 7) / 8;

    for (size_t i = 0; i < bitLength; i++) {
        if (bytes[i / 8] & (1 << (i % 8))) {
            bits |= (1ULL << i);
        }
    }
    return bits;
}

std::vector<uint8_t> bitsToBytes(uint64_t bits, size_t bitLength) {
    size_t byteLength = (bitLength + 7) / 8; // Round up to nearest byte
    std::vector<uint8_t> bytes(byteLength, 0);

    for (size_t i = 0; i < bitLength; i++) {
        if (bits & (1ULL << i)) {
            bytes[i / 8] |= (1 << (i % 8));
        }
    }
    return bytes;
}