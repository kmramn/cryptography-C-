
#include <Windows.h>
#include <winerror.h>

#include <stdio.h>

#include <iostream>
#include <chrono>
using namespace std;

#include <openssl/err.h>

#include <openssl/bio.h>
#include <openssl/bioerr.h>

#include <openssl/evp.h>
#include <openssl/evperr.h>

//#if defined(HAVE_OPENSSL)
#include <openssl/applink.c>
//#endif

#pragma comment (lib, "libssl.lib")
#pragma comment (lib, "libcrypto.lib")

int main()
{
    EVP_CIPHER_CTX* pAESCCBCEncipher = NULL;
    unsigned char szKey1[] = { 0x21, 0x9D, 0xA2, 0x97, 0x13, 0x0C, 0x3A, 0x3C, 0xCE, 0x37, 0x73, 0xEE, 0x7B, 0x2F, 0x6C, 0x4E };
    //unsigned char szMsg1[] = { "Pay Bob 1 doller" };
    unsigned char szMsg1[] = { "strongstpassword" };
    unsigned char szCipher1[32];
    int nCipherLen = 0;
    int nTotCipherLen = 0;

    pAESCCBCEncipher = EVP_CIPHER_CTX_new();
    EVP_EncryptInit(pAESCCBCEncipher, EVP_aes_128_cbc(), szKey1, NULL);
    EVP_CIPHER_CTX_set_padding(pAESCCBCEncipher, 0);
    EVP_EncryptUpdate(pAESCCBCEncipher, szCipher1, &nCipherLen, szMsg1, strlen((const char*)szMsg1));
    nTotCipherLen = nCipherLen;
    EVP_EncryptFinal(pAESCCBCEncipher, szCipher1 + nCipherLen, &nCipherLen);
    nTotCipherLen += nCipherLen;
    EVP_CIPHER_CTX_free(pAESCCBCEncipher);

    BIO_dump_fp(stdout, szCipher1, nTotCipherLen);

    EVP_CIPHER_CTX* pAESCBCDecCipher = NULL;
    unsigned char szDMsg1[16];
    int nDecMsgLen = 0;
    int nTotDecMsgLen = 0;
    unsigned char szKey2[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    //unsigned char szCipher2[32] = { 0x98, 0x8e, 0x73, 0x58, 0xd2, 0x38, 0x96, 0x39, 0x4a, 0xe3, 0x82, 0x29, 0xac, 0xd4, 0xd2, 0xff };
    unsigned char szCipher2[32] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    chrono::steady_clock::time_point start, finish;
    pAESCBCDecCipher = EVP_CIPHER_CTX_new();
    if (1 == EVP_DecryptInit(pAESCBCDecCipher, EVP_aes_128_cbc(), szKey1, NULL))
    //if (1 == EVP_DecryptInit(pAESCBCDecCipher, EVP_aes_128_cbc(), szKey2, NULL))
    {
        EVP_CIPHER_CTX_set_padding(pAESCBCDecCipher, 0);
        int nRet = 0;
        //nRet = EVP_DecryptUpdate(pAESCBCDecCipher, szDMsg1, &nDecMsgLen, szCipher, nTotCipherLen);
        nRet = EVP_DecryptUpdate(pAESCBCDecCipher, szDMsg1, &nDecMsgLen, szCipher1, nTotCipherLen);
        if (0 == nRet)
        {
            cout << "Failed" << endl;
            goto AECCBC_End;
        }
        nTotDecMsgLen = nDecMsgLen;
        EVP_DecryptFinal(pAESCBCDecCipher, szDMsg1 + nDecMsgLen, &nDecMsgLen);
        nTotDecMsgLen += nDecMsgLen;
    }
    EVP_CIPHER_CTX_free(pAESCBCDecCipher);

    start = chrono::high_resolution_clock::now();
    if (0 == memcmp(szCipher1, szCipher2, 16))
    {
        // Send success message.
        cout << "Success!" << endl;
    }
    else
    {
        // Send failuer message.
        cout << "Failed!" << endl;
    }
    finish = chrono::high_resolution_clock::now();
AECCBC_End:
    BIO_dump_fp(stdout, szDMsg1, nTotDecMsgLen);
    cout << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() << " nano seconds" << endl;

    return 0;
}