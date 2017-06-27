#ifndef FSS_COMMON_H
#define FSS_COMMON_H


#include "openssl-aes.h"

#include <cpuid.h>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <stdint.h>
#include <string>

const int initPRFLen = 4;

struct Fss {
    // store keys in fixedBlocks
    AES_KEY* aes_keys;
    uint32_t m; // used only in multiparty. Default is 4
    uint32_t numBits; // number of bits in domain 
    mpz_class prime;
};

struct CWEq {
    unsigned char cs[2][16];
    unsigned char ct[2];
};

struct CWLt {
    unsigned char cs[2][16];
    unsigned char ct[2];
    uint64_t cv[2];
};

struct ServerKeyEq {
    unsigned char s[2][16];
    unsigned char t[2];
    CWEq* cw[2];
    mpz_class w;
};

struct ServerKeyLt {
    unsigned char s[2][16];
    unsigned char t[2];
    uint64_t v[2];
    CWLt* cw[2];
};

// Assumes integers are 64 bits
inline int getBit(uint64_t n, uint64_t pos) {
    int val = n & (1 << (64 - pos));
    if (val > 0) {
        return 1;
    } else {
        return 0;
    }
}

void prf(unsigned char* out, unsigned char* key, unsigned char* in, uint64_t in_size, AES_KEY* aes_keys);

#endif