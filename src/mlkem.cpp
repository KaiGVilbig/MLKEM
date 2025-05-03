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
        auto [ekh, dkh] = kemKeyGenInternal(d, z, Variants::MLKEM512);

        std::string ek = toHex(ekh);
        std::string dk = toHex(dkh);

        keys512 retKeys;
        strcpy_s(retKeys.ek, ek.c_str());
        strcpy_s(retKeys.dk, dk.c_str());

        return retKeys;
    }

    EXPORT_API keyCipher512 mlkemEncaps_512(char ek[800]) {
        std::vector<uint8_t> m = secureRandomBytes();

        std::vector<uint8_t> ekv(800); // Create a vector of the desired size

        std::memcpy(ekv.data(), ek, 800);
        auto [Kh, ch] = kemEncapsInternal(ekv, m, Variants::MLKEM512);

        std::string K = toHex(Kh);
        std::string c = toHex(ch);

        keyCipher512 retKeyCipher;
        strcpy_s(retKeyCipher.Key, K.c_str());
        strcpy_s(retKeyCipher.c, c.c_str());

        return retKeyCipher;
    }

    EXPORT_API Key mlkemDecaps_512(char dk[1632], char c[768]) {
        std::vector<uint8_t> dkv(1632); // Create a vector of the desired size
        std::vector<uint8_t> cv(768);
        std::memcpy(dkv.data(), dk, 1632);
        std::memcpy(cv.data(), c, 768);
        std::vector<uint8_t> Kv = kemDecapsInternal(dkv, cv, Variants::MLKEM512);

        std::string K = toHex(Kv);

        Key key;
        strcpy_s(key.K, K.c_str());

        return key;
    }

    EXPORT_API keys768 mlkemKeyGen_768() {
        std::vector<uint8_t> d = secureRandomBytes();
        std::vector<uint8_t> z = secureRandomBytes();
        auto [ekh, dkh] = kemKeyGenInternal(d, z, Variants::MLKEM768);

        std::string ek = toHex(ekh);
        std::string dk = toHex(dkh);

        keys768 retKeys;
        strcpy_s(retKeys.ek, ek.c_str());
        strcpy_s(retKeys.dk, dk.c_str());

        return retKeys;
    }

    EXPORT_API keyCipher768 mlkemEncaps_768(char ek[1184]) {
        std::vector<uint8_t> m = secureRandomBytes();

        std::vector<uint8_t> ekv(1184); // Create a vector of the desired size

        std::memcpy(ekv.data(), ek, 1184);
        auto [Kh, ch] = kemEncapsInternal(ekv, m, Variants::MLKEM512);

        std::string K = toHex(Kh);
        std::string c = toHex(ch);

        keyCipher768 retKeyCipher;
        strcpy_s(retKeyCipher.Key, K.c_str());
        strcpy_s(retKeyCipher.c, c.c_str());

        return retKeyCipher;
    }

    EXPORT_API Key mlkemDecaps_768(char dk[2400], char c[1088]) {
        std::vector<uint8_t> dkv(2400); // Create a vector of the desired size
        std::vector<uint8_t> cv(1088);
        std::memcpy(dkv.data(), dk, 2400);
        std::memcpy(cv.data(), c, 1088);
        std::vector<uint8_t> Kv = kemDecapsInternal(dkv, cv, Variants::MLKEM512);

        std::string K = toHex(Kv);

        Key key;
        strcpy_s(key.K, K.c_str());

        return key;
    }

    EXPORT_API keys1024 mlkemKeyGen_1024() {
        std::vector<uint8_t> d = secureRandomBytes();
        std::vector<uint8_t> z = secureRandomBytes();
        auto [ekh, dkh] = kemKeyGenInternal(d, z, Variants::MLKEM1024);

        std::string ek = toHex(ekh);
        std::string dk = toHex(dkh);

        keys1024 retKeys;
        strcpy_s(retKeys.ek, ek.c_str());
        strcpy_s(retKeys.dk, dk.c_str());

        return retKeys;
    }

    EXPORT_API keyCipher1024 mlkemEncaps_1024(char ek[1568]) {
        std::vector<uint8_t> m = secureRandomBytes();

        std::vector<uint8_t> ekv(1568); // Create a vector of the desired size

        std::memcpy(ekv.data(), ek, 1568);
        auto [Kh, ch] = kemEncapsInternal(ekv, m, Variants::MLKEM512);

        std::string K = toHex(Kh);
        std::string c = toHex(ch);

        keyCipher1024 retKeyCipher;
        strcpy_s(retKeyCipher.Key, K.c_str());
        strcpy_s(retKeyCipher.c, c.c_str());

        return retKeyCipher;
    }

    EXPORT_API Key mlkemDecaps_1024(char dk[3168], char c[1568]) {
        std::vector<uint8_t> dkv(3168); // Create a vector of the desired size
        std::vector<uint8_t> cv(1568);
        std::memcpy(dkv.data(), dk, 3168);
        std::memcpy(cv.data(), c, 1568);
        std::vector<uint8_t> Kv = kemDecapsInternal(dkv, cv, Variants::MLKEM512);

        std::string K = toHex(Kv);

        Key key;
        strcpy_s(key.K, K.c_str());

        return key;
    }
}
