#ifndef MLKEM_H
#define MLKEM_H

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __attribute__((visibility("default")))
#endif

struct keys512 {
    char ek[800];
    char dk[1632];
};

struct keys768 {
    char ek[1184];
    char dk[2400];
};

struct keys1024 {
    char ek[1568];
    char dk[3168];
};

struct keyCipher512 {
    char Key[32];
    char c[768];
};

struct keyCipher768 {
    char Key[32];
    char c[1088];
};

struct keyCipher1024 {
    char Key[32];
    char c[1568];
};

struct Key {
    char K[32];
};

extern "C" {
    EXPORT_API keys512 mlkemKeyGen_512();
    EXPORT_API keyCipher512 mlkemEncaps_512(char ek[800]);
    EXPORT_API Key mlkemDecaps_512(char dk[1632], char c[768]);

    EXPORT_API keys768 mlkemKeyGen_768();
    EXPORT_API keyCipher768 mlkemEncaps_768(char ek[1184]);
    EXPORT_API Key mlkemDecaps_768(char dk[2400], char c[1088]);

    EXPORT_API keys1024 mlkemKeyGen_1024();
    EXPORT_API keyCipher1024 mlkemEncaps_1024(char ek[1568]);
    EXPORT_API Key mlkemDecaps_1024(char dk[3168], char c[1568]);
}

#endif // MLKEM_H
