#ifndef MLKEM_INTERNAL_H
#define MLKEM_INTERNAL_H
#include "kpke.h"

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> kemKeyGenInternal(std::vector<uint8_t>, std::vector<uint8_t>, Variants);
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> kemEncapsInternal(std::vector<uint8_t>, std::vector<uint8_t>, Variants);
std::vector<uint8_t> kemDecapsInternal(std::vector<uint8_t>, std::vector<uint8_t>, Variants);
#endif // !MLKEM_INTERNAL_H
