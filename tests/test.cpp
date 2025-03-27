#include "mlkem.h"
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

void testHashFunctions() {
    std::vector<uint8_t> input = { 't', 'e', 's', 't' }; // "test" in ASCII
    std::vector<uint8_t> expected = {
        0x36, 0xf0, 0x28, 0x58, 0x0b,
        0xb0, 0x2c, 0xc8, 0x27, 0x2a, 
        0x9a, 0x02, 0x0f, 0x42, 0x00,
        0xe3, 0x46, 0xe2, 0x76, 0xae,
        0x66, 0x4e, 0x45, 0xee, 0x80,
        0x74, 0x55, 0x74, 0xe2, 0xf5,
        0xab, 0x80
    }; // SHA3-256("test")

    std::cout << "[TEST] Running Hash function H Test...\n";
    std::vector<uint8_t> result = H(input);
    if (result == expected) {
        std::cout << "[PASS] Hash function H executed successfully\n\n";
    }
    else {
        std::cout << "[FAIL] Hash function H Test Failed: Result did not equal known expected output\n\n";
    }
}

int main() {
    std::cout << "===============================\n";
    std::cout << " ML-KEM Library Test Suite \n";
    std::cout << "===============================\n\n";


    testHashFunctions();

    //testKeyGen();
    //testEncaps();
    //testDecaps();

    return 0;
}