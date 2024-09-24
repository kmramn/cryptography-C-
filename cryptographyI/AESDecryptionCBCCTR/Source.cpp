/*
Question 1
In this project you will implement two encryption/decryption systems, 
one using AES in CBC mode and another using AES in counter mode (CTR).
In both cases the 16-byte encryption IV is chosen at random and is prepended
to the ciphertext.

For CBC encryption we use the PKCS5 padding scheme discussed  in the lecture (14:04).
While we ask that you implement both encryption and decryption,
we will only test the decryption function. In the following questions you are
given an AES key and a ciphertext (both are  hex encoded ) and your goal
is to recover the plaintext and enter it in the input boxes provided below.

For an implementation of AES you may use an existing crypto library such as
PyCrypto  (Python), Crypto++  (C++), or any other. While it is fine to use
the built-in AES functions, we ask that as a learning experience you implement
CBC and CTR modes yourself.

Question 1
    CBC key: 140b41b22a29beb4061bda66b6747e14
    CBC Ciphertext 1: 4ca00ff4c898d61e1edbf1800618fb2828a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c6822236e1daafb94ffe0c5da05d9476be028ad7c1d81

Question 2
    CBC key: 140b41b22a29beb4061bda66b6747e14
    CBC Ciphertext 2: 5b68629feb8606f9a6667670b75b38a5b4832d0f26e1ab7da33249de7d4afc48e713ac646ace36e872ad5fb8a512428a6e21364b0c374df45503473c5242a253

Question 3
    CTR key: 36f18357be4dbd77f050515c73fcf9f2
    CTR Ciphertext 1: 69dda8455c7dd4254bf353b773304eec0ec7702330098ce7f7520d1cbbb20fc388d1b0adb5054dbd7370849dbf0b88d393f252e764f1f5f7ad97ef79d59ce29f5f51eeca32eabedd9afa9329

Question 4
    CTR key: 36f18357be4dbd77f050515c73fcf9f2
    CTR Ciphertext 2: 770b80259ec33beb2561358a9f2dc617e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451

*/
#include <Windows.h>
#include <Winerror.h>
#include <tchar.h>
#include <strsafe.h>

#include <stdio.h>
#include <iostream>
using namespace std;

#include <wincrypt.h>
#pragma comment(lib, "advapi32.lib")

void INCREMENTIV(unsigned char arr1[])
{
    for(int i = 15; i >= 0; i--)
    {
        arr1[i]++;
        if (arr1[i] != 0)
            break;
    }
}

int VALUELEN(unsigned char arr1[])
{
    int nLen = 0;
    for (int i = 0; i < 1024 - 1; i++)
    {
        if (arr1[i] == 0 && arr1[i + 1] == 0)
            break;
        nLen++;
    }

    return nLen;
}

void XORTWOVALUE(unsigned char xored[], unsigned char arr1[], unsigned char arr2[], int len)
{
    unsigned char mm[1024];
    SecureZeroMemory(mm, sizeof(mm));
    for (int i = 0; i < len; i++)
        xored[i] = arr1[i] ^ arr2[i];
}

void wmain()
{
    unsigned char szKey[4][16] = {
        { 0x14, 0x0b, 0x41, 0xb2, 0x2a, 0x29, 0xbe, 0xb4, 0x06, 0x1b, 0xda, 0x66, 0xb6, 0x74, 0x7e, 0x14 },
        { 0x14, 0x0b, 0x41, 0xb2, 0x2a, 0x29, 0xbe, 0xb4, 0x06, 0x1b, 0xda, 0x66, 0xb6, 0x74, 0x7e, 0x14 },
        { 0x36, 0xf1, 0x83, 0x57, 0xbe, 0x4d, 0xbd, 0x77, 0xf0, 0x50, 0x51, 0x5c, 0x73, 0xfc, 0xf9, 0xf2 },
        { 0x36, 0xf1, 0x83, 0x57, 0xbe, 0x4d, 0xbd, 0x77, 0xf0, 0x50, 0x51, 0x5c, 0x73, 0xfc, 0xf9, 0xf2 }
    };

    unsigned char szCT[4][80] = {
        { 0x4c, 0xa0, 0x0f, 0xf4, 0xc8, 0x98, 0xd6, 0x1e, 0x1e, 0xdb, 0xf1, 0x80, 0x06, 0x18, 0xfb, 0x28, 0x28, 0xa2, 0x26, 0xd1, 0x60, 0xda, 0xd0, 0x78, 0x83, 0xd0, 0x4e, 0x00, 0x8a, 0x78, 0x97, 0xee, 0x2e, 0x4b, 0x74, 0x65, 0xd5, 0x29, 0x0d, 0x0c, 0x0e, 0x6c, 0x68, 0x22, 0x23, 0x6e, 0x1d, 0xaa, 0xfb, 0x94, 0xff, 0xe0, 0xc5, 0xda, 0x05, 0xd9, 0x47, 0x6b, 0xe0, 0x28, 0xad, 0x7c, 0x1d, 0x81 },
        { 0x5b, 0x68, 0x62, 0x9f, 0xeb, 0x86, 0x06, 0xf9, 0xa6, 0x66, 0x76, 0x70, 0xb7, 0x5b, 0x38, 0xa5, 0xb4, 0x83, 0x2d, 0x0f, 0x26, 0xe1, 0xab, 0x7d, 0xa3, 0x32, 0x49, 0xde, 0x7d, 0x4a, 0xfc, 0x48, 0xe7, 0x13, 0xac, 0x64, 0x6a, 0xce, 0x36, 0xe8, 0x72, 0xad, 0x5f, 0xb8, 0xa5, 0x12, 0x42, 0x8a, 0x6e, 0x21, 0x36, 0x4b, 0x0c, 0x37, 0x4d, 0xf4, 0x55, 0x03, 0x47, 0x3c, 0x52, 0x42, 0xa2, 0x53 },
        { 0x69, 0xdd, 0xa8, 0x45, 0x5c, 0x7d, 0xd4, 0x25, 0x4b, 0xf3, 0x53, 0xb7, 0x73, 0x30, 0x4e, 0xec, 0x0e, 0xc7, 0x70, 0x23, 0x30, 0x09, 0x8c, 0xe7, 0xf7, 0x52, 0x0d, 0x1c, 0xbb, 0xb2, 0x0f, 0xc3, 0x88, 0xd1, 0xb0, 0xad, 0xb5, 0x05, 0x4d, 0xbd, 0x73, 0x70, 0x84, 0x9d, 0xbf, 0x0b, 0x88, 0xd3, 0x93, 0xf2, 0x52, 0xe7, 0x64, 0xf1, 0xf5, 0xf7, 0xad, 0x97, 0xef, 0x79, 0xd5, 0x9c, 0xe2, 0x9f, 0x5f, 0x51, 0xee, 0xca, 0x32, 0xea, 0xbe, 0xdd, 0x9a, 0xfa, 0x93, 0x29 },
        { 0x77, 0x0b, 0x80, 0x25, 0x9e, 0xc3, 0x3b, 0xeb, 0x25, 0x61, 0x35, 0x8a, 0x9f, 0x2d, 0xc6, 0x17, 0xe4, 0x62, 0x18, 0xc0, 0xa5, 0x3c, 0xbe, 0xca, 0x69, 0x5a, 0xe4, 0x5f, 0xaa, 0x89, 0x52, 0xaa, 0x0e, 0x31, 0x1b, 0xde, 0x9d, 0x4e, 0x01, 0x72, 0x6d, 0x31, 0x84, 0xc3, 0x44, 0x51 }
    };

    unsigned char szKe1[] = {
        PLAINTEXTKEYBLOB, CUR_BLOB_VERSION, 0x00, 0x00, 0x0E, 0x66, 0x00, 0x00,
        0x10, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    unsigned char szKeyIV[16] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    unsigned char szM[4][80];
    SecureZeroMemory(szM, sizeof(szM));
    unsigned char szIV[16];
    SecureZeroMemory(szIV, sizeof(szIV[0]));
    //wprintf(L"%d-%u-%u-%u\n", sizeof(szM[0]), _countof(szM[0]), sizeof(szKe1), sizeof(WORD));

    BOOL bRet = FALSE;

    HCRYPTPROV hCryptProv = NULL;
    bRet = CryptAcquireContext(&hCryptProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES,
        CRYPT_VERIFYCONTEXT);
    //bRet = CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    if (bRet == FALSE)
    {
        return;
    }

    HCRYPTKEY hCryptKey = NULL;
    for (int j = 0; j < 2; j++)
    {
        memcpy(szIV, szCT[j], 16);
        memcpy(szM[j], szCT[j] + 16, sizeof(szCT[j]) - 16);
        DWORD dwDataLen = VALUELEN(szM[j]);

        for (int i = 0; i < ((dwDataLen / 16) + ((dwDataLen % 16) ? 1 : 0)); i++)
        {
            memcpy(szKe1 + 12, szKey[j], 16); // Since both keys are same.
            hCryptKey = NULL;
            bRet = CryptImportKey(hCryptProv, szKe1, sizeof(szKe1), 0, 0, &hCryptKey);
            if (bRet == FALSE)
            {
                bRet = CryptReleaseContext(hCryptProv, 0);
                hCryptProv = NULL;
                return;
            }

            DWORD dwDataDecLen = 16;
            bRet = CryptDecrypt(hCryptKey, 0, FALSE, 0, szM[j] + i * 16, &dwDataDecLen);
            if (bRet == FALSE)
            {
                CryptDestroyKey(hCryptKey);
                hCryptKey = NULL;
                CryptReleaseContext(hCryptProv, 0);
                hCryptProv = NULL;
                return;
            }

            bRet = CryptDestroyKey(hCryptKey);
        }

        for (int i = 0; i < dwDataLen; i++)
        {
            //if (i / 16 == 0)
            //    szM[j][i] ^= szIV[i];
            //else
                szM[j][i] ^= szCT[j][i];
        }
    }

    for (int j = 2; j < 4; j++)
    {
        memcpy(szIV, szCT[j], 16);
        DWORD dwDataLen = VALUELEN(szCT[j]);

        //int i = 0;
        for (int i = 0; i < ((dwDataLen / 16) + ((dwDataLen % 16) ? 1 : 0)); i++)
        {
            memcpy(szKe1 + 12, szKey[j], 16); // Since both keys are same.
            hCryptKey = NULL;
            bRet = CryptImportKey(hCryptProv, szKe1, sizeof(szKe1), 0, 0, &hCryptKey);
            if (bRet == FALSE)
            {
                bRet = CryptReleaseContext(hCryptProv, 0);
                hCryptProv = NULL;
                return;
            }

            memcpy(szM[j] + i * 16, szIV, sizeof(szIV));
            DWORD dwDataDecLen = 16;
            DWORD dwDataDecLenOrig = 16;
            bRet = CryptEncrypt(hCryptKey, 0, FALSE, 0, szM[j] + i * 16, &dwDataDecLen, dwDataDecLenOrig);
            if (bRet == FALSE)
            {
                CryptDestroyKey(hCryptKey);
                hCryptKey = NULL;
                CryptReleaseContext(hCryptProv, 0);
                hCryptProv = NULL;
                return;
            }

            for (int k = 0; k < 16; k++)
            {
                szM[j][i * 16 + k] ^= szCT[j][(i * 16 + k) + 16];
            }

            INCREMENTIV(szIV);
            bRet = CryptDestroyKey(hCryptKey);
        }

    }

CreptReleas:
    if (hCryptKey != NULL)
        CryptDestroyKey(hCryptKey);
    if (hCryptProv != NULL)
        bRet = CryptReleaseContext(hCryptProv, 0);
}
