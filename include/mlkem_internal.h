#ifndef MLKEM_INTERNAL_H
#define MLKEM_INTERNAL_H
#include "kpke.h"

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> kemKeyGenInternal(std::vector<uint8_t>, std::vector<uint8_t>, Variants);
void kemEncapsInternal();
void kemDecapsInternal();

#endif // !MLKEM_INTERNAL_H
