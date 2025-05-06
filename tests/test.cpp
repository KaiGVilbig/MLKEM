#include "test.h"

std::vector<uint8_t> getSeed(Variants variant) {
    switch (variant) {
    case Variants::MLKEM512:
        return seed512;
    case Variants::MLKEM768:
        return seed768;
    case Variants::MLKEM1024:
        return seed1024;
    default:
        return seed512;
    }
}
std::vector<uint8_t> getZ(Variants variant) {
    switch (variant) {
    case Variants::MLKEM512:
        return z512;
    case Variants::MLKEM768:
        return z768;
    case Variants::MLKEM1024:
        return z1024;
    default:
        return z512;
    }
}
std::vector<uint8_t> getMessage(Variants variant) {
    switch (variant) {
    case Variants::MLKEM512:
        return message512;
    case Variants::MLKEM768:
        return message768;
    case Variants::MLKEM1024:
        return message1024;
    default:
        return message512;
    }
}
std::vector<uint8_t> getK(Variants variant) {
    switch (variant) {
    case Variants::MLKEM512:
        return K512;
    case Variants::MLKEM768:
        return K768;
    case Variants::MLKEM1024:
        return K1024;
    default:
        return K512;
    }
}
std::string getVarString(Variants variant) {
    switch (variant) {
    case Variants::MLKEM512:
        return "MLKEM512";
    case Variants::MLKEM768:
        return "MLKEM768";
    case Variants::MLKEM1024:
        return "MLKEM1024";
    default:
        return "MLKEM512";
    }
}


std::pair<std::vector<uint8_t>, std::vector<uint8_t>> testKpkeKeyGen(Variants variant) {

    // Call KeyGen
    auto [ekPKE, dkPKE] = kemKeyGenInternal(getSeed(variant), getZ(variant), variant);

    // Print sizes
    std::cout << "[PASS] K-PKE.KeyGen(" << getVarString(variant) << ") completed!" << std::endl;
    
    return { ekPKE, dkPKE };
}

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> testKpkeEncrypt(std::vector<uint8_t> ek, Variants variant) {

    auto [K, c] = kemEncapsInternal(ek, getMessage(variant), variant);
    auto [K2, c2] = kemEncapsInternal(ek, getMessage(variant), variant);

    if (c != c2) {
        std::cout << "[FAIL] Ciphertext mismatch: encryption not deterministic!";
    }
    else {
        std::cout << "[PASS] K-PKE.Encrypt(" << getVarString(variant) << ") completed!\n";
    }
    return { K, c };
}

void testkpkeDecrypt(int& pass, int& fail, std::vector<uint8_t> dk, std::vector<uint8_t> c, std::vector<uint8_t> K, Variants variant) {
    auto decrypted = kemDecapsInternal(dk, c, variant);

    if (K == decrypted && K == getK(variant)) {
        std::cout << "[PASS] K-PKE.Decrypt(" << getVarString(variant) << "): shared secret key K successfully recovered.\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] K-PKE.Decrypt(" << getVarString(variant) << "): Key mismatch!\n";
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

void testByteEncodeDecode(int& pass, int& fail) {
    std::cout << "[TEST] Running Byte Encode/Decode function Test...\n";

    for (int d = 1; d <= 12; ++d) {
        std::vector<uint16_t> input(256);
        uint16_t maxVal = (d == 12) ? 3329 : (1 << d);

        // Fill input with a pattern
        for (int i = 0; i < 256; ++i) {
            input[i] = i % maxVal;
        }

        auto encoded = byteEncode(input, d);
        auto decoded = byteDecode(encoded, d);

        if (input != decoded) {
            std::cout << "[FAIL] ByteEncode/Decode round-trip failed for d = " << d << "\n";
            fail++;
            pass--;
        }

        std::cout << "[PASS] ByteEncode/Decode round-trip passed for d = " << d << "\n";
    }
    pass++;
    std::cout << std::endl;
}

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
        std::cout << "[PASS] Hash function H executed successfully\n";
        pass++;
    }
    else {
        std::cout << "[FAIL] Hash function H test failed: Result did not equal known expected output\n\n";
        fail++;
    }

    std::cout << "[TEST] Running Hash function J Test...\n";
    std::vector<uint8_t> resultJ = J(input);
    if (resultJ == expectedJ) {
        std::cout << "[PASS] Hash function J executed successfully\n";
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
    testByteEncodeDecode(pass, fail);
    // Test the hash functions H, J and G
    testHashFunctions(pass, fail);

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

bool testMainFunctions() {
    int pass = 0, fail = 0;

    std::cout << "Test Main Functions\n";
    std::cout << "-------------------------------\n\n";

    constexpr Variants allVariants[] = {
        Variants::MLKEM512,
        Variants::MLKEM768,
        Variants::MLKEM1024
    };

    for (Variants v : allVariants) {
        auto [ek, dk] = testKpkeKeyGen(v);
        auto [K, c] = testKpkeEncrypt(ek, v);
        testkpkeDecrypt(pass, fail, dk, c, K, v);
        std::cout << std::endl;
    }

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
    bool mainPassed = false;
    if (supportsPassed) {
        mainPassed = testMainFunctions();
    }

    if (mainPassed) {
        std::cout << "-------------------------------\n\n";
        std::cout << "All tests passed\n\n";
        std::cout << "===============================\n\n";
    }

    return 0;
}
