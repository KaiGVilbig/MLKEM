#ifndef SAMPLING_H
#define SAMPLING_H

#include <vector>
#include <cstdint>

std::vector<uint16_t> SampleNTT(std::vector<uint8_t>);
std::vector<uint16_t> samplePolyCBD(std::vector<uint8_t>, uint8_t);

#endif // SAMPLING_H
