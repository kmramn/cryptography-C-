
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
/*#include <gmp.h>
#pragma comment(lib, "libgmp.a")
//#pragma comment(lib, "libgmpxx.a")
#pragma comment(lib, "libmpz.a")
#pragma comment(lib, "libmpf.a")
#pragma comment(lib, "libmpq.a")
#pragma comment(lib, "libmpn.a")
#include <gmpxx.h>
#pragma comment(lib, "libcxx.a")

// C:\MinGW\lib\gcc\mingw32\6.3.0 for x86 or
#pragma comment(lib, "libgcc.a")
// C:\cygwin64\lib\gcc\x86_64-w64-mingw32\11 for x64
#pragma comment(lib, "libgccpp.dll.a")
// If you use Cygwin64 include this
#pragma comment(lib, "libcygwin.a")*/

// https://github.com/BrianGladman/
#include <gmp.h>
#include <gmpxx.h>
#pragma comment(lib, "mpir.lib")
#pragma comment(lib, "mpirxx.lib")

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

// Brute force
/*void main()
{
    // 29273167435619875865648635574214463921301073660463254408453331850401657956983537871787113609292615794062203509616835173757634929204648986253320335067363537346974880192601710607509298307716746218004361136134358473506342760986595032228188627696801089373330585170010488176393659806562392542974720770277547459350895538966336339097331021919348216767110579418607554641860403061482744502133517219269921108961049865670520752589149396650766533592202331766023286364589443152588748580046154633824567218845887105251274070051
    // 84F5733EECB08886845FA5F2B39F32098AE6BA6C9FF8C7487EE64E14FE3AEDACC8EF4DC3EEDC9D37FBF973785A2B2965D374D22AC0787BE95058815071E4DBCAF04C71EB1ABBA912F2C7BD4B5716465FE6E603849269E5B5F8D9744090843E93EFA72EBAC2B08F58BF5DF7B3ACB01916C03AD017417C0D5D3A07920B65A204E6E4729A2E068E161489521B868EF5B304FA5DD3EA4A55914C54CF6C5084F9B005DABB6E3779F4BDE1CD234E4FF20794B20B1A3ECDD124AE2F36C33FBD9C0A1AB031DB436F24AD095B7AFE0B0BB3C0A9C7C54E71823

    //mpz_class p("1589946103", 10);
    mpz_class p("e7e94db309dc10540a75e38be90c32141ecb958802ae172e09de549156e028f443ea6f788074e1fec332703352b376170006f6ef4f4a2fb1d0d943d0bed9", 16);

    //mpz_class g("1154947122", 10);
    mpz_class g("2F26760E85950864D1F24421F2AB599A2DE6A4379B86AD5972CA348938B2B25ED6ABF80D03E9BC7C9F54CFDC670B15EC33DDA88CBFFC53F725D779247813", 16);

    //mpz_class h("926098862", 10);
    //mpz_class h("1395891057", 10);
    //mpz_class h("2cc77e4b71156c88f9773e4310a9ace9368f2f805ce7257c8b758f838917630e2d91b07956f41828eec83d6b31e8aa787bb3e1d934e08a128b75a7d85418", 16);
    //mpz_class h("A897869057ED2B2175BDB8D40D051BC7184ADA9C18349681B1D34942650CAA49BCE98B61F86D9093C23170EF473A7A7DEB0D8C1D4FC559E20C82F3E1EE2F", 16);
    //mpz_class h("4CCEB3BC46C20F2CCE84D3002A97A2346EAC084600911EE86A5382CFF997993C883BE3D3498896E95B79185A560F62109F8F4C982E10073B8BA1468B2B52", 16); //10796093022208
    mpz_class h("9A00CCF93DCB972C96FD19C7663D0FAA05604C16EA75BB4056F7B3B7A688CD3C8CEE1038A9949CCDC6626DFBF6894496E56672E973D2DA101F7EBB233260", 16); // 2 ^ 56
    // Find x Descreet Log using MITM Attack
    //unsigned long long llMax = pow(2, 16);
    //unsigned long long llMax = pow(2, 44);
    unsigned long long llMax = pow(2, 56);
    //mpz_class x(-1);
    mpz_class x("72057594037927936", 10);
    mpz_class nh;
    {
        cout << "Matching all possible values x = 0 to " << llMax << endl;
        PRTimer prTimer;
        do
        {
            //prTimer.DetectKeyBoard(x++);
            prTimer.DetectKeyBoard(x--);
            mpz_powm(nh.get_mpz_t(), g.get_mpz_t(), x.get_mpz_t(), p.get_mpz_t());
        //} while (h != nh);
        } while ((h != nh) &&
            //(strtoull(x.get_str().c_str(), NULL, 10) < llMax));
            (strtoull(x.get_str().c_str(), NULL, 10) > 0));
        prTimer.m_x = x;
    }

    cout << endl << "Discrete logarithm(DLog) x found using brute-force method [such that h = (g^x) mod p] = " << x.get_str() << endl;
}*/

/*// MITM Attack
void main()
{
    // 29273167435619875865648635574214463921301073660463254408453331850401657956983537871787113609292615794062203509616835173757634929204648986253320335067363537346974880192601710607509298307716746218004361136134358473506342760986595032228188627696801089373330585170010488176393659806562392542974720770277547459350895538966336339097331021919348216767110579418607554641860403061482744502133517219269921108961049865670520752589149396650766533592202331766023286364589443152588748580046154633824567218845887105251274070051
    // 84F5733EECB08886845FA5F2B39F32098AE6BA6C9FF8C7487EE64E14FE3AEDACC8EF4DC3EEDC9D37FBF973785A2B2965D374D22AC0787BE95058815071E4DBCAF04C71EB1ABBA912F2C7BD4B5716465FE6E603849269E5B5F8D9744090843E93EFA72EBAC2B08F58BF5DF7B3ACB01916C03AD017417C0D5D3A07920B65A204E6E4729A2E068E161489521B868EF5B304FA5DD3EA4A55914C54CF6C5084F9B005DABB6E3779F4BDE1CD234E4FF20794B20B1A3ECDD124AE2F36C33FBD9C0A1AB031DB436F24AD095B7AFE0B0BB3C0A9C7C54E71823

    //mpz_class p("1589946103", 10); // 2 ^ 16
    mpz_class p("e7e94db309dc10540a75e38be90c32141ecb958802ae172e09de549156e028f443ea6f788074e1fec332703352b376170006f6ef4f4a2fb1d0d943d0bed9", 16);

    //mpz_class g("1154947122", 10); // 2 ^ 16
    mpz_class g("2F26760E85950864D1F24421F2AB599A2DE6A4379B86AD5972CA348938B2B25ED6ABF80D03E9BC7C9F54CFDC670B15EC33DDA88CBFFC53F725D779247813", 16);

    //mpz_class h("926098862", 10); // 2 ^ 16
    //mpz_class h("1395891057", 10); // 2 ^ 16
    //mpz_class h("1056482489", 10); // 2 ^ 20
    //mpz_class h("2cc77e4b71156c88f9773e4310a9ace9368f2f805ce7257c8b758f838917630e2d91b07956f41828eec83d6b31e8aa787bb3e1d934e08a128b75a7d85418", 16); // 2 ^ 56
    //mpz_class h("33AA23876E0AE4E2C4D14214740B6083C1323E2DCDBE69B36AEE6E8CADE7DAE7A2BFA1EFFFD753736A1D3B2EC22FC136A0C9641B65C6AC00FA7C78738A51", 16); // ??
    //mpz_class h("A897869057ED2B2175BDB8D40D051BC7184ADA9C18349681B1D34942650CAA49BCE98B61F86D9093C23170EF473A7A7DEB0D8C1D4FC559E20C82F3E1EE2F", 16); // 2 ^ 32
    //mpz_class h("4CCEB3BC46C20F2CCE84D3002A97A2346EAC084600911EE86A5382CFF997993C883BE3D3498896E95B79185A560F62109F8F4C982E10073B8BA1468B2B52", 16); // ((2 ^ 44) / 2 ) + 10
    mpz_class h("9A00CCF93DCB972C96FD19C7663D0FAA05604C16EA75BB4056F7B3B7A688CD3C8CEE1038A9949CCDC6626DFBF6894496E56672E973D2DA101F7EBB233260", 16); // 2 ^ 56
    //typedef vector<mpz_class> H2TABLE;
    typedef map<mpz_class, unsigned long long int> H2TABLE;
    //unsigned long long llMax = pow(2, 8);
    //unsigned long long llMax = pow(2, 28);
    mpz_class llMax;
    //mpz_ui_pow_ui(llMax.get_mpz_t(), 2, 8); // works for h = 1395891057
    //mpz_ui_pow_ui(llMax.get_mpz_t(), 2, 16); // works for h = A897869057ED2B2175BDB8D40D051BC7184ADA9C18349681B1D34942650CAA49BCE98B61F86D9093C23170EF473A7A7DEB0D8C1D4FC559E20C82F3E1EE2F
    //mpz_ui_pow_ui(llMax.get_mpz_t(), 2, 22); // works for h = 4CCEB3BC46C20F2CCE84D3002A97A2346EAC084600911EE86A5382CFF997993C883BE3D3498896E95B79185A560F62109F8F4C982E10073B8BA1468B2B52
    mpz_ui_pow_ui(llMax.get_mpz_t(), 2, 28); // works for 9A00CCF93DCB972C96FD19C7663D0FAA05604C16EA75BB4056F7B3B7A688CD3C8CEE1038A9949CCDC6626DFBF6894496E56672E973D2DA101F7EBB233260
    // Find x Descreet Log using MITM Attack
    // 0 < x < 2^16
    // Build half h/(g^x2) where 0 < x2 < 2^8

    H2TABLE h2t;
    {
        mpz_class h2;
        mpz_class g2;
        mpz_class x22;
        PRTimer prTimer;
        cout << "Building h table...! of size " << llMax.get_str() << endl;
        //for (unsigned long long x2 = 0; x2 < llMax; x2++)
        for (mpz_class x2 = 0; x2 < llMax; x2++)
        {
            x22 = -x2;
            mpz_powm(g2.get_mpz_t(), g.get_mpz_t(), x22.get_mpz_t(), p.get_mpz_t());
            mpz_mul(h2.get_mpz_t(), h.get_mpz_t(), g2.get_mpz_t());
            mpz_mod(h2.get_mpz_t(), h2.get_mpz_t(), p.get_mpz_t());

            //h2t.push_back(h2, x2);
            h2t.insert(make_pair(h2, x2.get_ui()));

            //prTimer.DetectKeyBoard(x2);
        }
        cout << "Finish building h table...! of size " << llMax.get_str() << endl;
    }

    cout << "Search h table using g...!" << endl;
    H2TABLE::iterator itrx2 = h2t.end();
    mpz_class x1max = 0;
    {
        PRTimer prTimer;

        //mpz_class g1;
        //mpz_class x1 = 0;
        //for (x1 = 0; x1 < (llMax - 1); x1++)
        //{
        //    x1max = x1 * llMax;

        //    mpz_powm(g1.get_mpz_t(), g.get_mpz_t(), x1max.get_mpz_t(), p.get_mpz_t());

        //    //itrx2 = h2t.find(g1);
        //    //itrx2 = find(h2t.begin(), h2t.end(), g1);
        //    itrx2 = h2t.find(g1);
        //    if (itrx2 != h2t.end())
        //        break;

        //    //prTimer.DetectKeyBoard(x1);
        //}
        // cout << "x1 found using Meet-In-The-Middle attack [such that h = (g^x) mod p] = " << x1.get_str() << endl;

        // * Paraller For https://learn.microsoft.com/en-us/cpp/parallel/concrt/how-to-use-cancellation-to-break-from-a-parallel-loop?view=msvc-170 * /
        // Call parallel_for in the context of a cancellation token to search for the element.
        cancellation_token_source cts;
        run_with_cancellation_token([g, p, llMax, &h2t, &prTimer, &x1max, &itrx2, &cts]()
        {
            atomic<mpir_ui> x1 = 0;
            parallel_for((mpir_ui)0, llMax.get_ui(), (mpir_ui)1, [g, p, llMax, &x1, &h2t, &prTimer, &x1max, &itrx2, &cts](mpir_ui dummy) {
                mpir_ui x1Temp = ++x1;
                H2TABLE::iterator itrx2Tmp;
                mpz_class g1, x1Tmpmax;
                x1Tmpmax = llMax * x1Temp;
                //cout << x1Tmpmax.get_ui() << "=" << llMax.get_ui() << "*" << x1 << endl;
                mpz_powm(g1.get_mpz_t(), g.get_mpz_t(), x1Tmpmax.get_mpz_t(), p.get_mpz_t());

                itrx2Tmp = h2t.find(g1);
                if (itrx2Tmp != h2t.end())
                {
                    itrx2 = itrx2Tmp;
                    x1max = x1Tmpmax;
                    cts.cancel();
                }

                //prTimer.DetectKeyBoard(x1.load());
            });
        }, cts.get_token());
        // *Paraller For* /
    }

    //if (itrx2 != h2t.end())
    {
        mpz_class x;
        //x = x1max + itrx2->second;
        //unsigned long ulx2 = distance(h2t.begin(), itrx2);
        //mpz_class x2(ulx2);
        //x = x1max + x2;
        x = x1max + itrx2->second;
        cout << x.get_ui() << "=" << x1max.get_ui() << "+" << itrx2->second << endl;
        cout << endl <<
            "Discrete logarithm(DLog) x found using Meet-In-The-Middle attack [such that h = (g^x) mod p] = " << x.get_str()
            << endl;
    }
    //else
    //{
    //    cout << endl <<
    //        "Discrete logarithm(DLog) x NOT found using Meet-In-The-Middle attack [such that h = (g^x) mod p] = 0" << endl;
    //}
}*/

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
    mpz_class p("e7e94db309dc10540a75e38be90c32141ecb958802ae172e09de549156e028f443ea6f788074e1fec332703352b376170006f6ef4f4a2fb1d0d943d0bed9", 16);
    mpz_class g("2F26760E85950864D1F24421F2AB599A2DE6A4379B86AD5972CA348938B2B25ED6ABF80D03E9BC7C9F54CFDC670B15EC33DDA88CBFFC53F725D779247813", 16);
    mpz_class h("9A00CCF93DCB972C96FD19C7663D0FAA05604C16EA75BB4056F7B3B7A688CD3C8CEE1038A9949CCDC6626DFBF6894496E56672E973D2DA101F7EBB233260", 16); // 2 ^ 56
    //typedef map<mpz_class, unsigned long long int> H2TABLE;
    typedef vector<pair<mpz_class, unsigned long long int>> H2TABLE;
    //H2TABLE h2t1;
    //mpz_class i1("23");
    //h2t1.push_back(make_pair(i1, 1));
    //i1 = "12";
    //h2t1.push_back(make_pair(i1, 2));
    //i1 = "2";
    //h2t1.push_back(make_pair(i1, 3));
    //i1 = "1";
    //h2t1.push_back(make_pair(i1, 4));
    //i1 = "122";
    //h2t1.push_back(make_pair(i1, 5));
    //i1 = "78";
    //h2t1.push_back(make_pair(i1, 6));
    //i1 = "34";
    //h2t1.push_back(make_pair(i1, 7));
    //i1 = "56";
    //h2t1.push_back(make_pair(i1, 8));
    //sort(h2t1.begin(), h2t1.end());
    //for(auto it1 : h2t1)
    //{
    //    cout << "(" << it1.first.get_str() << ", " << it1.second << ")" << endl;
    //}
    //mpz_class j2("56");
    //if (binary_search(h2t1.begin(), h2t1.end(), j2, mpzComp()))
    //{
    //    cout << "found" << endl;
    //    cout << lower_bound(h2t1.begin(), h2t1.end(), j2, mpzComp())->second << endl;
    //}
    //return;
    mpz_class llMax;
    //mpz_ui_pow_ui(llMax.get_mpz_t(), 2, 28); // works for 9A00CCF93DCB972C96FD19C7663D0FAA05604C16EA75BB4056F7B3B7A688CD3C8CEE1038A9949CCDC6626DFBF6894496E56672E973D2DA101F7EBB233260
    mpz_ui_pow_ui(llMax.get_mpz_t(), 2, 31); // works for 9A00CCF93DCB972C96FD19C7663D0FAA05604C16EA75BB4056F7B3B7A688CD3C8CEE1038A9949CCDC6626DFBF6894496E56672E973D2DA101F7EBB233260

    // Non thread
    //H2TABLE h2t;
    //{
    //    mpz_class h2;
    //    mpz_class g2;
    //    mpz_class x22;
    //    PRTimer prTimer;
    //    cout << "Building h table...! of size " << llMax.get_str() << endl;
    //    //for (unsigned long long x2 = 0; x2 < llMax; x2++)
    //    for (mpz_class x2 = 0; x2 < llMax; x2++)
    //    {
    //        x22 = -x2;
    //        mpz_powm(g2.get_mpz_t(), g.get_mpz_t(), x22.get_mpz_t(), p.get_mpz_t());
    //        mpz_mul(h2.get_mpz_t(), h.get_mpz_t(), g2.get_mpz_t());
    //        mpz_mod(h2.get_mpz_t(), h2.get_mpz_t(), p.get_mpz_t());

    //        //h2t.push_back(h2, x2);
    //        //h2t.insert(make_pair(h2, x2.get_ui()));
    //        h2t.push_back(make_pair(h2, x2.get_ui()));

    //        //prTimer.DetectKeyBoard(x2);
    //    }
    //    cout << "Finish building h table...! of size " << llMax.get_str() << endl;
    //}
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
    {
        PRTimer prTimer;
        cout << "Allocation vector h table...! of size " << llMax.get_str() << endl;
        h2t.resize(llMax.get_ui());
    }
    return;
    {
        PRTimer prTimer;
        cout << "Building h table...! of size " << llMax.get_str() << endl;
        //for (unsigned long long x2 = 0; x2 < llMax; x2++)
        cancellation_token_source cts;
        run_with_cancellation_token([h, g, p, llMax, &h2t, &prTimer, &cts]()
        {
            atomic<mpir_ui> x2 = 0;
            parallel_for((mpir_ui)0, llMax.get_ui(), (mpir_ui)1, [h, g, p, &x2, &h2t, &prTimer,
                &cts](mpir_ui index)
            {
                //cout << index << endl;
                //mpz_class x2Temp = index;
                mpz_class x2Temp = ++x2;
                mpz_class x22 = -x2Temp;
                mpz_class h2;
                mpz_class g2;
                mpz_powm(g2.get_mpz_t(), g.get_mpz_t(), x22.get_mpz_t(), p.get_mpz_t());
                mpz_mul(h2.get_mpz_t(), h.get_mpz_t(), g2.get_mpz_t());
                mpz_mod(h2.get_mpz_t(), h2.get_mpz_t(), p.get_mpz_t());

                //h2t.push_back(h2, x2);
                //h2t.insert(make_pair(h2, x2.get_ui()));
                //cout << h2.get_str() << endl;
                h2t[index] = make_pair(h2, x2Temp.get_ui());

                //prTimer.DetectKeyBoard(x2);
            });
        }, cts.get_token());
        cout << "Finish building h table...! of size " << llMax.get_str() << endl;
    }

    {
        PRTimer prTimer;
        cout << "Sorting h table...! of size " << llMax.get_str() << endl;

        std::sort(h2t.begin(), h2t.end());
        //parallel_sort(h2t.begin(), h2t.end()); It took almost the smae time as std::sort

        cout << "Finish sorting h table...! of size " << llMax.get_str() << endl;
    }

    cout << "Search h table using g...!" << endl;
    H2TABLE::iterator itrx2 = h2t.end();
    mpz_class x1max = 0;
    {
        PRTimer prTimer;

        //mpz_class g1;
        //mpz_class x1 = 0;
        //for (x1 = 0; x1 < (llMax - 1); x1++)
        //{
        //    x1max = x1 * llMax;

        //    mpz_powm(g1.get_mpz_t(), g.get_mpz_t(), x1max.get_mpz_t(), p.get_mpz_t());

        //    //itrx2 = h2t.find(g1);
        //    //itrx2 = find(h2t.begin(), h2t.end(), g1);
        //    itrx2 = h2t.find(g1);
        //    if (itrx2 != h2t.end())
        //        break;

        //    //prTimer.DetectKeyBoard(x1);
        //}
        //cout << "x1 found using Meet-In-The-Middle attack [such that h = (g^x) mod p] = " << x1.get_str() << endl;

        /*Paraller For https://learn.microsoft.com/en-us/cpp/parallel/concrt/how-to-use-cancellation-to-break-from-a-parallel-loop?view=msvc-170*/
        // Call parallel_for in the context of a cancellation token to search for the element.
        cancellation_token_source cts;
        run_with_cancellation_token([g, p, llMax, &h2t, &prTimer, &x1max, &itrx2, &cts]()
        {
            atomic<mpir_ui> x1 = 0;
            parallel_for((mpir_ui)0, llMax.get_ui(), (mpir_ui)1, [g, p, llMax, &x1, &h2t, &prTimer, &x1max, &itrx2, &cts](mpir_ui dummy) {
                mpir_ui x1Temp = ++x1;
                H2TABLE::iterator itrx2Tmp;
                mpz_class g1, x1Tmpmax;
                x1Tmpmax = llMax * x1Temp;
                //cout << x1Tmpmax.get_ui() << "=" << llMax.get_ui() << "*" << x1 << endl;
                mpz_powm(g1.get_mpz_t(), g.get_mpz_t(), x1Tmpmax.get_mpz_t(), p.get_mpz_t());

                //itrx2Tmp = h2t.find(g1);
                //if (itrx2Tmp != h2t.end())
                if (std::binary_search(h2t.begin(), h2t.end(), g1, mpzComp()))
                {
                    //itrx2 = itrx2Tmp;
                    itrx2 = lower_bound(h2t.begin(), h2t.end(), g1, mpzComp());
                    x1max = x1Tmpmax;
                    cts.cancel();
                }

                //prTimer.DetectKeyBoard(x1.load());
            });
        }, cts.get_token());
        /*Paraller For*/
    }

    //if (itrx2 != h2t.end())
    {
        mpz_class x;
        //x = x1max + itrx2->second;
        //unsigned long ulx2 = distance(h2t.begin(), itrx2);
        //mpz_class x2(ulx2);
        //x = x1max + x2;
        x = x1max + itrx2->second;
        cout << x.get_ui() << "=" << x1max.get_ui() << "+" << itrx2->second << endl;
        cout << endl <<
            "Discrete logarithm(DLog) x found using Meet-In-The-Middle attack [such that h = (g^x) mod p] = " << x.get_str()
            << endl;
    }
    //else
    //{
    //    cout << endl <<
    //        "Discrete logarithm(DLog) x NOT found using Meet-In-The-Middle attack [such that h = (g^x) mod p] = 0" << endl;
    //}
}
