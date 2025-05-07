#ifndef HASH_H
#define HASH_H
#include <openssl/evp.h> // For OpenSSL functions
#include <openssl/sha.h> // For OpenSSL SHA3
#include <vector>

/// <summary>
/// Takes one 32-byte input and one 1-byte input and produces on 64*n byte output
/// </summary>
/// <param name="eta">n</param>
/// <param name="s">32 byte input</param>
/// <param name="b">1 byte input</param>
/// <returns>64*n byte output</returns>
std::vector<uint8_t> prfEta(int eta, std::vector<uint8_t> s, uint8_t b);

/// <summary>
/// Take one variable-length input and produces one 32-byte output using SHA3-256
/// </summary>
/// <param name="">variable length input</param>
/// <returns>32-byte output</returns>
std::vector<uint8_t> H(std::vector<uint8_t>);

/// <summary>
/// Take one variable-length input and produces one 32-byte output using SHAKE256
/// </summary>
/// <param name="">variable length input</param>
/// <returns>32-byte output</returns>
std::vector<uint8_t> J(std::vector<uint8_t>);

/// <summary>
/// Takes one variable-length input and produces two 32-byte outputs using SHA3-512
/// </summary>
/// <param name="c">variable length input</param>
/// <returns>a pair of 32-byte outputs</returns>
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> G(std::vector<uint8_t>);

#endif