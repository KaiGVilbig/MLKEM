#ifndef SAMPLING_H
#define SAMPLING_H

#include <vector>
#include <cstdint>

std::vector<uint16_t> SampleNTT(const std::vector<uint8_t>);
void samplePolyCBD();

#endif // SAMPLING_H
