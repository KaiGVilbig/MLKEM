#include "ntt.h"
#include <cmath>
#include <stdexcept>

// Overflow safe multiply mod q
uint16_t modMul(uint16_t a, uint16_t b) {
    return static_cast<uint16_t>((static_cast<uint32_t>(a) * b) % q);
}

// Underflow safe subtraction mod q
uint16_t modSub(uint16_t a, uint16_t b) {
    return (a >= b) ? a - b : a + q - b;
}


// NTT using Cooley-Tukey Butterfly Operation
std::vector<uint16_t> NTT(std::vector<uint16_t> f) {
    std::vector<uint16_t> fhat = f;
    uint8_t i = 1;

    for (int len = 128; len >= 2; len /= 2) {
        for (int start = 0; start < 256; start = start + 2 * len) {
            uint16_t zeta = Zeta[i];
            i++;
            for (int j = start; j < start + len; j++) {
                uint16_t t = modMul(zeta, fhat[j + len]); // zeta * fhat[j + len] % q;
                fhat[j + len] = modSub(fhat[j], t) % q;
                fhat[j] = (fhat[j] + t) % q;
            }
        }
    }

    return fhat;
}

// Inverse NTT to return to the coefficient domain
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
        f[j] = modMul(f[j], 3303); // f[j] * 3303 % q;
    }

    return f;
}

std::vector<uint16_t> multiplyNTT(std::vector<uint16_t fhat, std::vector<uint16_t> ghat>) {

}

std::vector<uint16_t> BaseCaseMultiply(uint16_t a0, uint16_t a1, uint16_t b0, uint16_t b1, int16_t z2) {

}