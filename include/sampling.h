#ifndef SAMPLING_H
#define SAMPLING_H

#include <vector>
#include <cstdint>

/// <summary>
/// Takes a 32-byte seed and two indices as input and outputs a pseudorandom element of Tq
/// </summary>
/// <param name="B">byte array B</param>
/// <returns>array aHat</returns>
std::vector<uint16_t> SampleNTT(std::vector<uint8_t>);

/// <summary>
/// Takes a seed as input and outputs a pseudorandom sample from the distribution Dn(Rq)
/// </summary>
/// <param name="B">byte array B</param>
/// <param name="n"></param>
/// <returns>array f</returns>
std::vector<uint16_t> samplePolyCBD(std::vector<uint8_t>, uint8_t);

#endif // SAMPLING_H
