#include "mlkem_internal.h"
#include "kpke.h"
#include "samplePolyCBD.h"
#include "ntt.h"
#include "byteEncode.h"
#include "random.h"
#include "hash.h"
#include <iostream>
#include <vector>

/*
    Input: randomness d element of B^32
    Input: randomness z element of B^32
    Output: encapsulation key ek element of B^384k+32
    Output: decapsulation key dk element of B^768k+96
*/
void kemKeyGenInternal() {
    std::cout << "[INFO] ML-KEM.KeyGen_internal() called\n";
    // ekpke, dkpke <- K_PKE.KeyGen(d)
    kpkeKeyGen(); // Run kye generation for K-PKE

    // ek <- ekpke
    // dk <- (dkpke||ek||H(ek)||z)
    H(); // KEM decaps key includes PKE decryption key
    std::cout << "[INFO] ML-KEM.KeyGen_internal() completed\n";

    // return (ek, dk)
}

/*
    Input: encapsulation key ek element of B^384k+32
    Input: randomness m element of B^32
    Output: shared secret key K element of B^32
    Output: ciphertext c element of B^32(duk+dv)
*/
void kemEncapsInternal() {
    std::cout << "[INFO] ML-KEM.Encaps_internal() called\n";
    // (K, r) <- G(m||H(ek))
    G(); // Derive shared secret key K and randomness r

    // c <- K-PKE.Encrypt(ek, m, r)
    kpkeEncrypt(); // encrypt m using K-PKE with randomness r
    std::cout << "[INFO] ML-KEM.Encaps_internal() completed\n";

    // return (K, c)
}


/*
    Input: decapsulation key dk element of B^768k+96
    Input: ciphertext c element of B^32(duk+dv)
    Output: shared secret key K element of B^32
*/
void kemDecapsInternal() {
    std::cout << "[INFO] ML-KEM.Decaps_internal() called\n";

    // dkpke ← dk[0 ∶ 384k]
    // ekpke <- dk[384k: 768k + 32]
    // h <- dk[768k + 32 : 768k + 64]
    // z <- dk[768k + 64 : 768k + 96]
    // m' <- K-PKE.Derypt(dkpke, c)
    kpkeDecrypt(); // decrypt ciphertext

    // (K', r') <- G(m'||h)
    G();

    // K <- J(z||c)
    J();

    // c' <- K-PKE.Encrypt(epkpe, m', r')
    kpkeEncrypt(); // re-encrypt using the derived randomness r'
    
    // if c != c' then K' <- K
    std::cout << "[INFO] ML-KEM.Decaps_internal() completed\n";

    // return K'
}