/*
Question 1
In this project you will experiment with a padding oracle attack against a toy web site hosted at
crypto-class.appspot.com .  Padding oracle vulnerabilities affect a wide variety of products,
including secure tokens .
This project will show how they can be exploited.   We discussed CBC padding oracle attacks in
week 4 (segment number 6), but if you want to read more about them, see a short description here
or Vaudenay's paper on this topic.
Now to business. Suppose an attacker wishes to steal secret information from our target web site
crypto-class.appspot.com . The attacker suspects that the web site embeds encrypted customer data
in URL parameters such as this:

http://crypto-class.appspot.com/po?er=f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4

That is, when customer Alice interacts with the site, the site embeds a URL like this in web pages
it sends to Alice. The attacker intercepts the URL listed above and guesses that the ciphertext
following the "po?er=" is a hex encoded AES CBC encryption with a random IV of some secret data
about Alice's session.
After some experimentation the attacker discovers that the web site is vulnerable to a CBC padding
oracle attack. In particular, when a decrypted CBC ciphertext ends in an invalid pad the web server
returns a 403 error code (forbidden request). When the CBC padding is valid, but the message is
malformed, the web server returns a 404 error code (URL not found).
Armed with this information your goal is to decrypt the ciphertext listed above. To do so you can
send arbitrary HTTP requests to the web site of the form

http://crypto-class.appspot.com/po?er="your ciphertext here"

and observe the resulting error code. The padding oracle will let you
decrypt the given ciphertext one byte at a time. To decrypt a single byte you will need to send up
to 256 HTTP requests to the site. Keep in mind that the first ciphertext block is the random IV.
The decrypted message is ASCII encoded.
To get you started here is a short Python script that sends a ciphertext supplied on the command
line to the site and prints the resulting error code. You can extend this script (or write one
from scratch) to implement the padding oracle attack. Once you decrypt the given ciphertext,
please enter the decrypted message in the box below.
This project shows that when using encryption you must prevent padding oracle attacks by either
using encrypt-then-MAC as in EAX or GCM, or if you must use MAC-then-encrypt then ensure that the
site treats padding errors the same way it treats MAC errors.
The Magic Words are Squeamish Ossifrage
*/

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <winerror.h>
#include <tchar.h>
#include <strsafe.h>

#include <iostream>
using namespace std;
#include <stdio.h>

#include <wincrypt.h>
#pragma comment(lib, "advapi32.lib")

#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

void hextostring(unsigned char* uszDestBuffer, unsigned char* uszSrc, int nSize)
{
    for (int i = 0; i < nSize; i++)
    {
        sprintf((char*)uszDestBuffer, "%02x", uszSrc[i]);
        uszDestBuffer += 2;
    }
}

int SendHTTPPacket(unsigned char* uszGetPayload, int nPayloadSize)
{
    int nRet = 0;
    WSADATA wsData;
    WSAStartup(MAKEWORD(2, 2), &wsData);

    unsigned char uszHostURL[] = { "crypto-class.appspot.com" };
    //unsigned char uszHTTPGET[] = { "GET /po?er=%s HTTP/1.1\r\nHost: crypto-class.appspot.com\r\nAccept: */*\r\nContent-Type: text/html\r\n\r\n" };
    unsigned char uszHTTPGET[1024] = { "GET /po?er=%s HTTP/1.1\r\nHost: crypto-class.appspot.com\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nSec-GPC: 1\r\n\r\n" };
    //unsigned char uszHTTPGETBuffer[1024] = { "GET /po?er=f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4 HTTP/1.1\r\nHost: crypto-class.appspot.com\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:100.0) Gecko/20100101 Firefox/100.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\nSec-GPC: 1\r\n\r\n" };
    unsigned char uszHTTPGETBuffer[1024];
    memset(uszHTTPGETBuffer, 0, sizeof(uszHTTPGETBuffer));

    PADDRINFOA addr;
    nRet = getaddrinfo((PCSTR)uszHostURL, "http", NULL, &addr);
    //nRet = getaddrinfo((PCSTR)uszHostURL, NULL, NULL, &addr);
    if (nRet != 0)
        return nRet;

    char szNewPayload[256];
    memset(szNewPayload, 0, sizeof(szNewPayload));
    lstrcpynA(szNewPayload, (LPCSTR)uszGetPayload, nPayloadSize + 1);
    sprintf((char*)uszHTTPGETBuffer, (const char*)uszHTTPGET, szNewPayload);
    //sprintf((char*)uszHTTPGETBuffer, (const char*)uszHTTPGET, uszGetPayload);

    SOCKET sHTTPGET;
    sHTTPGET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sHTTPGET == INVALID_SOCKET)
    {
        freeaddrinfo(addr);
        nRet - WSAGetLastError();
        return nRet;
    }

    nRet = connect(sHTTPGET, addr->ai_addr, addr->ai_addrlen);
    if (nRet == SOCKET_ERROR)
    {
        closesocket(sHTTPGET);
        freeaddrinfo(addr);
        nRet = WSAGetLastError();
        return nRet;
    }

    nRet = send(sHTTPGET, (const char*)uszHTTPGETBuffer, strlen((const char*)uszHTTPGETBuffer), 0);
    if (nRet == SOCKET_ERROR)
    {
        closesocket(sHTTPGET);
        freeaddrinfo(addr);
        nRet = WSAGetLastError();
        return nRet;
    }

    unsigned char uszData[20480];
    memset(uszData, 0, sizeof(uszData));
    nRet = recv(sHTTPGET, (char*)uszData, sizeof(uszData), 0);
    if (nRet == SOCKET_ERROR)
    {
        closesocket(sHTTPGET);
        freeaddrinfo(addr);
        nRet = WSAGetLastError();
        return nRet;
    }
    //unsigned char uszDataSplit1[256];
    //unsigned char uszDataSplit2[256];
    //unsigned char uszDataSplit3[256];
    //memset(uszDataSplit1, 0, sizeof(uszDataSplit1));
    //memset(uszDataSplit2, 0, sizeof(uszDataSplit2));
    //memset(uszDataSplit3, 0, sizeof(uszDataSplit3));
    //sscanf((const char*)uszDataSplit1, (const char*)uszDataSplit2, (const char*)uszDataSplit3, "%s %s %s", uszData);
    uszData[13] = 0;
    nRet = atoi((const char*)&uszData[9]);

    shutdown(sHTTPGET, SD_BOTH);
    closesocket(sHTTPGET);
    freeaddrinfo(addr);
    WSACleanup();
    return nRet;
}

void wmain()
{
    unsigned char ct[4][16] = {
        { 0xf2, 0x0b, 0xdb, 0xa6, 0xff, 0x29, 0xee, 0xd7, 0xb0, 0x46, 0xd1, 0xdf, 0x9f, 0xb7, 0x00, 0x00 },
        { 0x58, 0xb1, 0xff, 0xb4, 0x21, 0x0a, 0x58, 0x0f, 0x74, 0x8b, 0x4a, 0xc7, 0x14, 0xc0, 0x01, 0xbd },
        { 0x4a, 0x61, 0x04, 0x44, 0x26, 0xfb, 0x51, 0x5d, 0xad, 0x3f, 0x21, 0xf1, 0x8a, 0xa5, 0x77, 0xc0 },
        { 0xbd, 0xf3, 0x02, 0x93, 0x62, 0x66, 0x92, 0x6f, 0xf3, 0x7d, 0xbf, 0x70, 0x35, 0xd5, 0xee, 0xb4 }
    };
    unsigned char newCT[4][16] = { /*newCT = newCT^msg^i*/
        { 0xf2, 0x0b, 0xdb, 0xa6, 0xff, 0x29, 0xee, 0xd7, 0xb0, 0x46, 0xd1, 0xdf, 0x9f, 0xb7, 0x00, 0x00 },
        { 0x58, 0xb1, 0xff, 0xb4, 0x21, 0x0a, 0x58, 0x0f, 0x74, 0x8b, 0x4a, 0xc7, 0x14, 0xc0, 0x01, 0xbd },
        { 0x4a, 0x61, 0x04, 0x44, 0x26, 0xfb, 0x51, 0x5d, 0xad, 0x3f, 0x21, 0xf1, 0x8a, 0xa5, 0x77, 0xc0 },
        { 0xbd, 0xf3, 0x02, 0x93, 0x62, 0x66, 0x92, 0x6f, 0xf3, 0x7d, 0xbf, 0x70, 0x35, 0xd5, 0xee, 0xb4 }
    };
    unsigned char msg[3][16] = {
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
    };
    unsigned char uszHexString[(2 * 4 * 16) + 1];
    unsigned char* puszHexString = NULL;
    memset(uszHexString, 0, sizeof(uszHexString));
    unsigned char uszHexStringOri[(2 * 4 * 16) + 1];
    unsigned char* puszHexStringOri = NULL;
    memset(uszHexStringOri, 0, sizeof(uszHexStringOri));
    hextostring(uszHexStringOri, (unsigned char*)ct, 4 * 16);

    // Testing case
    //hextostring(uszHexString, (unsigned char*)newCT, 4 * 16);
    //int nError = SendHTTPPacket(uszHexString);
    //return;

    //wprintf(L"Padding Attack\n");
    //for (int i = 2; i >= 0; i--) // For every cipher text
    for (int i = 0; i < 3 ; i++) // For every cipher text
    {
        //i = 2;
        for (int j = 15; j >= 0; j--) // for every byte in a block
        //for (int j = 0; j < 16; j++) // for every byte in a block
        {
            memcpy(newCT, ct, sizeof(ct));
            for (int k = (15 - j); k > 0; k--) // if message is found then use it to fill in cipher
            {
                newCT[i][16 - k] ^= msg[i][16 - k] ^ (16 - j);
            }
            //for (int k = 0; k < (15 - j); k++)
            //{
            //    newCT[i][15 - k] ^= msg[i][j] ^ (16 - k);
            //}
            //for (int g = 255; g >= 0; g--) // if message not found then try all g
            for (int g = 0; g < 256; g++) // if message not found then try all g
            {
                int nct = ct[i][j];
                int nNewCT = nct ^ g ^ (16 - j);
                newCT[i][j] = nNewCT;
                //newCT[i][j] = g ^ (16 - j);
                // Send the data as http to network and get the error
                hextostring(uszHexString, (unsigned char*)newCT, 4 * 16);
                //int nError = SendHTTPPacket(uszHexString, 2 * (i + 2) * 16);
                puszHexString = uszHexString + 2 * i * 16;
                int nError = SendHTTPPacket(puszHexString, 2 * 2 * 16);
                if (nError == 404)
                {
                    printf("404\n");
                    msg[i][j] = g;
                    //break;
                    if (lstrcmpA((LPSTR)uszHexStringOri, (LPSTR)uszHexString) != 0)
                        break;
                }
                else if (nError == 403)
                {
                    //printf("403\n");
                }
                else if (nError == 200)
                {
                    printf("200\n");
                }
            }
        }
    }
}
