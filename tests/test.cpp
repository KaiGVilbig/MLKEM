#include "mlkem.h"
#include <iostream>
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

int main() {
    std::cout << "===============================\n";
    std::cout << " ML-KEM Library Test Suite \n";
    std::cout << "===============================\n\n";

    testKeyGen();
    testEncaps();
    testDecaps();

    return 0;
}