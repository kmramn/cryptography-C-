
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>

#include <iostream>
using namespace std;

#include <stdio.h>

#include <openssl/evp.h>
//#include <openssl/crypto.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/x509.h>

// https://openssl-users.openssl.narkive.com/94soUqQI/openssl-uplink-0099e000-07-no-openssl-applink
extern "C"
{
#undef APPMACROS_ONLY
#include <openssl/applink.c>
}
#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")

void main()
{
    EVP_MD_CTX* ctx;
    ctx = EVP_MD_CTX_new();
    EVP_MD* sha256;
    sha256 = EVP_MD_fetch(NULL, "sha256", NULL);
    EVP_DigestInit_ex(ctx, sha256, NULL);
    char msg[] = { 0x01, 0x02, 0x03, 0x05 };
    EVP_DigestUpdate(ctx, msg, sizeof(msg));
    unsigned char* dig = (unsigned char*)OPENSSL_malloc(EVP_MD_get_size(sha256));
    unsigned int len = 0;
    EVP_DigestFinal_ex(ctx, dig, &len);
    BIO_dump_fp(stdout, dig, len);
    OPENSSL_free(dig);
    EVP_MD_free(sha256);
    EVP_MD_CTX_free(ctx);
    /*EVP_MD_CTX* ctx = NULL;
    EVP_MD* sha256 = NULL;
    const unsigned char msg[] = {
        0x00, 0x01, 0x02, 0x03
    };
    unsigned int len = 0;
    unsigned char* outdigest = NULL;
    int ret = 1;

    // Create a context for the digest operation
    ctx = EVP_MD_CTX_new();
    if (ctx == NULL)
        goto err;

    //*
    // * Fetch the SHA256 algorithm implementation for doing the digest. We're
    // * using the "default" library context here (first NULL parameter), and
    // * we're not supplying any particular search criteria for our SHA256
    // * implementation (second NULL parameter). Any SHA256 implementation will
    // * do.
    // *
    sha256 = EVP_MD_fetch(NULL, "SHA256", NULL);
    if (sha256 == NULL)
        goto err;

    // Initialise the digest operation
    if (!EVP_DigestInit_ex(ctx, sha256, NULL))
        goto err;

    //*
    // * Pass the message to be digested. This can be passed in over multiple
    // * EVP_DigestUpdate calls if necessary
    // *
    if (!EVP_DigestUpdate(ctx, msg, sizeof(msg)))
        goto err;

    // Allocate the output buffer
    outdigest = (unsigned char*)OPENSSL_malloc(EVP_MD_get_size(sha256));
    if (outdigest == NULL)
        goto err;

    // Now calculate the digest itself
    if (!EVP_DigestFinal_ex(ctx, outdigest, &len))
        goto err;

    // Print out the digest result
    BIO_dump_fp(stdout, outdigest, len);

    ret = 0;

err:
    // Clean up all the resources we allocated
    OPENSSL_free(outdigest);
    EVP_MD_free(sha256);
    EVP_MD_CTX_free(ctx);
    if (ret != 0)
        ERR_print_errors_fp(stderr);
    return;*/
}
