#include "mlkem.h"
#include "mlkem_internal.h"
#include "random.h"
#include <iostream>
#include <vector>
#include <stdexcept>

extern "C" {

    EXPORT_API std::pair<std::string, std::string> mlkemKeyGen_512() {
        std::vector<uint8_t> d = secureRandomBytes();
        std::vector<uint8_t> z = secureRandomBytes();
        auto [ekh, dkh] = kemKeyGenInternal(d, z, Variants::MLKEM512);

        std::string ek = toHex(ekh);
        std::string dk = toHex(dkh);

        return { ek, dk };
    }

    EXPORT_API void mlkemEncaps_512() {
        std::vector<uint8_t> m = secureRandomBytes();
         kemEncapsInternal();
    }

    EXPORT_API void mlkemDecaps_512() {
        std::cout << "[INFO] ML-KEM.Decaps() called\n";
        // kemDecapsInternal();
        std::cout << "[INFO] ML-KEM.Decaps() completed\n";
    }

    EXPORT_API void mlkemKeyGen_768() {
        std::cout << "[INFO] ML-KEM.KeyGen() called\n";
        // kemKeyGenInternal();
        std::cout << "[INFO] ML-KEM.KeyGen() completed\n";
    }

    EXPORT_API void mlkemEncaps_768() {
        std::cout << "[INFO] ML-KEM.Encaps() called\n";
        // kemEncapsInternal();
        std::cout << "[INFO] ML-KEM.Encaps() completed\n";
    }

    EXPORT_API void mlkemDecaps_768() {
        std::cout << "[INFO] ML-KEM.Decaps() called\n";
        // kemDecapsInternal();
        std::cout << "[INFO] ML-KEM.Decaps() completed\n";
    }

    EXPORT_API void mlkemKeyGen_1024() {
        std::cout << "[INFO] ML-KEM.KeyGen() called\n";
        // kemKeyGenInternal();
        std::cout << "[INFO] ML-KEM.KeyGen() completed\n";
    }

    EXPORT_API void mlkemEncaps_1024() {
        std::cout << "[INFO] ML-KEM.Encaps() called\n";
        // kemEncapsInternal();
        std::cout << "[INFO] ML-KEM.Encaps() completed\n";
    }

    EXPORT_API void mlkemDecaps1024() {
        std::cout << "[INFO] ML-KEM.Decaps() called\n";
        // kemDecapsInternal();
        std::cout << "[INFO] ML-KEM.Decaps() completed\n";
    }
}
