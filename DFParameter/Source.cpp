#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <winerror.h>

#include <stdio.h>

#include <iostream>
using namespace std;

#include <openssl/crypto.h>
#include <openssl/cryptoerr.h>

#include <openssl/err.h>

#include <openssl/bio.h>
#include <openssl/bioerr.h>

#include <openssl/evp.h>
#include <openssl/evperr.h>

#include <openssl/bn.h>
#include <openssl/bnerr.h>

#include <openssl/ocsp.h>
#include <openssl/ocsperr.h>

#include <openssl/core_names.h>
#include <openssl/provider.h>

// https://openssl-users.openssl.narkive.com/94soUqQI/openssl-uplink-0099e000-07-no-openssl-applink
extern "C"
{
#undef APPMACROS_ONLY
#include <openssl/applink.c>
}

#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")
#pragma warning(disable : 4996)
void wmain()
{
	/*cout << SSLeay_version(SSLEAY_VERSION) << endl;
	EVP_CIPHER_CTX* pevpAESCBCEncCtx = NULL;
	pevpAESCBCEncCtx = EVP_CIPHER_CTX_new();

	unsigned char szKey[16] = { 0xAE, 0xF4, 0x00, 0x06, 0x88, 0xB9, 0xCA, 0xF6, 0xE9, 0xF2, 0x28, 0x1B, 0x59, 0x8B, 0x36, 0x94 };
	unsigned char szIV[16] = { 0xF0, 0xCE, 0xF9, 0x39, 0x2F, 0x94, 0xD1, 0xB8, 0x61, 0x12, 0x3B, 0xFE, 0x96, 0x87, 0x88, 0xE7 };
	//EVP_CIPHER_CTX_set_padding(pevpAESCBCCtx, 0); // By default padding is enabled
	EVP_CipherInit_ex(pevpAESCBCEncCtx, EVP_aes_128_cbc(), NULL, szKey, szIV, 1);
	//EVP_CIPHER_CTX_set_padding(pevpAESCBCCtx, 0); // By default padding is enabled
	//unsigned char szMsg[] = { "God is great all the time." };
	//unsigned char szMsg[] = { "God is good always & every time." };
	unsigned char szMsg[] =   { "0123456789abcdef0123456789" };

	cout << "Message:" << endl;
	cout << szMsg << endl;

	// Encryption
	unsigned char byCipher[48];
	int nCipherLen = 0;
	int nCipherTotLen = 0;
	EVP_CipherUpdate(pevpAESCBCEncCtx, byCipher, &nCipherLen, szMsg, strlen((const char*)szMsg));
	nCipherTotLen += nCipherLen;
	EVP_CipherFinal_ex(pevpAESCBCEncCtx, byCipher + nCipherTotLen, &nCipherLen);
	nCipherTotLen += nCipherLen;
	EVP_CIPHER_CTX_free(pevpAESCBCEncCtx);

	cout << "Encrypted message (padding enabled):" << endl;
	BIO_dump_fp(stdout, (const char*)byCipher, nCipherTotLen);


	// Decryption
	EVP_CIPHER_CTX* pEVPAESCBCDecCtx = NULL;
	pEVPAESCBCDecCtx = EVP_CIPHER_CTX_new();

	EVP_CipherInit_ex(pEVPAESCBCDecCtx, EVP_aes_128_cbc(), NULL, szKey, szIV, 0);
	//EVP_CIPHER_CTX_set_padding(pEVPAESCBCDecCtx, 0);
	unsigned char szCipherTemp[48];
	unsigned char szDMsg[48];
	int nDLen = 0;
	int nDTotLen = 0;
	//nCipherTotLen -= 0x10;
	bool nFound = false;
	//for(unsigned char szVal = 0; szVal < 255; szVal++)
	{
		EVP_CipherInit_ex(pEVPAESCBCDecCtx, EVP_aes_128_cbc(), NULL, szKey, szIV, 0);
		EVP_CIPHER_CTX_set_padding(pEVPAESCBCDecCtx, 0);
		memset(szDMsg, 0, 48);
		memcpy((void*)szCipherTemp, (const void*)byCipher, 48);
		nDLen = 0;
		nDTotLen = 0;
		//szCipherTemp[15] ^= (szVal ^ 0x01);
		//szCipherTemp[14] ^= (szVal ^ 0x02);
		//szCipherTemp[15] ^= ('f' ^ 0x02);
		if (1 == EVP_CipherUpdate(pEVPAESCBCDecCtx, szDMsg, &nDLen, szCipherTemp, nCipherTotLen))
		{
			//cout << (int)szVal << endl;
			nDTotLen += nDLen;
			if (1 == EVP_CipherFinal_ex(pEVPAESCBCDecCtx, szDMsg + nDTotLen, &nDLen))
			{
				nFound = true;
				//cout << szVal << endl;
				nDTotLen += nDLen;
				//break;
			}
		}
		EVP_CIPHER_CTX_reset(pEVPAESCBCDecCtx);
	}
	EVP_CIPHER_CTX_free(pEVPAESCBCDecCtx);

	if (nFound)
	{
		cout << "Decrypted message (padding disabled):" << endl;
		BIO_dump_fp(stdout, (const char*)szDMsg, nDTotLen);
	}*/

	// 1. Decrypt plain text and build the table for 2^56 possible keys..
	OSSL_PROVIDER* legacy;
	OSSL_PROVIDER* deflt;

	// * Load Multiple providers into the default (NULL) library context * /
	//legacy = OSSL_PROVIDER_load(NULL, "legacy");
	legacy = OSSL_PROVIDER_try_load(NULL, "legacy", 1);
	if (legacy == NULL) {
		printf("Failed to load Legacy provider\n");
		ERR_print_errors_fp(stdout);
		exit(EXIT_FAILURE);
	}
	//deflt = OSSL_PROVIDER_load(NULL, "default");
	deflt = OSSL_PROVIDER_try_load(NULL, "default", 1);
	if (deflt == NULL) {
		printf("Failed to load Default provider\n");
		ERR_print_errors_fp(stdout);
		OSSL_PROVIDER_unload(legacy);
		exit(EXIT_FAILURE);
	}

	// Use built-in parameters
	// EVP_PKEY* params1 = EVP_PKEY_new();
	// EVP_PKEY_assign(params1, EVP_PKEY_DH, DH_get_1024_160());

	// Create context for the key generation
	//EVP_PKEY_CTX* kctx = EVP_PKEY_CTX_new(params1, NULL);

	// Generate a new key
	//EVP_PKEY_keygen_init(kctx);
	//EVP_PKEY* dhkey = NULL;
	//EVP_PKEY_keygen(kctx, &dhkey);

	// Optional : useful if you want to check your private key
	//BIO* fp = BIO_new_fp(stdout, BIO_NOCLOSE);
	//EVP_PKEY_print_private(fp, dhkey, 0, NULL);
	//EVP_PKEY_print_public(fp, dhkey, 0, NULL);
	//BIGNUM* prime1 = NULL;
	//BIGNUM* generator1 = NULL;
	//EVP_PKEY_get_bn_param(dhkey, OSSL_PKEY_PARAM_FFC_P, &prime1);
	//EVP_PKEY_get_bn_param(dhkey, OSSL_PKEY_PARAM_FFC_G, &generator1);
	//cout << "p" << endl;
	//BN_print_fp(stdout, prime1);
	//cout << endl << "g" << endl;
	//BN_print_fp(stdout, generator1);

	//return;

	EVP_PKEY_CTX* pDHCtx = NULL;
	//pDHCtx = EVP_PKEY_CTX_new_from_name(NULL, "DH", NULL);
	pDHCtx = EVP_PKEY_CTX_new_id(EVP_PKEY_DH, NULL);
	EVP_PKEY_keygen_init(pDHCtx);
	EVP_PKEY* pkey = NULL;
	int priv_len = 1024;
	unsigned int priv_len1 = 1024;
	int gen = 5;
	OSSL_PARAM params[4];
	params[0] = OSSL_PARAM_construct_utf8_string(OSSL_PKEY_PARAM_GROUP_NAME, (char*)"ffdhe2048", 0);
	//params[0] = OSSL_PARAM_construct_utf8_string(OSSL_PKEY_PARAM_GROUP_NAME, (char*)"512", 0);
	//params[0] = OSSL_PARAM_construct_utf8_string(OSSL_PKEY_PARAM_GROUP_NAME, (char*)"ffdhe2048", 0);
	//params[1] = OSSL_PARAM_construct_utf8_string(OSSL_PKEY_PARAM_FFC_TYPE, (char*)OSSL_PKEY_PARAM_EC_GENERATOR, 0);
	//params[2] = OSSL_PARAM_construct_int(OSSL_PKEY_PARAM_DH_GENERATOR, &gen);
	/* "priv_len" is optional */
	params[1] = OSSL_PARAM_construct_int(OSSL_PKEY_PARAM_DH_PRIV_LEN, &priv_len);
	params[2] = OSSL_PARAM_construct_uint(OSSL_PKEY_PARAM_FFC_PBITS, &priv_len1);
	params[3] = OSSL_PARAM_construct_end();

	EVP_PKEY_keygen_init(pDHCtx);
	EVP_PKEY_CTX_set_params(pDHCtx, params);
	EVP_PKEY_generate(pDHCtx, &pkey);
	ERR_print_errors_fp(stdout);
	BIO* pBIO = BIO_new_fp(stdout, 0);
	EVP_PKEY_print_params(pBIO, pkey, 0, NULL);
	BIGNUM* prime = NULL;
	BIGNUM* generator = NULL;
	EVP_PKEY_get_bn_param(pkey, OSSL_PKEY_PARAM_FFC_P, &prime);
	EVP_PKEY_get_bn_param(pkey, OSSL_PKEY_PARAM_FFC_G, &generator);
	cout << "p" << endl;
	BN_print_fp(stdout, prime);
	cout << endl << "g" << endl;
	BN_print_fp(stdout, generator);
	EVP_PKEY_free(pkey);
	EVP_PKEY_CTX_free(pDHCtx);
}
