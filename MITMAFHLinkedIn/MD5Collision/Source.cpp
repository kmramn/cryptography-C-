
#include <Windows.h>
#include <winerror.h>

#include <ppl.h>
#include <pplcancellation_token.h>
using namespace concurrency;

//
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <chrono>
#include <atomic>
#include <mutex>
#include <execution>
using namespace std;

#include <tchar.h>
#include <strsafe.h>

#pragma warning(disable : 4146)

// https://github.com/BrianGladman/
#include <gmp.h>
#include <gmpxx.h>
#pragma comment(lib, "mpir.lib")
#pragma comment(lib, "mpirxx.lib")

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
    mpz_class m_x;
    PRTimer()
    {
        m_start = m_sc.now();
    }

    inline void DetectKeyBoard(const mpz_class& x)
    {
        if (_kbhit())
        {
            wint_t wch = WEOF;
            m_x = x;
            wch = _getwch();
            if (wch != WEOF)
            {
                chrono::steady_clock::time_point end = m_sc.now();
                auto time_span = static_cast<chrono::duration<double>>(end - m_start);
                cout << "x = " << m_x.get_str() << " Operation took: " << time_span.count() << " seconds !!!" << endl;
            }
        }
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

struct mpzComp
{
    bool operator()(const mpz_class& lhs, const pair<mpz_class, unsigned long long>& rhs)
    {
        if (lhs < rhs.first)
            return true;
        return false;
    }
    bool operator()(const pair<mpz_class, unsigned long long>& lhs, const mpz_class& rhs)
    {
        if (lhs.first < rhs)
            return true;
        return false;
    }
};

// MITM Attack
void main()
{
    typedef map<vector<uint8_t>, mpz_class> H2TABLE;
    //typedef vector<pair<vector<uint8_t>, mpz_class>> H2TABLE;
    mpz_class llMax;
    mpz_ui_pow_ui(llMax.get_mpz_t(), 2, 31);

    //// Thread1 vector
    //H2TABLE h2t;
    //{
    //    PRTimer prTimer;
    //    mutex mtxVecX1;
    //    cout << "Building h table...! of size " << llMax.get_str() << endl;
    //    //for (unsigned long long x2 = 0; x2 < llMax; x2++)
    //    cancellation_token_source cts;
    //    run_with_cancellation_token([h, g, p, llMax, &h2t, &prTimer, &mtxVecX1, &cts]()
    //    {
    //        atomic<mpir_ui> x2 = 0;
    //        parallel_for((mpir_ui)0, llMax.get_ui(), (mpir_ui)1, [h, g, p, &x2, &h2t, &prTimer, 
    //            &mtxVecX1, &cts](mpir_ui dummy)
    //        {
    //            mpz_class x2Temp = ++x2;
    //            mpz_class x22;
    //            x22 = -x2Temp;
    //            mpz_class h2;
    //            mpz_class g2;
    //            mpz_powm(g2.get_mpz_t(), g.get_mpz_t(), x22.get_mpz_t(), p.get_mpz_t());
    //            mpz_mul(h2.get_mpz_t(), h.get_mpz_t(), g2.get_mpz_t());
    //            mpz_mod(h2.get_mpz_t(), h2.get_mpz_t(), p.get_mpz_t());

    //            //h2t.push_back(h2, x2);
    //            //h2t.insert(make_pair(h2, x2.get_ui()));
    //            mtxVecX1.lock();
    //            h2t.push_back(make_pair(h2, x2Temp.get_ui()));
    //            mtxVecX1.unlock();

    //            //prTimer.DetectKeyBoard(x2);
    //        });
    //    }, cts.get_token());

    //    cout << "Finish building h table...! of size " << llMax.get_str() << endl;
    //}
    // Thread2 vector
    H2TABLE h2t;
    //{
    //    PRTimer prTimer;
    //    cout << "Allocation vector h table...! of size " << llMax.get_str() << endl;
    //    h2t.resize(llMax.get_ui());
    //}
    {
        PRTimer prTimer;
        const EVP_MD* pMD5 = EVP_md5();
        std::mutex mtxMap;
        cout << "Building colission table...! of size " << llMax.get_str() << endl;
        //for (unsigned long long x2 = 0; x2 < llMax; x2++)
        cancellation_token_source cts;
        run_with_cancellation_token([pMD5, llMax, &h2t, &prTimer, &mtxMap, &cts]()
        {
            atomic<mpir_ui> x2 = 0;
            parallel_for((mpir_ui)0, llMax.get_ui(), (mpir_ui)1, [pMD5, &x2, &h2t, &prTimer,
                &mtxMap, &cts](mpir_ui index)
            {
                mpz_class mpzData = ++x2;
                EVP_MD_CTX* pMDCtx = EVP_MD_CTX_new();
                //cout << index << endl;
                //mpz_class x2Temp = index;
                EVP_DigestInit_ex(pMDCtx, pMD5, NULL);
                EVP_DigestUpdate(pMDCtx, mpzData.get_str(16).c_str(), mpzData.get_str(16).size());
                unsigned char szMD[16];
                unsigned int nMDLen = 0;
                EVP_DigestFinal_ex(pMDCtx, szMD, &nMDLen);

                vector<uint8_t> vMD(begin(szMD), end(szMD));
                H2TABLE::iterator itrClash = h2t.find(vMD);
                if (itrClash == h2t.end())
                    h2t.emplace(make_pair(vMD, mpzData));
                else
                {
                    mtxMap.lock();
                    cout << "Collision detected for data:" << itrClash->second.get_str(16) << endl;
                    cout << mpzData.get_str(16) << endl;
                    cout << "MD5 hash:" << endl;
                    BIO_dump_fp(stdout, szMD, nMDLen);
                    cout << endl;
                    h2t[vMD] = mpzData;
                    mtxMap.unlock();
                }

                //prTimer.DetectKeyBoard(x2);
            });
        }, cts.get_token());
        cout << "Finish building colission table...! of size " << llMax.get_str() << endl;
    }
}
