#include "mlkem_internal.h"
#include "kpke.h"
#include "ntt.h"
#include "byteEncode.h"
#include "random.h"
#include "hash.h"
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
std::vector<uint8_t> kemDecapsInternal(std::vector<uint8_t> dk, std::vector<uint8_t> c, Variants variant) {
    int k = 0;
    switch (variant) {
        case Variants::MLKEM512:
            k = 2;
            break;
        case Variants::MLKEM768:
            k = 3;
            break;
        case Variants::MLKEM1024:
            k = 4;
            break;
        default:
            k = 2;
            break;
    }

    std::vector<uint8_t> dkpke(dk.begin(), dk.begin() + (384 * k));
    std::vector<uint8_t> ekpke(dk.begin() + (384 * k), dk.begin() + (768 * k) + 32);

    std::vector<uint8_t> h(dk.begin() + (768 * k) + 32, dk.begin() + (768 * k) + 64);
    std::vector<uint8_t> z(dk.begin() + (768 * k) + 64, dk.begin() + (768 * k) + 96);

    std::vector<uint8_t> m = kpkeDecrypt(dkpke, c, variant);
    std::vector<uint8_t> mh;
    mh.reserve(m.size() + h.size());
    mh.insert(mh.end(), m.begin(), m.end());
    mh.insert(mh.end(), h.begin(), h.end());
    auto [Kp, r] = G(mh);

    std::vector<uint8_t> zc;
    zc.reserve(z.size() + c.size());
    zc.insert(zc.end(), z.begin(), z.end());
    zc.insert(zc.end(), c.begin(), c.end());
    std::vector<uint8_t> K = J(zc);

    std::vector<uint8_t> cp = kpkeEncrypt(ekpke, m, r, variant);

    if (c != cp) {
        Kp = K;
    }

    return Kp;
}