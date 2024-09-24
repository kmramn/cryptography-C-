/*
Your goal this week is to write a program to compute discrete log modulo a prime p. Let g be some
element in Zp∗​ and suppose you are given h in Zp∗​ such that h = g^x where 1≤x≤2^40. Your goal is
to find x. More precisely, the input to your program is p,g,h and the output is x.

The trivial algorithm for this problem is to try all 2^{40} possible values of x until the correct
one is found, that is until we find an x satisfying h = g^x in Zp​. This requires 2^{40} multiplications.
In this project you will implement an algorithm that runs in time roughly sqrt{2^{40}} = 2^{20} using
a meet in the middle attack.

Let B=2^{20}. Since x is less than B^2

we can write the unknown x base B as x=x0*B+x1

where x0,x1​ are in the range [0,B−1]. Then

h = g^x = g^{x0*B + x1} = (g^B)^{x0} * g^{x1} in Zp

By moving the term g^{x1}​ to the other side we obtain

  h/g^{x1}=(g^B)^{x0}​ in Zp.

The variables in this equation are x0,x1​ and everything else is known: you are given g,h and B=2^{20}.
Since the variables x0​ and x1​ are now on different sides of the equation we can find a solution using
meet in the middle (Lecture 3.3 at 14:25):

First build a hash table of all possible values of the left hand side h/g^{x1}​ for x1=0,1,…,2^{20}.

Then for each value x0=0,1,2,…,2^{20} check if the right hand side (g^B)^{x0}​ is in this hash table.
If so, then you have found a solution (x0,x1) from which you can compute the required x as x= x0*B + x1​.

The overall work is about 2^{20} multiplications to build the table and another 2^{20} lookups in this table.

Now that we have an algorithm, here is the problem to solve:

p=134078079299425970995740249982058461274793658205923933 \77723561443721764030073546976801874298166903427690031 \858186486050853753882811946569946433649006084171

g=11717829880366207009516117596335367088558084999998952205 \59997945906392949973658374667057217647146031292859482967 \5428279466566527115212748467589894601965568

h=323947510405045044356526437872806578864909752095244 \952783479245297198197614329255807385693795855318053 \2878928001494706097394108577585732452307673444020333

Each of these three numbers is about 153 digits. Find x such that h=g^x in Zp.

To solve this assignment it is best to use an environment that supports multi-precision and modular
arithmetic. In Python you could use the gmpy2 or numbthy modules. Both can be used for modular inversion
and exponentiation. In C you can use GMP(https://gmplib.org/#DOWNLOAD). In Java use a BigInteger class
which can perform mod, modPow and modInverse operations.

gmp for windows https://gmplib.org/list-archives/gmp-discuss/2012-July/005089.html

https://hyperactve.blogspot.com/2012/04/gmp-c-library-in-windows-mingwmsys.html
https://stackoverflow.com/questions/22873884/how-do-i-run-configure-with-mingw

https://gmplib.org/list-archives/gmp-discuss/2012-July/005089.html
https://gmplib.org/manual/Notes-for-Particular-Systems#Notes-for-Particular-Systems

gmp tutorialss
https://home.cs.colorado.edu/~srirams/courses/csci2824-spr14/gmpTutorial.html
https://gmplib.org/manual/Integer-Functions

gmp_invert

X mpz_powm - negative exponenciation T = 1/g^x1 mod Zp
(h*T MOD Zp) - mpz_mul (r, h, T); mpz_mod (r, r, P);

X mpz_powm_ui - (g^B)^x0 d Zp
x = 787046375374217830 - wrong
x = 375374217830
*/

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <winerror.h>
#include <tchar.h>
#include <strsafe.h>

#include <iostream>
#include <vector>
using namespace std;

#include <stdio.h>
#include <math.h>

#include <wincrypt.h>
#pragma comment(lib, "Advapi32.lib")

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

//#define _SCL_SECURE_NO_WARNINGS
#pragma warning(disable:4146) 
#include <gmp.h>
#pragma comment(lib, "libgmp.a")
#pragma comment(lib, "libmpz.a")
#pragma comment(lib, "libgcc.a")

//#include <gmpxx.h>
//#pragma comment(lib, "libgmpxx.a")

void Pp(mpz_t p)
{
    mpz_out_str(stdout, 10, p);
    wprintf(L"\n");
}

int mpzsearch(mpz_t* pTable, unsigned int nSize, mpz_t val)
{
    unsigned int i = 0;
    for (i = 0; i < nSize; i++)
    {
        if (mpz_cmp(pTable[i], val) == 0)
            break;
    }
    if (i < nSize)
        return i;
    else
        return -1;
}

int wmain()
{
    wprintf(L"Descreet Log %u\n", sizeof(int));
    /*mpz_t integ;
    mpz_init(integ);
    mpz_set_str(integ, "134078079299425970995740249982058461274793658205923933", 10);
    mpz_out_str(stdout, 10, integ);
    wprintf(L"\n");
    mpz_add_ui(integ, integ, 1);
    mpz_out_str(stdout, 10, integ);*/

    /*mpz_t t1;
    mpz_init(t1);
    mpz_t b1;
    mpz_init_set_si(b1, 3);
    mpz_t e1;
    mpz_init_set_si(e1, -1);
    mpz_t m1;
    mpz_init_set_si(m1, 11);
    mpz_powm(t1, b1, e1, m1);
    mpz_out_str(stdout, 10, t1);
    char num[100];
    mpz_get_str(num, 10, t1);
    mpz_clear(integ);*/

    // Validate Answer
    /*int i1 = 0;
    wprintf(L"%u\n", sizeof(i1));
    unsigned int i2 = 0;
    wprintf(L"%u\n", sizeof(i2));
    long l1 = 0;
    wprintf(L"%u\n", sizeof(l1));
    unsigned long long l2 = 0;
    wprintf(L"%u\n", sizeof(l2));
    wprintf(L"%u\n", l1);
    wprintf(L"%u\n", l2);
    wprintf(L"%u\n", i1);
    wprintf(L"%u\n", i2);*/

    /*mpz_t p0;
    mpz_init(p0);
    mpz_set_str(p0, "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171", 10);
    //mpz_set_str(p0, "61", 10);
    Pp(p0);
    mpz_t g0;
    mpz_init(g0);
    mpz_set_str(g0, "11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568", 10);
    //mpz_set_str(g0, "6", 10);
    Pp(g0);
    mpz_t x0;
    mpz_init(x0);
    mpz_set_str(x0, "787046375374217830", 10);
    //mpz_set_str(x0, "57", 10);
    Pp(x0);
    mpz_t h0;
    mpz_init(h0);
    mpz_set_str(h0, "3239475104050450443565264378728065788649097520952449527834792452971981976143292558073856937958553180532878928001494706097394108577585732452307673444020333", 10);
    //mpz_set_str(h0, "37", 10);
    Pp(h0);
    mpz_t hr;
    mpz_init(hr);
    mpz_powm(hr, g0, x0, p0);
    Pp(h0);
    Pp(hr);
    return 0;*/

    /*unsigned long i = 0;
    long double B0 = pow((long)2, (long)40);
    for (i = 0; i < B0; i++)
    {
        mpz_powm_ui(hr, g0, i, p0);
        if (mpz_cmp(hr, h0) == 0)
        {
            wprintf(L"%lu", i);
            break;
        }
    }
    mpz_clear(hr); mpz_clear(h0); mpz_clear(x0); mpz_clear(g0); mpz_clear(p0);
    return 0;
    */

    mpz_t p;
    mpz_init_set_str(p, "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171", 10);
    mpz_t g;
    mpz_init_set_str(g, "11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568", 10);
    mpz_t h;
    mpz_init_set_str(h, "3239475104050450443565264378728065788649097520952449527834792452971981976143292558073856937958553180532878928001494706097394108577585732452307673444020333", 10);

    const unsigned int B = pow(2, 20);
    //const unsigned int B = pow(2, 3);
    //vector<string> X1HashTable;
    mpz_t* x1HashTable = new mpz_t[B];
    wprintf(L"Initialize Hash Table\n");
    for (unsigned int i = 0; i < B; i++)
    {
        mpz_init(x1HashTable[i]);
    }

    //X mpz_powm - negative exponenciation T = 1 / g ^ x1 mod Zp
    //(h * T MOD Zp) - mpz_mul(r, h, T); mpz_mod(r, r, P);
    // Build x1 power hash table
    wprintf(L"Building Hash Table\n");
    for (unsigned int i = 0; i < B; i++)
    {
        mpz_t x1;
        mpz_init(x1);
        mpz_set_si(x1, -i);
        //Pp(x1);
        mpz_t le;
        mpz_init(le);
        mpz_powm(le, g, x1, p);
        //Pp(T);

        //mpz_t r;
        //mpz_init(r);
        //char szNum[1024];
        //SecureZeroMemory(szNum, sizeof(szNum));
        //mpz_get_str(szNum, 10, r);
        //X1HashTable.push_back(szNum);
        mpz_mul(x1HashTable[i], h, le);
        //Pp(x1HashTable[i]);
        mpz_mod(x1HashTable[i], x1HashTable[i], p);
        //Pp(x1HashTable[i]);
        mpz_clear(x1); mpz_clear(le);
    }


    //vector<string>::iterator itr;

    //X mpz_powm_ui - (g ^ B) ^ x0 d Zp
    mpz_t gB;
    mpz_init_set(gB, g);
    //Pp(gB);
    mpz_powm_ui(gB, gB, B, p);
    //Pp(gB);

    unsigned int nx1 = 0;
    unsigned int nx0 = 0;
    wprintf(L"Searching Hash Table\n");
    for (nx0 = 0; nx0 < B; nx0++)
    {
        mpz_t r;
        mpz_init(r);
        mpz_powm_ui(r, gB, nx0, p);
        //Pp(r);
        if ((nx1 = mpzsearch(x1HashTable, B, r)) != -1)
        {
            mpz_clear(r);
            break;
        }

        mpz_clear(r);
        //char szNum[1024];
        //SecureZeroMemory(szNum, sizeof(szNum));
        //mpz_get_str(szNum, 10, r);
        //itr = find(X1HashTable.begin(), X1HashTable.end(), string(szNum));
        //if (itr != X1HashTable.end())
        //    break;
    }
    mpz_clear(gB);

    wprintf(L"Finished Searching Hash Table\n");
    if (nx0 < B)
    {
        wprintf(L"Found x\n");
        mpz_t x;
        mpz_init(x);
        mpz_t x0;
        mpz_init(x0);
        mpz_t x1;
        mpz_init(x1);

        mpz_set_ui(x0, nx0);
        wprintf(L"%u\n", nx1);
        Pp(x0);
        mpz_set_ui(x1, nx1);
        wprintf(L"%u\n", nx1);
        Pp(x1);

        mpz_mul_ui(x, x0, B);
        Pp(x);

        mpz_add(x, x, x1);
        Pp(x);

        mpz_clear(x);
    }
    wprintf(L"UnInitialize Hash Table\n");
    for (unsigned int i = 0; i < B; i++)
    {
        mpz_clear(x1HashTable[i]);
    }
    delete[] x1HashTable;

    mpz_clear(p);
    mpz_clear(g);
    mpz_clear(h);

    return 0;
}
