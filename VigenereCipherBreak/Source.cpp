
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <conio.h>

#include <map>
#include <utility>
using namespace std;

typedef struct
{
    int nTotalChar;
    int nTotPrintChar;
} TOTCHAR;

typedef map<unsigned char, int> CHTOINT;
typedef map<int, CHTOINT> TOTTOMAP;
typedef map<int, unsigned char> INTTOCH;
void GetEnglishFrequency(TOTTOMAP& TotEngCharFreq)
{
    FILE* pFile1 = NULL;
    pFile1 = fopen("ptext.txt", "r");

    CHTOINT EngCharFreq;
    TOTCHAR totChar = {0, 0};

    int nTotalCount = 0;
    int nTotalPrintableChar = 0;
    while (!feof(pFile1))
    {
        unsigned char ch;
        fread(&ch, 1, 1, pFile1);

        CHTOINT::iterator itr1 = EngCharFreq.find(ch);
        int nVal = 0;
        if (itr1 != EngCharFreq.end())
            nVal = itr1->second++;
        else
            nVal = 1;

        EngCharFreq.insert(make_pair(tolower(ch), nVal));
        totChar.nTotalChar++;
        if (ch > 31 && ch < 127)
            totChar.nTotPrintChar++;
    }
    TotEngCharFreq.insert(make_pair(totChar.nTotalChar, EngCharFreq));
    fclose(pFile1);
}

void PrintEngCharFreq(const TOTTOMAP& TotEngCharFreq, bool bPrintDetail = false)
{
    int nTotalCount = 0;
    int nTotalPrintableChar = 0;

    double dProb = 0.0;
    double dPrct = 0.0;
    double dPiSqProb = 0.0;
    double dPiSqPrct = 0.0;
    TOTTOMAP::const_iterator itr = TotEngCharFreq.begin();
    for (CHTOINT::const_iterator itr1 = itr->second.begin(); itr1 != itr->second.end(); itr1++)
    {
        nTotalCount++;
        if (itr1->first >= 32 && itr1->first < 127)
        {
            //dProb = ((double)itr1->second / g_totChar.nTotPrintChar);
            //dPrct = (((double)(itr1->second * 100)) / g_totChar.nTotPrintChar);
            dProb = ((double)itr1->second / itr->first);
            dPrct = (((double)(itr1->second * 100)) / itr->first);
            if (bPrintDetail)
                printf("%c(%03d) - %06d - probability - %.10lf, percentage - %.10lf %%\n", itr1->first, itr1->first, itr1->second,
                    dProb, dPrct);
            dPiSqProb += (dProb * dProb);
            dPiSqPrct += (dPrct * dPrct);
            nTotalPrintableChar++;
        }
        //else
        //    printf("%d - %c(%03d) - probability - 0.000, percentage - 0.00 %%\n", itr1->first, itr1->second, itr1->second);
    }
    printf("Total Char: %d\nTotalPrintable  Characters: %d\n", nTotalCount, nTotalPrintableChar);
    printf("%c(Pi2) = %lf - %lf %%\n(1 / 255 = %lf) (1 / 95 = %lf)\n", 0xE4, dPiSqProb, dPiSqPrct, (double)1 / 256, (double)1 / 95);

    /*INTTOCH chrSortFreq;
    for (CHTOINT::iterator itr1 = chrFreq.begin(); itr1 != chrFreq.end(); itr1++)
    {
        chrSortFreq.insert(make_pair(itr1->second, itr1->first));
    }

    printf("Total Characters: %d\n", nTotalCount);
    for (INTTOCH::iterator itr1 = chrSortFreq.begin(); itr1 != chrSortFreq.end(); itr1++)
    {
        printf("%d - %c(%02d) - probability - %.3lf, percentage - %.2lf %%\n", itr1->first, itr1->second, itr1->second,
            (double)itr1->first / nTotalCount, ((double)itr1->first * 100) / nTotalCount);
    }

    printf("TotalPrintable  Characters: %d\n", nTotalPrintableChar);
    double dProb = 0.0;
    double dPrct = 0.0;
    double dPiSqProb = 0.0;
    double dPiSqPrct = 0.0;
    for (INTTOCH::iterator itr1 = chrSortFreq.begin(); itr1 != chrSortFreq.end(); itr1++)
    {
        if (itr1->second > 32 && itr1->second < 127)
        {
            dProb = ((double)itr1->first / nTotalPrintableChar);
            dPrct = (((double)(itr1->first * 100)) / nTotalPrintableChar);
            printf("%06d - %c(%03d) - probability - %.10lf, percentage - %.10lf %%\n", itr1->first, itr1->second, itr1->second,
                dProb, dPrct);
            dPiSqProb += (dProb * dProb);
            dPiSqPrct += (dPrct * dPrct);
        }
        //else
        //    printf("%d - %c(%03d) - probability - 0.000, percentage - 0.00 %%\n", itr1->first, itr1->second, itr1->second);
    }*/
}

int ReadFile(const WCHAR* wszFile, BYTE** byBuff)
{
    FILE* pCFile = NULL;

    pCFile = _wfopen(wszFile, L"r");
    fseek(pCFile, 0, SEEK_END);
   long lNoBytes = ftell(pCFile);
   *byBuff = (BYTE*)malloc(lNoBytes + 1);
   SecureZeroMemory(*byBuff, lNoBytes + 1);
   fseek(pCFile, 0, SEEK_SET);
    size_t stSize = fread(*byBuff, 1, lNoBytes, pCFile);
    //g_nTotSize = stSize / 2;
    //printf("%s\n", *byBuff);
    fclose(pCFile);
    return lNoBytes;
}

void HEXToAscii(BYTE* byBuff, BYTE* byBuffAscii)
{
    int nTotalCount = 0;
    while (*byBuff)
    {
        UCHAR ch;
        UINT unVal;
        sscanf((char*)byBuff, "%02X", &unVal);
        ch = unVal;
        *byBuffAscii = ch;
        byBuffAscii++;
        byBuff += 2;
        nTotalCount++;
    }
}

int FindKeyLength(BYTE* byBuff)
{
    return 0;
}

BOOL IsMatching(const TOTTOMAP& DycCharFreq, const TOTTOMAP& EngCharFreq)
{
    BOOL bRet = TRUE;
    TOTTOMAP::const_iterator dycitr1 = DycCharFreq.begin();
    TOTTOMAP::const_iterator engitr1 = EngCharFreq.begin();
    double SumOfQIPI = 0.0;
    for (CHTOINT::const_iterator dycitr2 = dycitr1->second.begin(); dycitr2 != dycitr1->second.end(); dycitr2++)
    {
        double QI = ((double)dycitr2->second / dycitr1->first);
        CHTOINT::const_iterator engitr2 = engitr1->second.find(dycitr2->first);
        double PI = 0.0;
        if (engitr2 != engitr1->second.end())
            PI = ((double)engitr2->second / engitr1->first);

        SumOfQIPI += (QI * PI);
    }

    if (SumOfQIPI < 0.057)
        bRet = FALSE;

    return bRet;
}

void FindKey(BYTE* byBuff, BYTE* byKey, int nKeyLength, const TOTTOMAP& totEngCharFreq)
{
    BYTE* byBuffTmp = byBuff;
    int nCryptLen = lstrlenA((LPCSTR)byBuff);
    for (int k = 0; k < nKeyLength; k++)
    {
        byBuff = byBuffTmp + k;
        for (UINT B = 0; B < 255; B++)
        {
            CHTOINT EngCharFreq;
            TOTCHAR totChar = { 0, 0 };
            BOOL bIsValidChar = TRUE;
            byBuff = byBuffTmp + k;
            while ((byBuff - byBuffTmp + k) < nCryptLen)
            {
                UCHAR ucDec = (*byBuff ^ B);

                if (ucDec < 32 || ucDec > 126)
                {
                    bIsValidChar = FALSE;
                    break;
                }

                CHTOINT::iterator itr1 = EngCharFreq.find(ucDec);
                int nVal = 0;
                if (itr1 != EngCharFreq.end())
                    nVal = itr1->second++;
                else
                    nVal = 1;

                EngCharFreq.insert(make_pair(tolower(ucDec), nVal));
                totChar.nTotalChar++;
                totChar.nTotPrintChar++;

                byBuff += nKeyLength;
            }
            if (bIsValidChar)
            {
                TOTTOMAP TotDycCharFreq;
                TotDycCharFreq.insert(make_pair(totChar.nTotPrintChar, EngCharFreq));
                if (IsMatching(TotDycCharFreq, totEngCharFreq))
                {
                    byKey[k] = B;
                    break;
                }
            }
        }
    }
}

void Decrypt(BYTE* byBuff, BYTE* byKey, int nKeyLength)
{
    BYTE* byBuffTmp = byBuff;
    int nCryptLen = lstrlenA((LPCSTR)byBuff);
    for (int i = 0; i < nCryptLen; i++)
    {
        BYTE c1 = *byBuff;
        BYTE k1 = *(byKey + (i % nKeyLength));
        BYTE d1 = c1 ^ k1;
        *byBuff = d1;
        byBuff++;
    }
    printf("%s\n", byBuffTmp);
}

typedef map<UCHAR, int> CHTOINT;
typedef struct
{
    CHTOINT CharCount;
    int nTotCount;
} CHARFREQ;
typedef map<int, CHARFREQ> INTTOQ;

void PrintFrequency(const INTTOQ& CharacterFrequency, bool bPrintDetail = false)
{
    double dTotal = 0.0;
    int i = 0;
    for (INTTOQ::const_iterator itr1 = CharacterFrequency.begin(); itr1 != CharacterFrequency.end(); itr1++, i++)
    {
        //printf("Interval: %d\nTotal Bytes: %d\n", itr1->first, itr1->second.nTotCount);
        double dSumOfFreqSqr = 0.0;
        double dFreq = 0.0;
        double dFreqSqr = 0.0;
        for (CHTOINT::const_iterator itr2 = itr1->second.CharCount.begin(); itr2 != itr1->second.CharCount.end(); itr2++)
        {
            dFreq = ((double)itr2->second / itr1->second.nTotCount);
            //dFreqSqr = ((double)itr2->second / g_nTotSize);
            dFreqSqr = dFreq * dFreq;
            dSumOfFreqSqr += dFreqSqr;
            if (bPrintDetail)
                printf("%c(%02X) : %d / (%d) - > %lf, (%lf)2\n", itr2->first, itr2->first, itr2->second, itr1->second.nTotCount, dFreq, dFreqSqr);
        }
        printf("%cQi%d - %lf\n", 0xE4, i, dSumOfFreqSqr);
        dTotal += dSumOfFreqSqr;
        //_getch();
    }
    printf("Total - %lf\n", dTotal);
    printf("(1 / 255) - %lf\n", (double)1 / 255);
}

void BuildHuffManArray(BYTE* byBuff, int nInterval, INTTOQ& CharacterFrequency)
{
    CHTOINT mpCharFrequency;
    int nTotalChar = 0;
    BYTE* byBuffTmp = byBuff;
    int nBuffLen = lstrlenA((LPCSTR)byBuff);
    for (int i = 0; i < nInterval; i++)
    {
        byBuff = byBuffTmp + i;
        mpCharFrequency.clear();
        int nTotalCount = 0;
        while ((byBuff - byBuffTmp + i) < nBuffLen)
        {
            CHTOINT::iterator itr1 = mpCharFrequency.find(*byBuff);
            int nVal = 0;
            if (itr1 != mpCharFrequency.end())
                nVal = itr1->second++;
            else
                nVal = 1;

            UCHAR uchar = *byBuff;
            mpCharFrequency.insert(make_pair(uchar, nVal));
            byBuff += nInterval;
            nTotalCount++;
            nTotalChar++;
        }
        CHARFREQ stChFreq;
        stChFreq.CharCount = mpCharFrequency;
        stChFreq.nTotCount = nTotalCount;
        CharacterFrequency.insert(make_pair(i, stChFreq));
    }
    int nBuffLen1 = lstrlenA((LPCSTR)byBuff);
}

#include <Shlobj.h>
#pragma comment(lib, "Shell32.lib")

void _tmain()
{
    TOTTOMAP totchrFreq;
    GetEnglishFrequency(totchrFreq);
    PrintEngCharFreq(totchrFreq);

    BYTE* pbyBuff = NULL;
    int nSize = ReadFile(L"ctest.txt", &pbyBuff);

    BYTE* pbyAsciiBuff = (BYTE*)malloc((nSize / 2) + 1);
    SecureZeroMemory(pbyAsciiBuff, (nSize / 2) + 1);
    HEXToAscii(pbyBuff, pbyAsciiBuff);
    if (pbyBuff)
        delete[] pbyBuff;

    INTTOQ mpChatIntervalFreq;
    //for (int i = 1; i <= 13; i++)
    //{
    //    printf("Key Length - %d\n", i);
    //    BuildHuffManArray(pbyAsciiBuff, i, mpChatIntervalFreq);
    //    PrintFrequency(mpChatIntervalFreq);
    //    mpChatIntervalFreq.clear();
    //    _getch();
    //}
    //return;
    mpChatIntervalFreq.clear();
    BuildHuffManArray(pbyAsciiBuff, 7, mpChatIntervalFreq);
    int nBuffLen2 = lstrlenA((LPCSTR)pbyAsciiBuff);
    //PrintFrequency(mpChatIntervalFreq);
    int nBuffLen3 = lstrlenA((LPCSTR)pbyAsciiBuff);
    mpChatIntervalFreq.clear();

    BYTE byKey[13];
    SecureZeroMemory(byKey, 13);
    FindKey(pbyAsciiBuff, byKey, 7, totchrFreq);
    Decrypt(pbyAsciiBuff, byKey, 7);

    /*BYTE* pbyAsciiBuff1 = (BYTE*)malloc((nSize / 2) + 1);
    memcpy(pbyAsciiBuff1, pbyAsciiBuff, (nSize / 2));
    for (int i1 = 33; i1 < 127; i1++)
        for (int i2 = 33; i2 < 127; i2++)
            for (int i3 = 33; i3 < 127; i3++)
                for (int i4 = 33; i4 < 127; i4++)
                    for (int i5 = 33; i5 < 127; i5++)
                        for (int i6 = 33; i6 < 127; i6++)
                            for (int i7 = 33; i7 < 127; i7++)
                            {
                                byKey[0] = i7; byKey[1] = i6; byKey[2] = i5;
                                byKey[3] = i4; byKey[4] = i3; byKey[5] = i2;
                                byKey[6] = i1;
                                printf("%s\n", byKey);
                                Decrypt(pbyAsciiBuff, byKey, 7);
                                memcpy(pbyAsciiBuff, pbyAsciiBuff1, (nSize / 2));
                            }*/

    FILE* pTFile = NULL;
    pTFile = _wfopen(L"ttest.txt", L"wb");
    size_t stSize = fwrite(pbyAsciiBuff, 1, nSize / 2, pTFile);
    fclose(pTFile);

    delete[] pbyAsciiBuff;
}
