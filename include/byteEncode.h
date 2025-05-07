#ifndef BYTE_ENCODE_H
#define BYTE_ENCODE_H

#include <vector>
#include <cstdint>
#include "ntt.h"

/// <summary>
/// Encodes an array of d-bit integers into a byte array 
/// for 1 <= d <= 12
/// </summary>
/// <param name="F">integer array F where m = 2^d if d < 12 and m = q if d = 12</param>
/// <param name="d">d</param>
/// <returns>byte array B</returns>
std::vector<uint8_t> byteEncode(std::vector<uint16_t>, uint8_t);

/// <summary>
/// Decodes a byte array into an array of d-bit integers for 1 <= d <= 12
/// </summary>
/// <param name="B">byte array B</param>
/// <param name="d">d</param>
/// <returns>integer array F where m = 2^d if d < 12 and m = q if d = 12</returns>
std::vector<uint16_t> byteDecode(std::vector<uint8_t>, uint8_t);

/// <summary>
/// Coverts a bit array (of a length that is a multiple of eight) into an array of bytes
/// </summary>
/// <param name="b">bit array b</param>
/// <returns>byte array B</returns>
std::vector<uint8_t> bytesToBits(std::vector<uint8_t>);

/// <summary>
/// Performs the inverse of bitsToBytes, converting a byte array into a bit array
/// </summary>
/// <param name="B">byte array B</param>
/// <returns>bit array b</returns>
std::vector<uint8_t> bitsToBytes(std::vector<uint8_t>);

std::vector<uint16_t> Compress(std::vector<uint16_t>, int);

std::vector<uint16_t> Decompress(std::vector<uint16_t>, int);

#endif // BYTE_ENCODE_H