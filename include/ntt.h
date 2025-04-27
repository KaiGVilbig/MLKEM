#ifndef NTT_H
#define NTT_H

#include <vector>
#include <cstdint>
#include "constants.h"
#include "byteEncode.h"

uint16_t modMul(uint16_t, uint16_t);
uint16_t modMulSigned(uint16_t, int16_t);
uint16_t modAdd(uint16_t, uint16_t);
uint16_t modSub(uint16_t, uint16_t);


std::vector<uint16_t> NTT(std::vector<uint16_t>);
std::vector<uint16_t> inverseNTT(std::vector<uint16_t> input);

std::vector<uint16_t> multiplyNTT(std::vector<uint16_t>, std::vector<uint16_t>);
std::vector<uint16_t> BaseCaseMultiply(uint16_t, uint16_t, uint16_t, uint16_t, int16_t);

#endif // NTT_H
