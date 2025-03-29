#include "mlkem.h"
#include "byteEncode.h"
#include "hash.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <stdexcept>

void testKeyGen() {
    try {
        std::cout << "[TEST] Running KeyGen Test...\n";
        kemKeyGen();
        std::cout << "[PASS] KeyGen executed successfully.\n\n";
    }
    catch (const std::exception& e) {
        std::cerr << "[FAIL] KeyGen Test Failed: " << e.what() << "\n\n";
    }
}

void testEncaps() {
    try {
        std::cout << "[TEST] Running Encapsulation Test...\n";
        kemEncaps();
        std::cout << "[PASS] Encapsulation executed successfully.\n\n";
    }
    catch (const std::exception& e) {
        std::cerr << "[FAIL] Encapsulation Test Failed: " << e.what() << "\n\n";
    }
}

void testDecaps() {
    try {
        std::cout << "[TEST] Running Decapsulation Test...\n";
        kemDecaps();
        std::cout << "[PASS] Decapsulation executed successfully.\n\n";
    }
    catch (const std::exception& e) {
        std::cerr << "[FAIL] Decapsulation Test Failed: " << e.what() << "\n\n";
    }
}

void testBitsBytesConversions() {
    std::vector<uint8_t> bits = {1, 1, 0, 1, 0, 0, 0, 1}; 
    std::vector<uint8_t> bytes = { 0x8b };

    std::cout << "[TEST] Running Bits to Bytes conversion function Test...\n";
    std::vector<uint8_t> result1 = bitsToBytes(bits);
    if (result1 == bytes) {
        std::cout << "[PASS] Bits to Bytes conversion executed successfully\n\n";
    }
    else {
        std::cout << "[FAIL] Bits to Bytes conversion test failed: Result did not equal known expected output\n\n";
    }

    std::cout << "[TEST] Running Bytes to Bits conversion function Test...\n";
    std::vector<uint8_t> result2 = bytesToBits(bytes);
    if (result2 == bits) {
        std::cout << "[PASS] Bytes to Bits conversion executed successfully\n\n";
    }
    else {
        std::cout << "[FAIL] Bytes to Bits conversion test failed: Result did not equal known expected output\n\n";
    }
}

void testByteEncodeDecode() {
    // Test for d = 1
    std::cout << "[TEST] Running Byte encode/decode function Test for d = 1, 4, 12...\n";
    std::vector<uint8_t> input1(256, 0);
    for (int i = 0; i < 256; i++) {
        input1[i] = i % 2;
    }
    auto encoded1 = byteEncode(input1, 1);
    auto decoded1 = byteDecode(encoded1, 1);
    if (decoded1 == input1) {
        std::cout << "[PASS] Byte encode/decode for d = 1 executed successfully\n";
    }
    else {
        std::cout << "[FAIL] Byte encode/decode for d = 1 failed: Result did not equal known expected output\n";
    }

    // Test for d = 4
    std::vector<uint8_t> input4(256, 0);
    for (int i = 0; i < 256; i++) {
        input4[i] = i % 16;
    }
    auto encoded4 = byteEncode(input4, 4);
    auto decoded4 = byteDecode(encoded4, 4);
    if (decoded1 == input1) {
        std::cout << "[PASS] Byte encode/decode for d = 4 executed successfully\n";
    }
    else {
        std::cout << "[FAIL] Byte encode/decode for d = 4 failed: Result did not equal known expected output\n";
    }

    // Test for d = 12
    std::vector<uint8_t> input12(256, 0);
    for (int i = 0; i < 256; i++) {
        input12[i] = (i * 17) % 3329;
    }
    auto encoded12 = byteEncode(input12, 12);
    auto decoded12 = byteDecode(encoded12, 12);
    if (decoded1 == input1) {
        std::cout << "[PASS] Byte encode/decode for d = 12 executed successfully\n\n";
    }
    else {
        std::cout << "[FAIL] Byte encode/decode for d = 12 failed: Result did not equal known expected output\n\n";
    }
}

void testHashFunctions() {
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
    }
    else {
        std::cout << "[FAIL] Hash function H test failed: Result did not equal known expected output\n\n";
    }

    std::cout << "[TEST] Running Hash function J Test...\n";
    std::vector<uint8_t> resultJ = J(input);
    if (resultJ == expectedJ) {
        std::cout << "[PASS] Hash function J executed successfully\n\n";
    }
    else {
        std::cout << "[FAIL] Hash function J test failed: Result did not equal known expected output\n\n";
    }

    std::cout << "[TEST] Running Hash function G Test...\n";
    auto [resultG1, resultG2] = G(input);
    if (resultG1 == expectedG1 && resultG2 == expectedG2) {
        std::cout << "[PASS] Hash function G executed successfully\n\n";
    }
    else {
        std::cout << "[FAIL] Hash function G test failed: Result did not equal known expected output\n\n";
    }

}

int main() {
    std::cout << "===============================\n";
    std::cout << " ML-KEM Library Test Suite \n";
    std::cout << "===============================\n\n";

    // Test the bits to bytes and bytes to bits conversions
    testBitsBytesConversions();
    testByteEncodeDecode();
    // Test the hash functions H, J and G
    testHashFunctions();


    //testKeyGen();
    //testEncaps();
    //testDecaps();

    return 0;
}