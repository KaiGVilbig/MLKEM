#ifndef XOF_H
#define XOF_H

#include <vector>
#include <cstdint>
#include <openssl/evp.h>

class XOF {
public:
    XOF();  // Constructor
    ~XOF(); // Destructor

    void init();
    void absorb(const std::vector<uint8_t> input);
    std::vector<uint8_t> squeeze(size_t n);

private:
    EVP_MD_CTX* ctx;
};

#endif // XOF_H
