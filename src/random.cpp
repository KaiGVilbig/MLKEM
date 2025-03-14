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