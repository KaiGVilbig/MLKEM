#include "random.h"
#include <openssl/rand.h> // BoringSSL includes OpenSSL headers
#include <stdexcept>

// Secure Random Byte Generator using OpenSSL
std::vector<uint8_t> secureRandomBytes() {
    size_t size = 32;
    std::vector<uint8_t> buffer(size);

    // Use BoringSSL's RAND_bytes to generate cryptographically secure random bytes
    if (RAND_bytes(buffer.data(), static_cast<int>(size)) != 1) {
        throw std::runtime_error("RAND_bytes failed in BoringSSL");
    }

    return buffer;
}