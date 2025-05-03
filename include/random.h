#ifndef RANDOM_H
#define RANDOM_H

#include <vector>
#include <cstdint>
#include <openssl/evp.h>

std::vector<uint8_t> secureRandomBytes();
//std::vector<uint8_t> PRF(std::vector<uint8_t>, int);

#endif // RANDOM_H