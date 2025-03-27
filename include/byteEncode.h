#ifndef BYTE_ENCODE_H
#define BYTE_ENCODE_H

#include <vector>
#include <cstdint>

void byteEncode();
void byteDecode();
uint64_t bytesToBits(const std::vector<uint8_t>, size_t);
std::vector<uint8_t> bitsToBytes(uint64_t, size_t);

#endif // BYTE_ENCODE_H