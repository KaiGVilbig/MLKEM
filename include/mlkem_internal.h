#ifndef MLKEM_INTERNAL_H
#define MLKEM_INTERNAL_H
#include "kpke.h"
#include <iostream>
#include <sstream>
#include <iomanip>

/// <summary>
/// Uses randomness to generate an encapsulation key and a corresponding decapsulation key
/// </summary>
/// <param name="d">randomness d</param>
/// <param name="z">randomness z</param>
/// <param name="variant">ML-KEM variant</param>
/// <returns>encapsulation key ek and decapsulation key dk</returns>
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> kemKeyGenInternal(std::vector<uint8_t>, std::vector<uint8_t>, Variants);

/// <summary>
/// Uses the encapsulation key and randomness to generate a key and an associated ciphertext
/// </summary>
/// <param name="ek">encapsulation key ek</param>
/// <param name="m">randomness m</param>
/// <param name="variant">ML-KEM variant</param>
/// <returns>shared secret key K and ciphertext</returns>
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> kemEncapsInternal(std::vector<uint8_t>, std::vector<uint8_t>, Variants);

/// <summary>
/// Uses the decapsulation key to produce a shared secret key from a ciphertext
/// </summary>
/// <param name="dk">decapsulation key dk</param>
/// <param name="c">ciphertext c</param>
/// <param name="variant">ML-KEM variant</param>
/// <returns>shared secret key K</returns>
std::vector<uint8_t> kemDecapsInternal(std::vector<uint8_t>, std::vector<uint8_t>, Variants);

#endif // !MLKEM_INTERNAL_H
