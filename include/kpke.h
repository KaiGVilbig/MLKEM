#ifndef KPKE_H
#define KPKE_H

#include "ntt.h"
#include "byteEncode.h"
#include "sampling.h"
#include "hash.h"
#include <vector>

enum class Variants {MLKEM512, MLKEM768, MLKEM1024};

/// <summary>
/// Uses randomness to generate an encryption key and a corresponding decryption key
/// </summary>
/// <param name="d">randomness d</param>
/// <param name="variant">ML-KEM variant</param>
/// <returns>encryption key ek and decryption key dk</returns>
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> kpkeKeyGen(std::vector<uint8_t>, Variants);

/// <summary>
/// Uses the encryption key to encrypt a plaintext message using the randomness r
/// </summary>
/// <param name="ek">encryption key ek</param>
/// <param name="m">message m</param>
/// <param name="r">randomness r</param>
/// <param name="variant">ML-KEM variant</param>
/// <returns>ciphertext c</returns>
std::vector<uint8_t> kpkeEncrypt(std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>, Variants);

/// <summary>
/// Uses the decryption key to derypt a ciphertext
/// </summary>
/// <param name="dk">decryption key dk</param>
/// <param name="c">ciphertext c</param>
/// <param name="variant">ML-KEM variant</param>
/// <returns>message m</returns>
std::vector<uint8_t> kpkeDecrypt(std::vector<uint8_t>, std::vector<uint8_t>, Variants);

#endif