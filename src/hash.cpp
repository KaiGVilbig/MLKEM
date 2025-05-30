#include "hash.h"
#include <iostream>

std::vector<uint8_t> prfEta(int eta, std::vector<uint8_t> s, uint8_t b) {

    // Concatenate s || b
    s.push_back(b); // Now s is 33 bytes
    const size_t outputLen = 64 * eta;
    std::vector<uint8_t> output(outputLen);

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    if (EVP_DigestInit_ex(ctx, EVP_shake256(), nullptr) != 1 ||
        EVP_DigestUpdate(ctx, s.data(), s.size()) != 1 ||
        EVP_DigestFinalXOF(ctx, output.data(), outputLen) != 1) {
        EVP_MD_CTX_free(ctx);
    }

    EVP_MD_CTX_free(ctx);
    return output;
}

std::vector<uint8_t> H(std::vector<uint8_t> input) {
    std::vector<uint8_t> output(32);
    EVP_Digest(input.data(), input.size(), output.data(), nullptr, EVP_sha3_256(), nullptr);
    return output;
}

std::vector<uint8_t> J(std::vector<uint8_t> input) {
    std::vector<uint8_t> output(32);
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_shake256(), nullptr);
    EVP_DigestUpdate(ctx, input.data(), input.size());
    EVP_DigestFinalXOF(ctx, output.data(), output.size());
    EVP_MD_CTX_free(ctx);
    return output;
}

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> G(std::vector<uint8_t> input) {
    std::vector<uint8_t> output(64);
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    if (EVP_DigestInit_ex(ctx, EVP_sha3_512(), nullptr) != 1 ||
        EVP_DigestUpdate(ctx, input.data(), input.size()) != 1 ||
        EVP_DigestFinal_ex(ctx, output.data(), nullptr) != 1) {
        EVP_MD_CTX_free(ctx);
    }

    EVP_MD_CTX_free(ctx);

    std::vector<uint8_t> a(output.begin(), output.begin() + 32);
    std::vector<uint8_t> b(output.begin() + 32, output.end());
    return { a, b };
}