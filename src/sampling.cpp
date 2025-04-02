#include "sampling.h"
#include "xof.h"
#include <stdexcept>
#include <iostream>

std::vector<uint16_t> SampleNTT(std::vector<uint8_t> B) {
    if (B.size() != 34) {
        throw std::invalid_argument("SampleNTT requires a 34-byte input.");
    }

    XOF xof;  // Create an XOF instance
    xof.init();       // Initialize SHAKE256
    xof.absorb(B);    // Absorb input B

    std::vector<uint16_t> a_hat(256);
    uint8_t j = 0;

    while (j < 256) {
        xof.init();
        std::vector<uint8_t> C = xof.squeeze(3); // Get 3 random bytes

        uint16_t d1 = static_cast<uint16_t>(C[0]) + 256 * (C[1] % 16);
        uint16_t d2 = static_cast<uint16_t>(C[1] / 16) + 16 * C[2];

        if (d1 < 4096) { // q = 4096 in ML-KEM
            a_hat[j] = d1;
            j++;
        }
        if (d2 < 4096 && j < 256) {
            a_hat[j] = d2;
            j++;
        }
    }

    return a_hat; // XOF is automatically destroyed when going out of scope
}


void samplePolyCBD() {
    std::cout << "[INFO] SamplePolyCBD() called\n";
}