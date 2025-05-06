#include "mlkem.h"
#include "mlkem_internal.h"
#include "random.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>

extern "C" {

    EXPORT_API keys512 mlkemKeyGen_512() {
        std::vector<uint8_t> d = secureRandomBytes();
        std::vector<uint8_t> z = secureRandomBytes();
        auto [ek, dk] = kemKeyGenInternal(d, z, Variants::MLKEM512);

        keys512 retKeys;
        std::memcpy(retKeys.ek, ek.data(), ek.size());
        std::memcpy(retKeys.dk, dk.data(), dk.size());

        return retKeys;
    }

    EXPORT_API keyCipher512 mlkemEncaps_512(uint8_t ek[800]) {
        std::vector<uint8_t> m = secureRandomBytes();

        std::vector<uint8_t> ekv(800); // Create a vector of the desired size

        std::memcpy(ekv.data(), ek, 800);
        auto [K, c] = kemEncapsInternal(ekv, m, Variants::MLKEM512);

        keyCipher512 retKeyCipher;
        std::memcpy(retKeyCipher.Key, K.data(), K.size());
        std::memcpy(retKeyCipher.c, c.data(), c.size());

        return retKeyCipher;
    }

    EXPORT_API Key mlkemDecaps_512(uint8_t dk[1632], uint8_t c[768]) {
        std::vector<uint8_t> dkv(1632); // Create a vector of the desired size
        std::vector<uint8_t> cv(768);
        std::memcpy(dkv.data(), dk, 1632);
        std::memcpy(cv.data(), c, 768);
        std::vector<uint8_t> K = kemDecapsInternal(dkv, cv, Variants::MLKEM512);

        Key key;
        std::memcpy(key.K, K.data(), K.size());

        return key;
    }

    EXPORT_API keys768 mlkemKeyGen_768() {
        std::vector<uint8_t> d = secureRandomBytes();
        std::vector<uint8_t> z = secureRandomBytes();
        auto [ek, dk] = kemKeyGenInternal(d, z, Variants::MLKEM768);

        keys768 retKeys;
        std::memcpy(retKeys.ek, ek.data(), ek.size());
        std::memcpy(retKeys.dk, dk.data(), dk.size());

        return retKeys;
    }

    EXPORT_API keyCipher768 mlkemEncaps_768(uint8_t ek[1184]) {
        std::vector<uint8_t> m = secureRandomBytes();

        std::vector<uint8_t> ekv(1184); // Create a vector of the desired size

        std::memcpy(ekv.data(), ek, 1184);
        auto [K, c] = kemEncapsInternal(ekv, m, Variants::MLKEM768);

        keyCipher768 retKeyCipher;
        std::memcpy(retKeyCipher.Key, K.data(), K.size());
        std::memcpy(retKeyCipher.c, c.data(), c.size());

        return retKeyCipher;
    }

    EXPORT_API Key mlkemDecaps_768(uint8_t dk[2400], uint8_t c[1088]) {
        std::vector<uint8_t> dkv(2400); // Create a vector of the desired size
        std::vector<uint8_t> cv(1088);
        std::memcpy(dkv.data(), dk, 2400);
        std::memcpy(cv.data(), c, 1088);
        std::vector<uint8_t> K = kemDecapsInternal(dkv, cv, Variants::MLKEM768);

        Key key;
        std::memcpy(key.K, K.data(), K.size());

        return key;
    }

    EXPORT_API keys1024 mlkemKeyGen_1024() {
        std::vector<uint8_t> d = secureRandomBytes();
        std::vector<uint8_t> z = secureRandomBytes();
        auto [ek, dk] = kemKeyGenInternal(d, z, Variants::MLKEM1024);

        keys1024 retKeys;
        std::memcpy(retKeys.ek, ek.data(), ek.size());
        std::memcpy(retKeys.dk, dk.data(), dk.size());

        return retKeys;
    }

    EXPORT_API keyCipher1024 mlkemEncaps_1024(uint8_t ek[1568]) {
        std::vector<uint8_t> m = secureRandomBytes();

        std::vector<uint8_t> ekv(1568); // Create a vector of the desired size

        std::memcpy(ekv.data(), ek, 1568);
        auto [K, c] = kemEncapsInternal(ekv, m, Variants::MLKEM1024);

        keyCipher1024 retKeyCipher;
        std::memcpy(retKeyCipher.Key, K.data(), K.size());
        std::memcpy(retKeyCipher.c, c.data(), c.size());

        return retKeyCipher;
    }

    EXPORT_API Key mlkemDecaps_1024(uint8_t dk[3168], uint8_t c[1568]) {
        std::vector<uint8_t> dkv(3168); // Create a vector of the desired size
        std::vector<uint8_t> cv(1568);
        std::memcpy(dkv.data(), dk, 3168);
        std::memcpy(cv.data(), c, 1568);
        std::vector<uint8_t> K = kemDecapsInternal(dkv, cv, Variants::MLKEM1024);

        Key key;
        std::memcpy(key.K, K.data(), K.size());

        return key;
    }
}
