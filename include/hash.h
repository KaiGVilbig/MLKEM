#ifndef HASH_H
#define HASH_H
#include <openssl/evp.h> // For OpenSSL functions
#include <openssl/sha.h> // For OpenSSL SHA3
#include <vector>

std::vector<uint8_t> prfEta(int eta, std::vector<uint8_t> s, uint8_t b);
std::vector<uint8_t> H(std::vector<uint8_t>);
std::vector<uint8_t> J(std::vector<uint8_t>);
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> G(std::vector<uint8_t>);

#endif