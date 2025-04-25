#include "ntt.h"
#include "byteEncode.h"
#include "sampling.h"
#include "hash.h"
#include <vector>

enum class Variants {MLKEM512, MLKEM768, MLKEM1024};

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> kpkeKeyGen(uint8_t, Variants);
void kpkeEncrypt();
void kpkeDecrypt();