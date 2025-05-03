#include "random.h"
#include <openssl/rand.h>
#include <stdexcept>

// Secure Random Byte Generator using OpenSSL
std::vector<uint8_t> secureRandomBytes() {
    size_t size = 32;
    // Enable FIPS mode
    if (EVP_default_properties_enable_fips(NULL, 1) != 1) {
        throw std::runtime_error("Failed to enable FIPS mode");
    }

    std::vector<uint8_t> buffer(size);
    if (RAND_bytes(buffer.data(), static_cast<int>(size)) != 1) {
        EVP_default_properties_enable_fips(NULL, 0); // Ensure it's disabled on failure
        throw std::runtime_error("RAND_bytes failed in FIPS mode");
    }

    // Disable FIPS mode
    if (EVP_default_properties_enable_fips(NULL, 0) != 1) {
        throw std::runtime_error("Failed to disable FIPS mode after RNG");
    }

    return buffer;
}
//
//std::vector<uint8_t> PRF(std::vector<uint8_t> a, int N) {
//    std::vector<uint8_t> output(32);
//    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
//    EVP_DigestInit_ex(ctx, EVP_shake256(), nullptr);
//    EVP_DigestUpdate(ctx, a.data(), a.size());
//    EVP_DigestFinalXOF(ctx, output.data(), output.size());
//    EVP_MD_CTX_free(ctx);
//    return output;
//}