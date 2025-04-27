#include "mlkem.h"
#include "byteEncode.h"
#include "hash.h"
#include "sampling.h"
#include "ntt.h"
#include "kpke.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <stdexcept>
#include <string>
#include <random>


void testKpkeKeyGen() {
    // Initialize the seed with random values
    std::vector<uint8_t> seed(32);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);

    // Fill the seed with random bytes
    for (auto& byte : seed) {
        byte = static_cast<uint8_t>(distrib(gen));
    }

    // Call KeyGen
    auto [ekPKE, dkPKE] = kpkeKeyGen(seed, Variants::MLKEM512);

    // Print sizes
    std::cout << "[PASS] K-PKE.KeyGen(MLKEM512) completed!" << std::endl;
    std::cout << "Public key size: " << ekPKE.size() << " bytes" << std::endl;
    std::cout << "Secret key size: " << dkPKE.size() << " bytes" << std::endl;
}

void testEncaps(int& pass, int& fail) {
    try {
        std::cout << "[TEST] Running Encapsulation Test...\n";
        kemEncaps();
        std::cout << "[PASS] Encapsulation executed successfully.\n\n";
        pass++;
    }
    catch (const std::exception& e) {
        std::cerr << "[FAIL] Encapsulation Test Failed: " << e.what() << "\n\n";
        fail++;
    }
}

void testDecaps(int& pass, int& fail) {
    try {
        std::cout << "[TEST] Running Decapsulation Test...\n";
        kemDecaps();
        std::cout << "[PASS] Decapsulation executed successfully.\n\n";
        pass++;
    }
    catch (const std::exception& e) {
        std::cerr << "[FAIL] Decapsulation Test Failed: " << e.what() << "\n\n";
        fail++;
    }
}

void testBitsBytesConversions(int& pass, int& fail) {
    std::vector<uint8_t> bits = {1, 1, 0, 1, 0, 0, 0, 1}; 
    std::vector<uint8_t> bytes = { 0x8b };

    std::cout << "[TEST] Running Bits to Bytes conversion function Test...\n";
    std::vector<uint8_t> result1 = bitsToBytes(bits);
    if (result1 == bytes) {
        std::cout << "[PASS] Bits to Bytes conversion executed successfully\n\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] Bits to Bytes conversion test failed: Result did not equal known expected output\n\n";
        fail++;
    }

    std::cout << "[TEST] Running Bytes to Bits conversion function Test...\n";
    std::vector<uint8_t> result2 = bytesToBits(bytes);
    if (result2 == bits) {
        std::cout << "[PASS] Bytes to Bits conversion executed successfully\n\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] Bytes to Bits conversion test failed: Result did not equal known expected output\n\n";
        fail++;
    }
}

//void testByteEncodeDecode(int& pass, int& fail) {
//    // Test for d = 1
//    std::cout << "[TEST] Running Byte encode/decode function Test for d = 1, 4, 12...\n";
//    std::vector<uint8_t> input1(256, 0);
//    for (int i = 0; i < 256; i++) {
//        input1[i] = i % 2;
//    }
//    auto encoded1 = byteEncode(input1, 1);
//    auto decoded1 = byteDecode(encoded1, 1);
//    if (decoded1 == input1) {
//        std::cout << "[PASS] Byte encode/decode for d = 1 executed successfully\n";
//        pass++;
//    }
//    else {
//        std::cout << "[FAIL] Byte encode/decode for d = 1 failed: Result did not equal known expected output\n";
//        fail++;
//    }
//
//    // Test for d = 4
//    std::vector<uint8_t> input4(256, 0);
//    for (int i = 0; i < 256; i++) {
//        input4[i] = i % 16;
//    }
//    auto encoded4 = byteEncode(input4, 4);
//    auto decoded4 = byteDecode(encoded4, 4);
//    if (decoded1 == input1) {
//        std::cout << "[PASS] Byte encode/decode for d = 4 executed successfully\n";
//        pass++;
//    }
//    else {
//        std::cout << "[FAIL] Byte encode/decode for d = 4 failed: Result did not equal known expected output\n";
//        fail++;
//    }
//
//    // Test for d = 12
//    std::vector<uint8_t> input12(256, 0);
//    for (int i = 0; i < 256; i++) {
//        input12[i] = (i * 17) % 3329;
//    }
//    auto encoded12 = byteEncode(input12, 12);
//    auto decoded12 = byteDecode(encoded12, 12);
//    if (decoded1 == input1) {
//        std::cout << "[PASS] Byte encode/decode for d = 12 executed successfully\n\n";
//        pass++;
//    }
//    else {
//        std::cout << "[FAIL] Byte encode/decode for d = 12 failed: Result did not equal known expected output\n\n";
//        fail++;
//    }
//}

void testHashFunctions(int& pass, int& fail) {
    std::vector<uint8_t> input = { 't', 'e', 's', 't' }; // "test" in ASCII
    std::vector<uint8_t> expectedH = {
        0x36, 0xf0, 0x28, 0x58, 0x0b,
        0xb0, 0x2c, 0xc8, 0x27, 0x2a, 
        0x9a, 0x02, 0x0f, 0x42, 0x00,
        0xe3, 0x46, 0xe2, 0x76, 0xae,
        0x66, 0x4e, 0x45, 0xee, 0x80,
        0x74, 0x55, 0x74, 0xe2, 0xf5,
        0xab, 0x80
    }; // SHA3-256("test")
    std::vector<uint8_t> expectedJ = {
        0xb5, 0x4f, 0xf7, 0x25, 0x57, 
        0x05, 0xa7, 0x1e, 0xe2, 0x92, 
        0x5e, 0x4a, 0x3e, 0x30, 0xe4,
        0x1a, 0xed, 0x48, 0x9a, 0x57,
        0x9d, 0x55, 0x95, 0xe0, 0xdf, 
        0x13, 0xe3, 0x2e, 0x1e, 0x4d,
        0xd2, 0x02
    };
    std::vector<uint8_t> expectedG1 = {
        0x9e, 0xce, 0x08, 0x6e, 0x9b, 
        0xac, 0x49, 0x1f, 0xac, 0x5c,
        0x1d, 0x10, 0x46, 0xca, 0x11,
        0xd7, 0x37, 0xb9, 0x2a, 0x2b,
        0x2e, 0xbd, 0x93, 0xf0, 0x05,
        0xd7, 0xb7, 0x10, 0x11, 0x0c, 
        0x0a, 0x67
    };
    std::vector<uint8_t> expectedG2 = {
        0x82, 0x88, 0x16, 0x6e, 0x7f, 
        0xbe, 0x79, 0x68, 0x83, 0xa4,
        0xf2, 0xe9, 0xb3, 0xca, 0x9f,
        0x48, 0x4f, 0x52, 0x1d, 0x0c,
        0xe4, 0x64, 0x34, 0x5c, 0xc1,
        0xae, 0xc9, 0x67, 0x79, 0x14,
        0x9c, 0x14
    };

    std::cout << "[TEST] Running Hash function H Test...\n";
    std::vector<uint8_t> resultH = H(input);
    if (resultH == expectedH) {
        std::cout << "[PASS] Hash function H executed successfully\n\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] Hash function H test failed: Result did not equal known expected output\n\n";
        fail++;
    }

    std::cout << "[TEST] Running Hash function J Test...\n";
    std::vector<uint8_t> resultJ = J(input);
    if (resultJ == expectedJ) {
        std::cout << "[PASS] Hash function J executed successfully\n\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] Hash function J test failed: Result did not equal known expected output\n\n";
        fail++;
    }

    std::cout << "[TEST] Running Hash function G Test...\n";
    auto [resultG1, resultG2] = G(input);
    if (resultG1 == expectedG1 && resultG2 == expectedG2) {
        std::cout << "[PASS] Hash function G executed successfully\n\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] Hash function G test failed: Result did not equal known expected output\n\n";
        fail++;
    }

}

void testSampleNTT(int& pass, int& fail) {
    // Known input (34 bytes)
    std::vector<uint8_t> known_input = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
        0x20, 0x21
    };

    // Expected output (NTT-transformed 256-coefficient polynomial)
    std::vector<uint16_t> expected_output = {
        3732, 1129, 3368, 1207, 3194, 2446, 407, 980, 
        3595, 3350, 2783, 2348, 3698, 153, 3385, 1507,
        3562, 386, 1437, 2930, 126, 2210, 2707, 2954, 
        543, 3097, 3824, 2827, 1161, 3371, 1957, 2614,
        1022, 3796, 1994, 126, 354, 2263, 2737, 2744, 
        785, 1275, 2007, 1850, 1628, 2990, 2299, 1170, 
        1779, 781, 3706, 1353, 83, 549, 3542, 2503, 
        96, 117, 873, 2183, 3525, 462, 93, 2676, 
        2291, 2953, 178, 3751, 4031, 1788, 1591, 3179, 
        3706, 2941, 2539, 3907, 3768, 2328, 1358, 1766, 
        1820, 221, 580, 1488, 293, 1868, 2257, 751, 
        2179, 790, 1755, 292, 1366, 3895, 3792, 3998, 
        2808, 3750, 4076, 2863, 2526, 755, 2514, 1867, 
        1317, 3512, 1350, 18, 3134, 1029, 2993, 1902,
        1592, 671, 361, 1020, 2141, 3764, 3658, 3754, 
        2365, 2097, 929, 1351, 1623, 563, 2184, 840, 
        1572, 2466, 1842, 3518, 279, 3215, 2747, 833, 
        1078, 3633, 2857, 897, 499, 703, 1357, 3429, 
        465, 389, 3011, 3339, 2303, 755, 1300, 2552, 
        1658, 3919, 855, 3083, 995, 2731, 3917, 2205, 
        1474, 317, 3739, 2881, 179, 498, 1977, 1305, 
        3136, 2659, 135, 2118, 2587, 857, 1461, 1550, 
        288, 2564, 2443, 1251, 1845, 2842, 1694, 743, 
        902, 1912, 3315, 486, 2130, 3288, 3216, 2970, 
        1757, 2026, 2067, 1719, 3137, 1492, 2536, 730, 
        489, 384, 2528, 67, 1162, 751, 799, 238, 1194, 
        1145, 1870, 261, 1851, 2169, 2648, 3959, 3514, 
        678, 43, 835, 3393, 589, 169, 1737, 2732, 444, 
        717, 2499, 2028, 2106, 1799, 3993, 3389, 981, 
        2642, 3130, 2384, 2357, 3718, 1517, 2991, 561, 
        57, 3632, 2876, 3834, 3196, 2733, 3504, 2106, 
        3372, 1700, 31, 840, 1046, 1081
    };

    std::cout << "[TEST] Running SampleNTT function Test...\n";

    // Compute NTT transformation
    std::vector<uint16_t> result = SampleNTT(known_input);

    // Verify output against expected values
    if (result.size() == expected_output.size()) {
        std::cout << "[PASS] SampleNTT produced expected output size\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] SampleNTT test failed: Result did not produce expected output size\n\n";
        fail++;
        return;
    }
    int failedCount = 0;
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i] != expected_output[i]) failedCount++;
    }
    if (failedCount == 0) {
        std::cout << "[PASS] SampleNTT executed successfully\n\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] SampleNTT test failed: Result did not equal known expected output\n\n";
        fail++;
    }
}

void testSamplePolyCBD(int& pass, int& fail) {
    const int eta = 2;
    const int q = 4096;
    const size_t byteCount = 64 * eta;

    std::cout << "[TEST] Running SampleNTT function Test...\n";

    std::vector<uint8_t> B(byteCount, 0x00);

    // Set first 4 bytes manually to introduce predictable bit patterns
    B[0] = 0b00000000; // bits 0–7
    B[1] = 0b00001111; // bits 8–15
    B[2] = 0b11110000; // bits 16–23
    B[3] = 0b11000011; // bits 24–31

    std::vector<uint16_t> expected = {
    0, 0, 0, 0, 0, 0, 2, 4094
    };
    // Remaining bytes can stay 0x00 since we are only checking first few outputs

    std::vector<uint16_t> result = samplePolyCBD(B, eta);
    bool firstTest = true;
    for (size_t i = 0; i < expected.size(); ++i) {
        if (result[i] != expected[i]) {
            firstTest = false;
        }
    }    
    if (firstTest) {
        std::cout << "[PASS] SamplePolyCBD executed successfully\n\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] SamplePolyCBD test failed: Result did not equal known expected output\n\n";
        fail++;
    }
}

void testNTT(int& pass, int& fail) {
    // Create a test input: [0, 1, 2, ..., 255]
    std::cout << "[TEST] Running NTT and inverseNTT function Test...\n";

    std::vector<uint16_t> input(256);
    for (size_t i = 0; i < 256; ++i) {
        input[i] = static_cast<uint16_t>(i);
    }
    
    // Run NTT and inverse NTT
    std::vector<uint16_t> transformed = NTT(input);
    std::vector<uint16_t> recovered = inverseNTT(transformed);
    
    // Verify: recovered == original input
    bool good = true;
    for (size_t i = 0; i < 256; ++i) {
        if (recovered[i] != input[i]) {
            good = false;
        }
    }
    
    if (good) {
        std::cout << "[PASS] NTT and inverseNTT executed successfully\n\n";
        pass++;
    } else {
        std::cout << "[FAIL] NTT and inverseNTT test failed: input NTT'd and inverseNTT'd did not match\n\n";
        fail++;
    }
}

void testMultiplyNTT(int& pass, int& fail) {
    std::cout << "[TEST] Running NTT and inverseNTT function Test...\n";

    const int N = 256;
    const uint16_t expectedh1 = 4;

    std::vector<uint16_t> a_hat(N, 1);  // all 1s
    std::vector<uint16_t> b_hat(N, 2);  // all 2s

    std::vector<uint16_t> result = multiplyNTT(a_hat, b_hat);
    if (result.size() == N) {
        std::cout << "[PASS] multiplyNTT returned executed size successfully\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] multiplyNTT test failed: multiplyNTT returned incorrect size\n";
        fail++;
    }

    bool passed = true;
    for (int i = 0; i < 128; i++) {
        uint16_t expectedh0 = modAdd(2, modMulSigned(2, Zeta2[i]));  // 2 + 2*zeta[i] mod q
        if (result[2 * i + 1] != expectedh1 && result[2 * i] != expectedh0) {
            passed = false;
        }
    }

    if (passed) {
        std::cout << "[PASS] multiplyNTT returned executed output successfully\n\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] multiplyNTT test failed: multiplyNTT returned incorrect output\n\n";
        fail++;
    }
}

bool testSupportFunctions() {
    int pass = 0, fail = 0;

    std::cout << "Test Support Functions\n";
    std::cout << "-------------------------------\n\n";

    // Test the bits to bytes and bytes to bits conversions
    testBitsBytesConversions(pass, fail);
    //testByteEncodeDecode(pass, fail);
    // Test the hash functions H, J and G
    testHashFunctions(pass, fail);

    // Test the Sampling functions
    testSampleNTT(pass, fail);
    testSamplePolyCBD(pass, fail);

    // Test the NTT functions
    testNTT(pass, fail);
    testMultiplyNTT(pass, fail);

    std::cout << "Support Functions Tests Completed\n";
    std::cout << std::to_string(pass) << " tests passed, " << std::to_string(fail) << " tests failed\n";
    std::cout << "-------------------------------\n\n";

    if (fail > 0) {
        return false;
    }
    return true;
}

int main() {
    std::cout << "===============================\n";
    std::cout << " ML-KEM Library Test Suite \n";
    std::cout << "===============================\n\n";

    bool supportsPassed = testSupportFunctions();
    testKpkeKeyGen();
    return 0;
}