#ifndef BYTE_ENCODE_H
#define BYTE_ENCODE_H

#include <vector>
#include <cstdint>
#include "ntt.h"

std::vector<uint8_t> byteEncode(const std::vector<uint16_t>, uint8_t);
std::vector<uint8_t> byteDecode(const std::vector<uint8_t>, uint8_t);
std::vector<uint8_t> bytesToBits(std::vector<uint8_t>);
std::vector<uint8_t> bitsToBytes(std::vector<uint8_t>);
uint8_t bitRev(uint8_t);

#endif // BYTE_ENCODE_H