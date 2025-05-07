#include "ntt.h"
#include <cmath>
#include <stdexcept>

uint16_t modMul(uint16_t a, uint16_t b) {
    return static_cast<uint16_t>((static_cast<uint32_t>(a) * b) % q);
}

uint16_t modMulSigned(uint16_t a, int16_t b) {
    // Promote both to int32_t to avoid overflow
    int32_t result = static_cast<int32_t>(a) * static_cast<int32_t>(b);

    // Take mod q, safely into [0, q-1]
    result %= q;
    if (result < 0) result += q;

    return static_cast<uint16_t>(result);
}

uint16_t modAdd(uint16_t a, uint16_t b) {
    uint16_t sum = a + b;
    return (sum >= q) ? sum - q : sum;
}

uint16_t modSub(uint16_t a, uint16_t b) {
    return (a >= b) ? a - b : a + q - b;
}

std::vector<uint16_t> NTT(std::vector<uint16_t> f) {
    std::vector<uint16_t> fhat = f;
    uint8_t i = 1;

    for (int len = 128; len >= 2; len /= 2) {
        for (int start = 0; start < 256; start = start + 2 * len) {
            uint16_t zeta = Zeta[i];
            i++;
            for (int j = start; j < start + len; j++) {
                uint16_t t = modMul(zeta, fhat[j + len]); // zeta * fhat[j + len] % q;
                fhat[j + len] = modSub(fhat[j], t);
                fhat[j] = (fhat[j] + t) % q;
            }
        }
    }

    return fhat;
}

std::vector<uint16_t> inverseNTT(std::vector<uint16_t> fhat) {
    std::vector<uint16_t> f = fhat;
    uint8_t i = 127;

    for (int len = 2; len <= 128; len *= 2) {
        for (int start = 0; start < 256; start = start + 2 * len) {
            uint16_t zeta = Zeta[i];
            i--;
            for (int j = start; j < start + len; j++) {
                uint16_t t = f[j];
                f[j] = (t + f[j + len]) % q;
                f[j + len] = modMul(zeta, modSub(f[j + len], t)); // zeta * (f[j + len] - t) % q;
            }
        }
    }

    for (int j = 0; j < f.size(); j++) {
        f[j] = modMul(f[j], qInvN); // f[j] * 3303 % q;
    }

    return f;
}

std::vector<uint16_t> multiplyNTT(std::vector<uint16_t> fhat, std::vector<uint16_t> ghat) {
    std::vector<uint16_t> hhat(256, 0);
    for (int i = 0; i < 128; i++) {
        std::vector<uint16_t> c = BaseCaseMultiply(fhat[2 * i], fhat[2 * i + 1], ghat[2 * i], ghat[2 * i + 1], Zeta2[i]);
        hhat[2 * i] = c[0];
        hhat[2 * i + 1] = c[1];
    }
    return hhat;
}

std::vector<uint16_t> BaseCaseMultiply(uint16_t a0, uint16_t a1, uint16_t b0, uint16_t b1, int16_t z2) {
    uint32_t t1 = modMul(a0, b0);
    uint32_t t2 = modMulSigned(modMul(a1, b1), z2);
    uint16_t c0 = modAdd(t1, t2);

    uint16_t c1 = modAdd(modMul(a0, b1), modMul(a1, b0));

    return {c0, c1};
}