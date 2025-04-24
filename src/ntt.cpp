#include "ntt.h"
#include <cmath>
#include <stdexcept>

#define Q 3329  // Example modulus used in Kyber/ML-KEM
#define N 256   // Typical polynomial degree in ML-KEM

uint16_t modAdd(uint16_t a, uint16_t b) {
    uint16_t res = a + b;
    return (res >= q) ? res - q : res;
}

uint16_t modSub(uint16_t a, uint16_t b) {
    return (a >= b) ? a - b : a + q - b;
}

uint16_t modMul(uint16_t a, uint16_t b) {
    return static_cast<uint32_t>(a) * b % q;
}

// NTT using Cooley-Tukey Butterfly Operation
std::vector<uint16_t> NTT(std::vector<uint16_t> input) {
    std::vector<uint16_t> a = input;
    size_t i = 1;

    for (size_t len = 128; len >= 2; len >>= 1) {
        for (size_t start = 0; start < 256; start += 2 * len) {
            uint16_t zeta = Zeta[i - 1];
            i++;
            for (size_t j = start; j < start + len; j++) {
                uint16_t t = modMul(zeta, a[j + len]);
                a[j + len] = modSub(a[j], t);
                a[j] = modAdd(a[j], t);
            }
        }
    }

    return a;
}

// Inverse NTT to return to the coefficient domain
std::vector<uint16_t> inverseNTT(std::vector<uint16_t> input) {
    std::vector<uint16_t> a = input;
    size_t i = 127;

    for (size_t len = 2; len <= 128; len <<= 1) {
        for (size_t start = 0; start < 256; start += 2 * len) {
            uint16_t zeta = Zeta[i - 1];
            i--;
            for (size_t j = start; j < start + len; j++) {
                uint16_t t = a[j];
                a[j] = modAdd(t, a[j + len]);
                a[j + len] = modMul(zeta, modSub(t, a[j + len]));
            }
        }
    }

    for (size_t j = 0; j < 256; j++) {
        a[j] = modMul(a[j], qInvN);
    }

    return a;
}
