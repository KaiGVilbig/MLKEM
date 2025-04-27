#include "ntt.h"
#include "byteEncode.h"
#include "sampling.h"
#include "hash.h"
#include <vector>

enum class Variants {MLKEM512, MLKEM768, MLKEM1024};

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> kpkeKeyGen(std::vector<uint8_t> d, Variants variant);
void kpkeEncrypt();
void kpkeDecrypt();