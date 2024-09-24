
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <vector>

using namespace std;

typedef struct
{
    wchar_t wszCypher;
    wchar_t wszMsg;
} CYPHERMSG;

typedef struct
{
    wchar_t wszMsg1;
    wchar_t wszMsg2;
} DMSG;

typedef struct
{
    CYPHERMSG wszCypherMsg1;
    CYPHERMSG wszCypherMsg2;
    DMSG Msg;
} COMBINATIONMSG;

//BB  3A 65 F6 F0 03 4F  A9 57 F6 A7 67 69  9C E7 FA BA 85 5A  FB 4F 2B 52 0A EA  D6 12 94 4A 80 1E
//BA  7F 24 F2 A3 53 57  A0 5C B8 A1 67 62  C5 A6 AA AC 92 4A  E6 44 7F 06 08 A3  D1 13 88 56 9A 1E
//A6  72 61 BB B3 06 51  BA 5C F6 BA 29 7E  D0 E7 B4 E9 89 4A  A9 5E 30 02 47 F0  C0 02 8F 40 9A 1E
//A5  72 61 F5 F0 00 4B  A7 4C F4 AA 29 79  D9 A6 B7 AC 85 4D  A9 5E 30 52 03 EC  85 15 95 4C 9D 0F
//BB  3A 70 F3 B9 1D 48  E8 4D F0 AB 70 2E  CF EE B5 BC 8C 5D  A9 4C 30 1E 0B EC  D2 41 95 4C 83 1E
//A6  72 6D E8 F0 1A 50  E8 49 ED BC 6C 7C  9C F2 B2 A8 8E 19  FD 42 3E 06 47 EC  CB 04 DD 4C 9D 1E
//BC  75 70 BB BF 1D 46  E8 5A F9 AA 6C 7A  9C EF A9 E9 82 5C  FD 5E 3A 00 47 F7  CD 00 93 05 A7 1E

//? am p?a?n?ng a s?cr?t missio
//?e is ?h? ?nly pe?so? to trus
//?he cu?r?n? plan ?s ?op secre
//?hen s?o?l? we me?t ?o do thi
//? thin? ?h?y shou?d ?ollow hi
//?his i? ?u?er tha? t?at one i
//?ot on? ?a?et is ?et?er than
//
//I am planning a secret missio
//He is the only person to trus
//The current plan is top secre
//Then should we meet to do thi
//I think they should follow hi
//This is purer than that one i
//Not one cadet is better than
//

void _tmain()
{
    //CYPHERMSG wszCypher[][1] = { { 0x66, 0 }, { 0x32, 0 }, { 0x23, 0 } };
    //COMBINATIONMSG CombMsg[3];

    //CYPHERMSG wszCypher[][1] = { { 0xBB, 0 }, { 0xBA, 0 }, { 0xA6, 0 }, { 0xA5, 0 }, { 0xBB, 0 }, { 0xA6, 0 }, { 0xBC, 0 } };
    CYPHERMSG wszCypher[][31] = {
        { { 0xBB, 0 }, { 0x3A, 0 }, { 0x65, 0 }, { 0xF6, 0 }, { 0xF0, 0 }, { 0x03, 0 }, { 0x4F, 0 }, { 0xA9, 0 }, { 0x57, 0 }, { 0xF6, 0 }, { 0xA7, 0 }, { 0x67, 0 }, { 0x69, 0 }, { 0x9C, 0 }, { 0xE7, 0 }, { 0xFA, 0 }, { 0xBA, 0 }, { 0x85, 0 }, { 0x5A, 0 }, { 0xFB, 0 }, { 0x4F, 0 }, { 0x2B, 0 }, { 0x52, 0 }, { 0x0A, 0 }, { 0xEA, 0 }, { 0xD6, 0 }, { 0x12, 0 }, { 0x94, 0 }, { 0x4A, 0 }, { 0x80, 0 }, { 0x1E, 0 } },
        { { 0xBA, 0 }, { 0x7F, 0 }, { 0x24, 0 }, { 0xF2, 0 }, { 0xA3, 0 }, { 0x53, 0 }, { 0x57, 0 }, { 0xA0, 0 }, { 0x5C, 0 }, { 0xB8, 0 }, { 0xA1, 0 }, { 0x67, 0 }, { 0x62, 0 }, { 0xC5, 0 }, { 0xA6, 0 }, { 0xAA, 0 }, { 0xAC, 0 }, { 0x92, 0 }, { 0x4A, 0 }, { 0xE6, 0 }, { 0x44, 0 }, { 0x7F, 0 }, { 0x06, 0 }, { 0x08, 0 }, { 0xA3, 0 }, { 0xD1, 0 }, { 0x13, 0 }, { 0x88, 0 }, { 0x56, 0 }, { 0x9A, 0 }, { 0x1E, 0 } },
        { { 0xA6, 0 }, { 0x72, 0 }, { 0x61, 0 }, { 0xBB, 0 }, { 0xB3, 0 }, { 0x06, 0 }, { 0x51, 0 }, { 0xBA, 0 }, { 0x5C, 0 }, { 0xF6, 0 }, { 0xBA, 0 }, { 0x29, 0 }, { 0x7E, 0 }, { 0xD0, 0 }, { 0xE7, 0 }, { 0xB4, 0 }, { 0xE9, 0 }, { 0x89, 0 }, { 0x4A, 0 }, { 0xA9, 0 }, { 0x5E, 0 }, { 0x30, 0 }, { 0x02, 0 }, { 0x47, 0 }, { 0xF0, 0 }, { 0xC0, 0 }, { 0x02, 0 }, { 0x8F, 0 }, { 0x40, 0 }, { 0x9A, 0 }, { 0x1E, 0 } },
        { { 0xA5, 0 }, { 0x72, 0 }, { 0x61, 0 }, { 0xF5, 0 }, { 0xF0, 0 }, { 0x00, 0 }, { 0x4B, 0 }, { 0xA7, 0 }, { 0x4C, 0 }, { 0xF4, 0 }, { 0xAA, 0 }, { 0x29, 0 }, { 0x79, 0 }, { 0xD9, 0 }, { 0xA6, 0 }, { 0xB7, 0 }, { 0xAC, 0 }, { 0x85, 0 }, { 0x4D, 0 }, { 0xA9, 0 }, { 0x5E, 0 }, { 0x30, 0 }, { 0x52, 0 }, { 0x03, 0 }, { 0xEC, 0 }, { 0x85, 0 }, { 0x15, 0 }, { 0x95, 0 }, { 0x4C, 0 }, { 0x9D, 0 }, { 0x0F, 0 } },
        { { 0xBB, 0 }, { 0x3A, 0 }, { 0x70, 0 }, { 0xF3, 0 }, { 0xB9, 0 }, { 0x1D, 0 }, { 0x48, 0 }, { 0xE8, 0 }, { 0x4D, 0 }, { 0xF0, 0 }, { 0xAB, 0 }, { 0x70, 0 }, { 0x2E, 0 }, { 0xCF, 0 }, { 0xEE, 0 }, { 0xB5, 0 }, { 0xBC, 0 }, { 0x8C, 0 }, { 0x5D, 0 }, { 0xA9, 0 }, { 0x4C, 0 }, { 0x30, 0 }, { 0x1E, 0 }, { 0x0B, 0 }, { 0xEC, 0 }, { 0xD2, 0 }, { 0x41, 0 }, { 0x95, 0 }, { 0x4C, 0 }, { 0x83, 0 }, { 0x1E, 0 } },
        { { 0xA6, 0 }, { 0x72, 0 }, { 0x6D, 0 }, { 0xE8, 0 }, { 0xF0, 0 }, { 0x1A, 0 }, { 0x50, 0 }, { 0xE8, 0 }, { 0x49, 0 }, { 0xED, 0 }, { 0xBC, 0 }, { 0x6C, 0 }, { 0x7C, 0 }, { 0x9C, 0 }, { 0xF2, 0 }, { 0xB2, 0 }, { 0xA8, 0 }, { 0x8E, 0 }, { 0x19, 0 }, { 0xFD, 0 }, { 0x42, 0 }, { 0x3E, 0 }, { 0x06, 0 }, { 0x47, 0 }, { 0xEC, 0 }, { 0xCB, 0 }, { 0x04, 0 }, { 0xDD, 0 }, { 0x4C, 0 }, { 0x9D, 0 }, { 0x1E, 0 } },
        { { 0xBC, 0 }, { 0x75, 0 }, { 0x70, 0 }, { 0xBB, 0 }, { 0xBF, 0 }, { 0x1D, 0 }, { 0x46, 0 }, { 0xE8, 0 }, { 0x5A, 0 }, { 0xF9, 0 }, { 0xAA, 0 }, { 0x6C, 0 }, { 0x7A, 0 }, { 0x9C, 0 }, { 0xEF, 0 }, { 0xA9, 0 }, { 0xE9, 0 }, { 0x82, 0 }, { 0x5C, 0 }, { 0xFD, 0 }, { 0x5E, 0 }, { 0x3A, 0 }, { 0x00, 0 }, { 0x47, 0 }, { 0xF7, 0 }, { 0xCD, 0 }, { 0x00, 0 }, { 0x93, 0 }, { 0x05, 0 }, { 0xA7, 0 }, { 0x1E, 0 } },
    };
    COMBINATIONMSG CombMsg[21];

    wcout << sizeof(CombMsg) << endl;
    wcout << sizeof(COMBINATIONMSG) << endl;
    wcout << sizeof(CombMsg) / sizeof(COMBINATIONMSG) << endl;
    DWORD dwCypherSize = sizeof(CombMsg) / sizeof(COMBINATIONMSG);
    wcout << _countof(wszCypher) << endl;
    wcout << _countof(wszCypher[0]) << endl;
    for (int m = 0; m < _countof(wszCypher[0]); m++)
    {
        SecureZeroMemory(CombMsg, sizeof(CombMsg));
        int k = 0;
        for (int i = 0; i < _countof(wszCypher) - 1; i++)
        {
            for (int j = i + 1; j < _countof(wszCypher); j++)
            {
                if (wszCypher[i][m].wszCypher != wszCypher[j][m].wszCypher)
                {
                    CombMsg[k].wszCypherMsg1.wszCypher = wszCypher[i][m].wszCypher;
                    CombMsg[k].wszCypherMsg2.wszCypher = wszCypher[j][m].wszCypher;
                    wchar_t wszCypherXOR = wszCypher[i][m].wszCypher ^ wszCypher[j][m].wszCypher;
                    if (wszCypherXOR >> 6)
                    {
                        CombMsg[k].Msg.wszMsg1 = L' ';
                        CombMsg[k].Msg.wszMsg2 = wszCypherXOR ^ L' ';
                    }
                    k++;
                }
            }
        }

        for (int i = 0; i < dwCypherSize; i++)
        {
            if (!CombMsg[i].Msg.wszMsg1)
            {
                CYPHERMSG wszGetChar[4];
                for (int k = 0; k < dwCypherSize; k++)
                {
                    if ((CombMsg[k].wszCypherMsg1.wszCypher == CombMsg[i].wszCypherMsg1.wszCypher ||
                        CombMsg[k].wszCypherMsg2.wszCypher == CombMsg[i].wszCypherMsg1.wszCypher) &&
                        CombMsg[k].Msg.wszMsg1 != 0)
                    {
                        wszGetChar[0].wszCypher = CombMsg[i].wszCypherMsg1.wszCypher;
                        wszGetChar[0].wszMsg = CombMsg[k].Msg.wszMsg2;
                        wchar_t wchOther = (CombMsg[k].wszCypherMsg1.wszCypher == CombMsg[i].wszCypherMsg1.wszCypher) ?
                            CombMsg[k].wszCypherMsg1.wszCypher : CombMsg[k].wszCypherMsg2.wszCypher;
                        for (int l = 0; l < dwCypherSize; l++)
                        {
                            if ((CombMsg[l].wszCypherMsg1.wszCypher == wchOther ||
                                CombMsg[l].wszCypherMsg2.wszCypher == wchOther) &&
                                CombMsg[l].Msg.wszMsg1 != 0)
                            {
                                wszGetChar[1].wszCypher = CombMsg[i].wszCypherMsg1.wszCypher;
                                wszGetChar[1].wszMsg = CombMsg[k].Msg.wszMsg1;
                            }
                        }
                        //break;
                    }
                }
                for (int k = 0; k < dwCypherSize; k++)
                {
                    if ((CombMsg[k].wszCypherMsg1.wszCypher == CombMsg[i].wszCypherMsg2.wszCypher ||
                        CombMsg[k].wszCypherMsg2.wszCypher == CombMsg[i].wszCypherMsg2.wszCypher) &&
                        CombMsg[k].Msg.wszMsg1 != 0)
                    {
                        wszGetChar[2].wszCypher = CombMsg[i].wszCypherMsg2.wszCypher;
                        wszGetChar[2].wszMsg = CombMsg[k].Msg.wszMsg2;
                        wchar_t wchOther = (CombMsg[k].wszCypherMsg1.wszCypher == CombMsg[i].wszCypherMsg2.wszCypher) ?
                            CombMsg[k].wszCypherMsg1.wszCypher : CombMsg[k].wszCypherMsg2.wszCypher;
                        for (int l = 0; l < dwCypherSize; l++)
                        {
                            if ((CombMsg[l].wszCypherMsg1.wszCypher == wchOther ||
                                CombMsg[l].wszCypherMsg2.wszCypher == wchOther) &&
                                CombMsg[l].Msg.wszMsg1 != 0)
                            {
                                wszGetChar[3].wszCypher = CombMsg[i].wszCypherMsg1.wszCypher;
                                wszGetChar[3].wszMsg = CombMsg[k].Msg.wszMsg1;
                            }
                        }
                        //break;
                    }
                }

                for (int j = 0; j < _countof(wszCypher); j++)
                {
                    if (wszCypher[j][m].wszCypher == wszGetChar[0].wszCypher)
                        wszCypher[j][m].wszMsg = wszGetChar[0].wszMsg;
                    else if (wszCypher[j][m].wszCypher == wszGetChar[1].wszCypher)
                        wszCypher[j][m].wszMsg = wszGetChar[1].wszMsg;
                    else if (wszCypher[j][m].wszCypher == wszGetChar[2].wszCypher)
                        wszCypher[j][m].wszMsg = wszGetChar[1].wszMsg;
                    else if (wszCypher[j][m].wszCypher == wszGetChar[3].wszCypher)
                        wszCypher[j][m].wszMsg = wszGetChar[1].wszMsg;
                }
                /*for (int j = 0; j < _countof(wszCypher); j++)
                {
                    if (!wszCypher[j][m].wszMsg)
                        wszCypher[j][m].wszMsg = L' ';
                }*/
            }
        }
    }

    for (int i = 0; i < _countof(wszCypher); i++)
    {
        for (int l = 0; l < _countof(wszCypher[0]); l++)
        {
            //wprintf(L"[%02X : %c]\n", wszCypher[i][l].wszCypher, wszCypher[i][l].wszMsg);
            if (wszCypher[i][l].wszMsg != 0)
                wprintf(L"%c", wszCypher[i][l].wszMsg);
            else
                wprintf(L"?");
        }
        wprintf(L"\n");
    }
}
