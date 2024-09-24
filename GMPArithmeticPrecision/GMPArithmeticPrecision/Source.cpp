//
// Built using Visual Studio which use GMP (GNU Multi Pression) arithmetic library. 
//
#include <stdio.h>

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// GMP(https://gmplib.org/#DOWNLOAD)

#pragma warning ( disable : 4146 )
// gmp-6.2.1\gmp-6.2.1\C_LIBRARY\GMP\include
#include "gmp.h"
// gmp-6.2.1\gmp-6.2.1\C_LIBRARY\GMP\lib
#pragma comment(lib, "libgmp.a")

//// gmp-6.2.1\gmp-6.2.1\C_LIBRARY\GMP\include
//#include "gmpxx.h"
//// gmp-6.2.1\gmp-6.2.1\C_LIBRARY\GMP\lib
//#pragma comment(lib, "libgmpxx.a")

// Float
// gmp-6.2.1\gmp-6.2.1\mpf\.libs
#pragma comment(lib, "libmpf.a")
// Integer
// gmp-6.2.1\gmp-6.2.1\mpz\.libs
#pragma comment(lib, "libmpz.a")
// 
// gmp-6.2.1\gmp-6.2.1\mpn\.libs
#pragma comment(lib, "libmpn.a")
// Rational number
// gmp-6.2.1\gmp-6.2.1\mpq\.libs
#pragma comment(lib, "libmpq.a")
// gmp-6.2.1\gmp-6.2.1\printf\.libs
#pragma comment(lib, "libprintf.a")

// C:\MinGW\lib\gcc\mingw32\6.3.0
#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "libgcc.a")

string StrToHex(string szMsg)
{
    string szHexMsg;
    stringstream ss;
    for (auto chMsg : szMsg)
    {
        ss << setfill('0') << setw(2) << std::hex << (int)chMsg;
    }
    szHexMsg = ss.str();
    return szHexMsg;
}

string HexToStr(string szHex)
{
    string szMsg;
    for (int i = 0; i < szHex.length(); i += 2)
    {
        string szSub = szHex.substr(i, 2);
        char ch = stoul(szSub, nullptr, 16);
        szMsg += ch;
    }
    return szMsg;
}

void printmpz(mpz_t e)
{
    char szBuf[4096];
    memset(szBuf, 0, sizeof(szBuf));
    //gmp_printf("%Zd\n", integ);
    gmp_sprintf(szBuf, "%Zd\n", e);
    cout << szBuf << endl;
}

void main()
{
    char szBuf[4096];
    // We need to select two large primes p and q of 2048 bits. The resulting RSA key will be 4096 bits.
    // In the below code I have select two randomly genarated 2048 bits integer. But they may or may not
    // be primes. They are the seed value and we use this random generated ingeters to generated two 
    // primes p and q using the GMP function mpz_nextprime. It is very risky to generated two primes
    // which are closly related because there are general RSA attacks. That is the reason why chertain
    // softwares like PuTTYgen request the user to input the seed value by randomly moving the mouse in
    // a particular area.
    mpz_t p;
    mpz_init(p);
    mpz_set_str(p, "5C9E2F2AA0E5307D632844A4626E277842C7E17E205571D74138748A8258D44A57697E1CF56E7F07659F8EB5F2173A9949374A9D2BBE65E2C212DEA6A26DCBFB2F986B87C0E10122F5C68D32FFBA10A8A15721F3B33277CF32E195906CB225AF85E93BEC38050F0383618CA686498E624674ED33FF459FF98EF460BBAB3035E3AE32F91A0524A50A5408125EE4FED3134B9F1919BF7DBAB8FF1B9966AAD8D3DA8A628CFE3C9969FD4143632012E8F4EAA2C5756CC53902CAF196F1B8EACF3DD33BE33D613CE2634E0EC8B7692CCEDEDF3462FFCCB5C435392FC0253F3344829F3B0A84D620BF7F0D079B9FFEA2BB441A9CE7FC6D6874FF8EB0B78EF5276D1149", 16);
    mpz_nextprime(p, p);
    //printmpz(p);
    mpz_t q;
    mpz_init(q);
    mpz_set_str(q, "61EFF5E4AA2E336BF555EFF06E23588DCD128DBB03A4FA4F745753ABEAABC2E42B8B30513E74DA313413EEF8C4565C31F506DC24F44E7A2DE18A1C6020746CC75CFCB0B2F4AA57088AA048C0865EB87134A8515797E6BF051F9CCB17A769213012D07D74EF4BA3A6CE73C3B8A9C496E0DB5DF9D3ACF829787C9F1348E489B9D3D978147267B5E889160C01B761C4D878A3696ADF082894AA025DAD0F9B75B0A70027CDDC15C8CF6B0579C981742D461B2EDEE59AA4CD621DA32C9F0B7C8D8A1E1396481BBEECC36CD6DD57BB60A6573CD1D23098969A5162CAA8AC391BC6878FA7BE42A6FAE0EDBA21528A97C52B03700E5BABA1C7BBE32A9F4CAEDAE94D1FF9", 16);
    mpz_nextprime(q, q);
    //printmpz(q);
    mpz_t n;
    mpz_init(n);
    mpz_mul(n, p, q);
    //printmpz(n);

    mpz_t p1;
    mpz_init(p1);
    mpz_sub_ui(p1, p, 1);
    //printmpz(p1);
    mpz_t q1;
    mpz_init(q1);
    mpz_sub_ui(q1, q, 1);
    //printmpz(q1);
    mpz_t phi;
    mpz_init(phi);
    mpz_mul(phi, p1, q1);
    //printmpz(phi);

    // Usually e should be coprime with phi. So e can be prime like 3, 7,
    // but choosing the large prime is better
    mpz_t e;
    mpz_init(e);
    // 2 ^ 16 + 1 = 65537 // A prime number.
    mpz_set_str(e, "65537", 10); 
    //printmpz(e);
    memset(szBuf, 0, sizeof(szBuf));
    // gmp_printf("%Zd\n", e); This was not working.
    gmp_sprintf(szBuf, "%Zd", e);
    cout << "e = " << szBuf << " (PUBLIC KEY)" << endl << endl;

    // d = (e ^ -1) mod phi. d is the inverse of e mod phi.
    mpz_t d;
    mpz_init(d);
    //mpz_powm_ui(d, e, -1, phi); // This was giving wrong result. It worked for small number.
    mpz_invert(d, e, phi); // So I used mpz_invert to sinf the inverse of e.
    //printmpz(d);
    memset(szBuf, 0, sizeof(szBuf));
    gmp_sprintf(szBuf, "%Zd", d);
    cout << "d = " << szBuf << " (PRIVATE KEY)" << endl << endl;

    // Select a message and convert the message to hexa decimal value of each
    // character and store it in szAsciiData. G = 47 etc.. Instead of the
    // it can be any Symmetry key.
    string szMsg = { "God is good all the time. All the time God is good." };
    cout << "msg = " << szMsg.c_str() << " (MESSAGE)" << endl; // Print the actual message.
    string szAsciiData = StrToHex(szMsg);

    // Convert the hexa decimal message to mpz.
    mpz_t msg;
    mpz_init_set_str(msg, szAsciiData.c_str(), 16);
    memset(szBuf, 0, sizeof(szBuf));
    gmp_sprintf(szBuf, "%Zx", msg);
    cout << "msg = " << szBuf << " (HEX MESSAGE)" << endl << endl; // Print the hexa decimal message value.

    // Enrypt the message using the PUBLIC KEY e such that
    // enc = (msg ^ e) mod n
    mpz_t enc;
    mpz_init(enc);
    mpz_powm(enc, msg, e, n);
    memset(szBuf, 0, sizeof(szBuf));
    gmp_sprintf(szBuf, "%Zd", enc);
    cout << "enc = " << szBuf << " (ENCRYPTED MESSAGE)" << endl << endl; // Print the encrypted message value in decimal.

    // Decrypte the encrypted message enc using the PRIVATE KEY d such that
    // dec = (enc ^ d) mod n
    mpz_t dec;
    mpz_init(dec);
    mpz_powm(dec, enc, d, n);
    memset(szBuf, 0, sizeof(szBuf));
    gmp_sprintf(szBuf, "%Zx", dec);
    cout << "dec = " << szBuf << " (DECRYPTED MESSAGE)" << endl; // Print the hexa decimal decrypted message value.
    // It should be same as the actual hexa decimal original message.

    // Print the decrypted message.
    szMsg = "";
    szMsg = HexToStr(szBuf);
    cout << "msg = " << szMsg.c_str() << " (MESSAGE)" << endl;

    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);

    mpz_clear(p1);
    mpz_clear(q1);
    mpz_clear(phi);

    mpz_clear(e);
    mpz_clear(d);

    mpz_clear(msg);
    mpz_clear(enc);
    mpz_clear(dec);

    /*mpz_t rop;
    mpz_init(rop);
    mpz_nextprime(rop, integ);
    //gmp_printf("%Zd\n", rop);
    memset(szBuf, 0, 100);
    gmp_sprintf(szBuf, "%Zd\n", rop);
    cout << szBuf << endl;

    mpz_clear(rop);
    mpz_clear(integ);*/
}