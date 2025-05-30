﻿#include "sampling.h"
#include "xof.h"
#include "byteEncode.h"
#include "constants.h"
#include <stdexcept>
#include <iostream>

std::vector<uint16_t> SampleNTT(std::vector<uint8_t> B) {

    XOF xof;
    xof.init();
    xof.absorb(B);

    // Instead of squeezing repeatedly, grab enough output in one go.
    // Assume worst case: all rejections. We need ~3 bytes per sample, so go long.
    std::vector<uint8_t> xofBytes = xof.squeeze(3 * 512); // Grab extra just in case

    std::vector<uint16_t> aHat(256);
    uint16_t j = 0;
    size_t i = 0;

    while (j < 256 && i + 3 <= xofBytes.size()) {
        uint8_t C0 = xofBytes[i];
        uint8_t C1 = xofBytes[i + 1];
        uint8_t C2 = xofBytes[i + 2];
        i += 3;

        uint16_t d1 = C0 + 256 * (C1 % 16);
        uint16_t d2 = (C1 / 16) + 16 * C2;

        if (d1 < q) {
            aHat[j++] = d1;
        }
        if (j < 256 && d2 < q) {
            aHat[j++] = d2;
        }
    }

    if (j != 256) {
        throw std::runtime_error("SampleNTT: Not enough output from XOF to complete sampling.");
    }

    return aHat;
}

std::vector<uint16_t> samplePolyCBD(std::vector<uint8_t>B, uint8_t n) {
    std::vector<uint8_t> b = bytesToBits(B);

    // Validate input size
    if (n != 2 && n != 3) {
        throw std::invalid_argument("samplePolyCBD only supports n = 2 or 3");
    }
    if (B.size() != 64 * n) {
        throw std::invalid_argument("Input B must be 64*n bytes.");
    }

    std::vector<uint16_t> f(256);

    for (size_t i = 0; i < 256; i++) {
        uint8_t x = 0;
        uint8_t y = 0;

        for (uint8_t j = 0; j < n; j++) {
            x += b[2 * n * i + j];
        }

        for (uint8_t j = 0; j < n; j++) {
            y += b[2 * n * i + n + j];
        }

        int16_t diff = static_cast<int16_t>(x) - static_cast<int16_t>(y);
        f[i] = static_cast<uint16_t>((diff + q) % q);
    }

    return f;
}