#ifndef RANDOM_H
#define RANDOM_H

#include <vector>
#include <cstdint>
#include <openssl/evp.h>

/// <summary>
/// Generates a 32 random bytes using BoringSSL
/// </summary>
/// <returns>32 random  bytes</returns>
std::vector<uint8_t> secureRandomBytes();

#endif // RANDOM_H