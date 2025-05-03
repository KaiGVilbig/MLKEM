#include "mlkem_internal.h"
#include "kpke.h"
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
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> kemKeyGenInternal(std::vector<uint8_t> d, std::vector<uint8_t> z, Variants variant) {
    auto [ekpke, dkpke] = kpkeKeyGen(d, variant);

    std::vector<uint8_t> ek = ekpke;
    std::vector<uint8_t> dk;

    std::vector<uint8_t> hek = H(ek);

    dk.reserve(dkpke.size() + ek.size() + hek.size() + z.size());
    dk.insert(dk.end(), dkpke.begin(), dkpke.end());
    dk.insert(dk.end(), ek.begin(), ek.end());
    dk.insert(dk.end(), hek.begin(), hek.end());
    dk.insert(dk.end(), z.begin(), z.end());

    return {ek, dk};
}

/*
    Input: encapsulation key ek element of B^384k+32
    Input: randomness m element of B^32
    Output: shared secret key K element of B^32
    Output: ciphertext c element of B^32(duk+dv)
*/
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> kemEncapsInternal(std::vector<uint8_t> ek, std::vector<uint8_t> m, Variants variant) {
    std::vector<uint8_t> hek = H(ek);
    std::vector<uint8_t> mhek;
    mhek.reserve(m.size() + hek.size());
    mhek.insert(mhek.end(), m.begin(), m.end());
    mhek.insert(mhek.end(), hek.begin(), hek.end());
    auto [K, r] = G(mhek);

    std::vector<uint8_t> c = kpkeEncrypt(ek, m, r, variant);

    return { K, c };
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
    // kpkeDecrypt(); // decrypt ciphertext

    // (K', r') <- G(m'||h)
    // G();

    // K <- J(z||c)
    // J();

    // c' <- K-PKE.Encrypt(epkpe, m', r')
    // kpkeEncrypt(); // re-encrypt using the derived randomness r'
    
    // if c != c' then K' <- K
    std::cout << "[INFO] ML-KEM.Decaps_internal() completed\n";

    // return K'
}