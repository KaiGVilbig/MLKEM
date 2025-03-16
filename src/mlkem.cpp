#include "mlkem.h"
#include "mlkem_internal.h"
#include "random.h"
#include <iostream>
#include <vector>
#include <stdexcept>

#define MLKEM_SEED_SIZE 32  // 32-byte secure seed

extern "C" {

    EXPORT_API void kemKeyGen() {
        std::cout << "[INFO] ML-KEM.KeyGen() called\n";
        kemKeyGenInternal();
        std::cout << "[INFO] ML-KEM.KeyGen() completed\n";
    }

    EXPORT_API void kemEncaps() {
        std::cout << "[INFO] ML-KEM.Encaps() called\n";
        kemEncapsInternal();
        std::cout << "[INFO] ML-KEM.Encaps() completed\n";
    }

    EXPORT_API void kemDecaps() {
        std::cout << "[INFO] ML-KEM.Decaps() called\n";
        kemDecapsInternal();
        std::cout << "[INFO] ML-KEM.Decaps() completed\n";
    }

}
