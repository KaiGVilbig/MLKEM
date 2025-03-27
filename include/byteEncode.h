#ifndef BYTE_ENCODE_H
#define BYTE_ENCODE_H

#include <vector>
#include <cstdint>

void byteEncode();
void byteDecode();
std::vector<uint8_t> bytesToBits(std::vector<uint8_t>);
std::vector<uint8_t> bitsToBytes(std::vector<uint8_t>);

#endif // BYTE_ENCODE_H