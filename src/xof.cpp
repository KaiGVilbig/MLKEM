#include "xof.h"
#include <stdexcept>
#include <cstring>
#include <iostream>

XOF::XOF() {
    ctx = EVP_MD_CTX_new();
    if (!ctx) {
        throw std::runtime_error("Failed to initialize XOF context.");
    }
}

XOF::~XOF() {
    if (ctx) {
        EVP_MD_CTX_free(ctx);
    }
}

void XOF::init() {
    if (EVP_DigestInit_ex(ctx, EVP_shake128(), nullptr) != 1) {
        throw std::runtime_error("Failed to initialize SHAKE128.");
    }
}

void XOF::absorb(const std::vector<uint8_t> input) {
    if (EVP_DigestUpdate(ctx, input.data(), input.size()) != 1) {
        throw std::runtime_error("Failed to absorb input into SHAKE128.");
    }
}

std::vector<uint8_t> XOF::squeeze(size_t n) {
    std::vector<uint8_t> output(n);
    if (EVP_DigestFinalXOF(ctx, output.data(), n) != 1) {
        throw std::runtime_error("Failed to squeeze output from SHAKE128.");
    }
    return output;
}
