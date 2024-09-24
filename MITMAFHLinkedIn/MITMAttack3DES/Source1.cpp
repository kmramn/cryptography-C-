
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <cmath>

#include <ppl.h>
#include <pplcancellation_token.h>
using namespace concurrency;

#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <chrono>
#include <atomic>
#include <mutex>
using namespace std;


//OpenSSL library
#include <openssl/provider.h>

#include <openssl/err.h>

#include <openssl/bio.h>
#include <openssl/bioerr.h>

#include <openssl/evp.h>
#include <openssl/evperr.h>

#include <openssl/des.h>

// https://openssl-users.openssl.narkive.com/94soUqQI/openssl-uplink-0099e000-07-no-openssl-applink
extern "C"
{
#undef APPMACROS_ONLY
#include <openssl/applink.c>
}

#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")

class PRTimer
{
	chrono::steady_clock m_sc;
	chrono::steady_clock::time_point m_start;
public:
	//mpz_class m_x;
	vector<unsigned char> m_x;
	PRTimer()
	{
		m_start = m_sc.now();
	}

	~PRTimer()
	{
		chrono::steady_clock::time_point end = m_sc.now();
		auto time_span = static_cast<chrono::duration<double>>(end - m_start);
		//if (m_x != 0)
		//    cout << "x = " << m_x.get_str() << " Operation Finished. It took: " << time_span.count() << " seconds !!!" << endl;
		//else
		cout << "Operation Finished. It took: " << time_span.count() << " seconds !!!" << endl;
	}
};

void SetOddParity(unsigned char& szKey)
{
	szKey &= 127;
	unsigned char k0 = ((szKey) & 1);
	unsigned char k1 = ((szKey >> 1) & 1);
	unsigned char k2 = ((szKey >> 2) & 1);
	unsigned char k3 = ((szKey >> 3) & 1);
	unsigned char k4 = ((szKey >> 4) & 1);
	unsigned char k5 = ((szKey >> 5) & 1);
	unsigned char k6 = ((szKey >> 6) & 1);
	unsigned char k8 = k0 ^ k1 ^ k2 ^ k3 ^ k4 ^ k5 ^ k6 ^ 1;
	szKey = szKey | (k8 << 7);
}

// Add 56 bit key staored in a 64 bit value. In every byte the most-siggnificant bit
// is a odd parity bit. Assuming the intial value of szKeys is all 0'1
void Add56BitKey(unsigned char szKeys[8], uint64_t nVal)
{
	szKeys[7] = nVal % 128;
	SetOddParity(szKeys[7]);
	nVal = nVal / 128;
	szKeys[6] = nVal % 128;
	SetOddParity(szKeys[6]);
	nVal = nVal / 128;
	szKeys[5] = nVal % 128;
	SetOddParity(szKeys[5]);
	nVal = nVal / 128;
	szKeys[4] = nVal % 128;
	SetOddParity(szKeys[4]);
	nVal = nVal / 128;
	szKeys[3] = nVal % 128;
	SetOddParity(szKeys[3]);
	nVal = nVal / 128;
	szKeys[2] = nVal % 128;
	SetOddParity(szKeys[2]);
	nVal = nVal / 128;
	szKeys[1] = nVal % 128;
	SetOddParity(szKeys[1]);
	nVal = nVal / 128;
	szKeys[0] = nVal % 128;
	SetOddParity(szKeys[0]);
	nVal = nVal / 128;
}

struct mpzComp
{
	bool operator()(const vector<unsigned char>& lhs, pair<vector<unsigned char>, vector<unsigned char>>& rhs)
	{
		if (lhs < rhs.first)
			return true;
		return false;
	}
	bool operator()(const pair<vector<unsigned char>, vector<unsigned char>>& lhs, const vector<unsigned char>& rhs)
	{
		if (lhs.first < rhs)
			return true;
		return false;
	}
};

int main()
{
	// Decrypted value id obtained by encrypting plain text using 3DES ede3 ECB.
	// 3DES - 3 Data Encryption Standard
	// ede3 - Encrypt, Decrypt and Encrypt using 3 key.
	// ECB - Electronic Code book.
	// The cipher algritham in OpenSSL is EVP_des_ede3_ecb()
	// sz3DESEncData1 = E_K3(D_K2(E_K1(PlainText)))
	unsigned char szPlainText1[] = { "Hello" };
	unsigned char sz3DESEncData1[] = { 0xdf, 0x2b, 0xfb, 0x05, 0x16, 0x39, 0xdc, 0xa6 };
	int n3DESEncDataLen1 = 8;
	unsigned char szPlainText2[] = { "Over" };
	unsigned char sz3DESEncData2[] = { 0x02, 0x44, 0x23, 0xd8, 0x2b, 0x3c, 0x0d, 0x17 };
	int n3DESEncDataLen2 = 8;

	unsigned char szKey1[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned char szKey2[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned char szKey3[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned char szKey4[24] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	// For Meet-In-The-Middle Attack the following should match
	// D_K3(sz3DESEncData1) = (D_K2(E_K1(PlainText1)))

	//typedef vector<pair<vector<unsigned char>, vector<unsigned char>>> H2TABLE;
	typedef deque<pair<vector<unsigned char>, vector<unsigned char>>> H2TABLE;
	H2TABLE h2t;

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

	unsigned long long llMax1 = pow(2, 56);
	{
		PRTimer prTimer;
		cout << "Resizing h table...! of size " << llMax1 << endl;
		h2t.resize(llMax1);
	}
	EVP_CIPHER_CTX* plhsDecryptCtx1 = NULL;
	plhsDecryptCtx1 = EVP_CIPHER_CTX_new();
	unsigned long long x2 = 0;
	{
		PRTimer prTimer;
		cout << "Building h table...! of size " << llMax1 << endl;

		cancellation_token_source cts;
		run_with_cancellation_token([llMax1, &h2t, &plhsDecryptCtx1, sz3DESEncData1, n3DESEncDataLen1, &prTimer, &cts]()
		{
			parallel_for((unsigned long long)0, llMax1, (unsigned long long)1, [&h2t, &plhsDecryptCtx1,
				sz3DESEncData1, n3DESEncDataLen1, &prTimer, &cts](unsigned long long index3)
			{
				unsigned char szKey3Temp[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
				EVP_DecryptInit(plhsDecryptCtx1, EVP_des_ecb(), szKey3Temp, NULL);
				EVP_CIPHER_CTX_set_padding(plhsDecryptCtx1, 0);

				int nlhsDecLen1 = 0;
				int nlhsTotDecLen1 = 0;
				unsigned char szlhsDecBuff1[8];
				if (1 == EVP_DecryptUpdate(plhsDecryptCtx1, szlhsDecBuff1, &nlhsDecLen1, sz3DESEncData1, n3DESEncDataLen1))
				{
					nlhsTotDecLen1 = nlhsDecLen1;
					EVP_DecryptFinal(plhsDecryptCtx1, szlhsDecBuff1, &nlhsDecLen1);
					nlhsTotDecLen1 += nlhsDecLen1;

					// Build a table
					//BIO_dump_fp(stdout, (const char*)szlhsDecBuff1, nlhsTotDecLen1);
					vector<unsigned char> vlhsDecBuff1(begin(szlhsDecBuff1), end(szlhsDecBuff1));
					vector<unsigned char> vlhsDecKey3(begin(szKey3Temp), end(szKey3Temp));
					h2t[index3] = make_pair<>(vlhsDecBuff1, vlhsDecKey3);
				}

				// TODO: Add key with the index
				Add56BitKey(szKey3Temp, index3);
			});
		}, cts.get_token());

		cout << "Finish building h table...! of size " << llMax1 << endl;
	}
	EVP_CIPHER_CTX_free(plhsDecryptCtx1);

	{
		PRTimer prTimer;
		cout << "Sorting h table...! of size " << llMax1 << endl;

		std::sort(h2t.begin(), h2t.end());

		cout << "Finish sorting h table...! of size " << llMax1 << endl;
	}

	// 2.Search the constructed table for evey possible 2^112 keys.
	EVP_CIPHER_CTX* prhsDecryptCtx3 = NULL;
	prhsDecryptCtx3 = EVP_CIPHER_CTX_new();
	EVP_CIPHER_CTX* prhsDecryptCtx2 = NULL;
	prhsDecryptCtx2 = EVP_CIPHER_CTX_new();
	int nPlainTextLen1 = strlen((const char*)szPlainText1);
	nPlainTextLen1++; // Include NULL
	int nComp = 1;

	{
		PRTimer prTimer;
		cout << "Search h table using g...!" << endl;

		unsigned char szrhsDecBuff3[8];
		int nrhsDecLen3 = 0;
		int nrhsTotDecLen3 = 0;

		unsigned char szrhsDecBuff2[8];
		int nrhsDecLen2 = 0;
		int nrhsTotDecLen2 = 0;

		cancellation_token_source cts;
		run_with_cancellation_token([llMax1, &h2t, prhsDecryptCtx3, prhsDecryptCtx2,
			&szrhsDecBuff3, &nrhsDecLen3, &szrhsDecBuff2, &nrhsDecLen2, &szPlainText1, &nPlainTextLen1,
			&nrhsTotDecLen3, &nrhsTotDecLen2, &szKey1, &szKey2, &szKey3, &nComp,
			&cts]()
		{
			uint64_t j = 0;
			parallel_for((uint64_t)0, llMax1, (uint64_t)1, [llMax1, &h2t, prhsDecryptCtx3, prhsDecryptCtx2,
				&szrhsDecBuff3, &nrhsDecLen3, &szrhsDecBuff2, &nrhsDecLen2, &szPlainText1, &nPlainTextLen1,
				&nrhsTotDecLen3, &nrhsTotDecLen2, &szKey1, &szKey2, &szKey3, &nComp, &cts](uint64_t index1)
			{
				//cout << "First parallel for loop" << endl;
				unsigned char szKey1Temp[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
				// TODO: Increment key with index
				Add56BitKey(szKey1Temp, index1);
				EVP_EncryptInit(prhsDecryptCtx3, EVP_des_ecb(), szKey1Temp, NULL);
				EVP_EncryptUpdate(prhsDecryptCtx3, szrhsDecBuff3, &nrhsDecLen3, szPlainText1, nPlainTextLen1);
				nrhsTotDecLen3 = nrhsDecLen3;
				EVP_EncryptFinal(prhsDecryptCtx3, szrhsDecBuff3, &nrhsDecLen3);
				nrhsTotDecLen3 += nrhsDecLen3;
				//BIO_dump_fp(stdout, (const char*)szrhsDecBuff3, nrhsTotDeLen3);

				uint64_t k = 0;
				//for (k = 0; k < llMax1; k++, Incrememt56BitKey(szKey2)) {
				parallel_for((uint64_t)0, llMax1, (uint64_t)1, [llMax1, &h2t, prhsDecryptCtx2, &szrhsDecBuff3, &szrhsDecBuff2, &nrhsDecLen2,
					nrhsTotDecLen3, &nrhsTotDecLen2, &szKey1, &szKey1Temp, &szKey2, &szKey3, &nComp, &cts](uint64_t index2) {
					//cout << "Second parallel for loop" << endl;
					unsigned char szKey2Temp[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
					// TODO: Increment key2 with index
					Add56BitKey(szKey2Temp, index2);
					// 3.
					EVP_DecryptInit(prhsDecryptCtx2, EVP_des_ecb(), szKey2Temp, NULL);
					EVP_CIPHER_CTX_set_padding(prhsDecryptCtx2, 0);
					if (1 == EVP_DecryptUpdate(prhsDecryptCtx2, szrhsDecBuff2, &nrhsDecLen2, szrhsDecBuff3, nrhsTotDecLen3))
					{
						nrhsTotDecLen2 = nrhsDecLen2;
						EVP_DecryptFinal(prhsDecryptCtx2, szrhsDecBuff2, &nrhsDecLen2);
						nrhsTotDecLen2 += nrhsDecLen2;

						// Check everu valy in the table
						//BIO_dump_fp(stdout, (const char*)szrhsDecBuff2, nrhsTotDecLen2);
						vector<unsigned char> vrhsDecBuff2(begin(szrhsDecBuff2), end(szrhsDecBuff2));
						if (std::binary_search(h2t.begin(), h2t.end(), vrhsDecBuff2, mpzComp()))
						{
							H2TABLE::iterator itrx3 = lower_bound(h2t.begin(), h2t.end(), vrhsDecBuff2, mpzComp());
							memcpy(szKey1, szKey1Temp, 8);
							memcpy(szKey2, szKey2Temp, 8);
							memcpy(szKey3, itrx3->second.data(), 8);
							nComp = 0;
							cts.cancel();;
						}
					}
				});
				if (0 == nComp) cts.cancel();
			});
		}, cts.get_token());
	}
	EVP_CIPHER_CTX_free(prhsDecryptCtx3);
	EVP_CIPHER_CTX_free(prhsDecryptCtx2);

	// Test another pair of data and encrypted text and check whether the key is correct or not.
	if (0 == nComp) {
		memcpy(szKey4, szKey1, 8); memcpy(szKey4 + 8, szKey2, 8); memcpy(szKey4 + 16, szKey3, 8);
		EVP_CIPHER_CTX* pEVOCIPCTX4 = NULL;
		pEVOCIPCTX4 = EVP_CIPHER_CTX_new();
		EVP_DecryptInit(pEVOCIPCTX4, EVP_des_ede3_ecb(), szKey4, NULL);
		unsigned char szTestBuff[64];
		int nTestBuffLen = 0;
		int nTotTestBuffLen = 0;
		EVP_DecryptUpdate(pEVOCIPCTX4, szTestBuff, &nTestBuffLen, sz3DESEncData2, n3DESEncDataLen2);
		nTotTestBuffLen = nTestBuffLen;
		EVP_DecryptFinal(pEVOCIPCTX4, szTestBuff + nTotTestBuffLen, &nTestBuffLen);
		nTotTestBuffLen += nTestBuffLen;
		if (0 == strcmp((const char*)szTestBuff, (const char*)szPlainText2)) {
			cout << "The Key is :" << endl;
			BIO_dump_fp(stdout, (const char*)szKey4, 24);
		}

		EVP_CIPHER_CTX_free(pEVOCIPCTX4);
	}

	OSSL_PROVIDER_unload(legacy);
	OSSL_PROVIDER_unload(deflt);

	return 0;
}
