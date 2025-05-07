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
    /// <summary>
    /// Generates an encapsulation key and a corresponding decapsulation key for ML-KEM512
    /// </summary>
    /// <returns>encapsulation key ek and decapsulation key dk</returns>
    EXPORT_API keys512 mlkemKeyGen_512();

    /// <summary>
    /// Uses the encapsulation key to generate a shared secret key and an associated ciphertext for ML-KEM512
    /// </summary>
    /// <param name="ek">encapsulation key ek</param>
    /// <returns>ciphertext c</returns>
    EXPORT_API keyCipher512 mlkemEncaps_512(uint8_t ek[800]);
    
    /// <summary>
    /// Uses the decapsulation key to produce a shared secret key from a ciphertext for ML-KEM512
    /// </summary>
    /// <param name="dk">decapsulation key dk</param>
    /// <param name="c">ciphertext c</param>
    /// <returns>shared secret key K</returns>
    EXPORT_API Key mlkemDecaps_512(uint8_t dk[1632], uint8_t c[768]);


    /// <summary>
    /// Generates an encapsulation key and a corresponding decapsulation key for ML-KEM768
    /// </summary>
    /// <returns>encapsulation key ek and decapsulation key dk</returns>
    EXPORT_API keys768 mlkemKeyGen_768();

    /// <summary>
    /// Uses the encapsulation key to generate a shared secret key and an associated ciphertext for ML-KEM768
    /// </summary>
    /// <param name="ek">encapsulation key ek</param>
    /// <returns>ciphertext c</returns>
    EXPORT_API keyCipher768 mlkemEncaps_768(uint8_t ek[1184]);
    
    /// <summary>
    /// Uses the decapsulation key to produce a shared secret key from a ciphertext for ML-KEM768
    /// </summary>
    /// <param name="dk">decapsulation key dk</param>
    /// <param name="c">ciphertext c</param>
    /// <returns>shared secret key K</returns>
    EXPORT_API Key mlkemDecaps_768(uint8_t dk[2400], uint8_t c[1088]);


    /// <summary>
    /// Generates an encapsulation key and a corresponding decapsulation key for ML-KEM1024
    /// </summary>
    /// <returns>encapsulation key ek and decapsulation key dk</returns>
    EXPORT_API keys1024 mlkemKeyGen_1024();

    /// <summary>
    /// Uses the encapsulation key to generate a shared secret key and an associated ciphertext for ML-KEM1024
    /// </summary>
    /// <param name="ek">encapsulation key ek</param>
    /// <returns>ciphertext c</returns>
    EXPORT_API keyCipher1024 mlkemEncaps_1024(uint8_t ek[1568]);
    
    /// <summary>
    /// Uses the decapsulation key to produce a shared secret key from a ciphertext for ML-KEM512
    /// </summary>
    /// <param name="dk">decapsulation key dk</param>
    /// <param name="c">ciphertext c</param>
    /// <returns>shared secret key K</returns>
    EXPORT_API Key mlkemDecaps_1024(uint8_t dk[3168], uint8_t c[1568]);
}

#endif // MLKEM_H
