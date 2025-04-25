#ifndef NTT_H
#define NTT_H

#include <vector>
#include <cstdint>
#include "zeta.h"
#include "byteEncode.h"

constexpr uint16_t q = 3329;
constexpr uint16_t qInvN = 3303;

std::vector<uint16_t> NTT(std::vector<uint16_t>);
std::vector<uint16_t> inverseNTT(std::vector<uint16_t> input);

#endif // NTT_H
