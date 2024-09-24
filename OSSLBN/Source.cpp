#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <winerror.h>

#include <stdio.h>

#include <iostream>
using namespace std;

#include <openssl/err.h>

#include <openssl/bio.h>
#include <openssl/bioerr.h>

#include <openssl/bn.h>
#include <openssl/bnerr.h>

#include <openssl/rand.h>
#include <openssl/randerr.h>

#include <openssl/applink.c>

#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")

void wmain()
{
    BIGNUM* p = BN_new();
    BIGNUM* q = BN_new();

    BN_hex2bn(&p, (const char*)"123456789abcdef");
    BN_rand(p, 3, 0, 7);
    RAND_seed()
    BN_generate_prime_ex(p, 3, 0, NULL, NULL, NULL);
    BN_print_fp(stdout, p);

    BN_free(q);
    BN_free(p);
}