#ifndef MLKEM_H
#define MLKEM_H

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __attribute__((visibility("default")))
#endif

#include <stdint.h>

struct keys512 {
    uint8_t ek[800];
    uint8_t dk[1632];
};

struct keys768 {
    uint8_t ek[1184];
    uint8_t dk[2400];
};

struct keys1024 {
    uint8_t ek[1568];
    uint8_t dk[3168];
};

struct keyCipher512 {
    uint8_t Key[32];
    uint8_t c[768];
};

struct keyCipher768 {
    uint8_t Key[32];
    uint8_t c[1088];
};

struct keyCipher1024 {
    uint8_t Key[32];
    uint8_t c[1568];
};

struct Key {
    uint8_t K[32];
};

extern "C" {
    EXPORT_API keys512 mlkemKeyGen_512();
    EXPORT_API keyCipher512 mlkemEncaps_512(uint8_t ek[800]);
    EXPORT_API Key mlkemDecaps_512(uint8_t dk[1632], uint8_t c[768]);

    EXPORT_API keys768 mlkemKeyGen_768();
    EXPORT_API keyCipher768 mlkemEncaps_768(uint8_t ek[1184]);
    EXPORT_API Key mlkemDecaps_768(uint8_t dk[2400], uint8_t c[1088]);

    EXPORT_API keys1024 mlkemKeyGen_1024();
    EXPORT_API keyCipher1024 mlkemEncaps_1024(uint8_t ek[1568]);
    EXPORT_API Key mlkemDecaps_1024(uint8_t dk[3168], uint8_t c[1568]);
}

#endif // MLKEM_H
