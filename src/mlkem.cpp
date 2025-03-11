#include "mlkem.h"
#include <iostream>

extern "C" {

    EXPORT_API void kemKeyGen() {
        std::cout << "Generating ML-KEM key pair..." << std::endl;
    }

    EXPORT_API void kemEncaps() {
        std::cout << "Encapsulating key..." << std::endl;
    }

    EXPORT_API void kemDecaps() {
        std::cout << "Decapsulating key..." << std::endl;
    }

}
