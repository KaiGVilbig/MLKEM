#include "random.h"
#include <openssl/rand.h>
#include <stdexcept>

// Secure Random Byte Generator using OpenSSL
void secureRandomBytes(std::vector<uint8_t>& buffer, size_t size) {
    buffer.resize(size);
    if (RAND_bytes(buffer.data(), size) != 1) {
        throw std::runtime_error("OpenSSL RNG failed to generate secure random bytes.");
    }
}

std::vector<uint8_t> PRF(std::vector<uint8_t> a, int N) {
    std::vector<uint8_t> output(32);
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_shake256(), nullptr);
    EVP_DigestUpdate(ctx, a.data(), a.size());
    EVP_DigestFinalXOF(ctx, output.data(), output.size());
    EVP_MD_CTX_free(ctx);
    return output;
}