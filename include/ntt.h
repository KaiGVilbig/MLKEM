#ifndef NTT_H
#define NTT_H

#include <vector>
#include <cstdint>
#include "constants.h"
#include "byteEncode.h"

/// <summary>
/// Overflow safe multiplication mod q
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>a * b mod q</returns>
uint16_t modMul(uint16_t, uint16_t);
/// <summary>
/// Overflow safe signed multiplication mod q
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>a * b mod q</returns>
uint16_t modMulSigned(uint16_t, int16_t);
/// <summary>
/// Overflow safe addition
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>a + b mod q</returns>
uint16_t modAdd(uint16_t, uint16_t);
/// <summary>
/// Underflow safe subtraction mod q
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>a - b mod q</returns>
uint16_t modSub(uint16_t, uint16_t);

/// <summary>
/// Computes the NTT representation of fHat of the given polyomial f in Rq
/// </summary>
/// <param name="f">array f</param>
/// <returns>array fHat</returns>
std::vector<uint16_t> NTT(std::vector<uint16_t>);

/// <summary>
/// Computes the polynomial f in Rq that corresponds to the given NTT representation of fHat
/// </summary>
/// <param name="input">array fHat</param>
/// <returns>array f</returns>
std::vector<uint16_t> inverseNTT(std::vector<uint16_t> input);

/// <summary>
/// Computes the product (in the ring Tq) of two NTT representations
/// </summary>
/// <param name="fHat">fHat array</param>
/// <param name="gHat">gHat array</param>
/// <returns>array hHat</returns>
std::vector<uint16_t> multiplyNTT(std::vector<uint16_t>, std::vector<uint16_t>);

/// <summary>
/// Computes the product of two degree-one polynomials with respect to a quadratic modulus
/// </summary>
/// <param name="a0">coefficient a0</param>
/// <param name="a1">coefficient a1</param>
/// <param name="b0">coefficient b0</param>
/// <param name="b1">coefficient b1</param>
/// <param name="z2">z2</param>
/// <returns>c0, c1</returns>
std::vector<uint16_t> BaseCaseMultiply(uint16_t, uint16_t, uint16_t, uint16_t, int16_t);

#endif // NTT_H
