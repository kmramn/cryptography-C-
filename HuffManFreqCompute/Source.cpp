
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>

#include <map>
#include <utility>
using namespace std;

typedef map<unsigned char, int> CHTOINT;
typedef map<int, unsigned char> INTTOCH;
void _tmain()
{
    FILE* pFile1 = NULL;
    pFile1 = fopen("ptext.txt", "r");
    CHTOINT chrFreq;

    int nTotalCount = 0;
    int nTotalPrintableChar = 0;
    while (!feof(pFile1))
    {
        unsigned char ch;
        fread(&ch, 1, 1, pFile1);

        CHTOINT::iterator itr1 = chrFreq.find(ch);
        int nVal = 0;
        if (itr1 != chrFreq.end())
            nVal = itr1->second++;
        else
            nVal = 1;

        chrFreq.insert(make_pair(tolower(ch), nVal));
        nTotalCount++;
        if (ch > 31 && ch < 127)
            nTotalPrintableChar++;
    }
    fclose(pFile1);

    printf("Total Char: %d\nTotalPrintable  Characters: %d\n", nTotalCount, nTotalPrintableChar);
    double dProb = 0.0;
    double dPrct = 0.0;
    double dPiSqProb = 0.0;
    double dPiSqPrct = 0.0;
    for (CHTOINT::iterator itr1 = chrFreq.begin(); itr1 != chrFreq.end(); itr1++)
    {
        if (itr1->first >= 32 && itr1->first < 127)
        {
            dProb = ((double)itr1->second / nTotalPrintableChar);
            dPrct = (((double)(itr1->second * 100)) / nTotalPrintableChar);
            //dProb = ((double)itr1->second / nTotalCount);
            //dPrct = (((double)(itr1->second * 100)) / nTotalCount);
            printf("%c(%03d) - %06d - probability - %.10lf, percentage - %.10lf %%\n", itr1->first, itr1->first, itr1->second,
                dProb, dPrct);
            dPiSqProb += (dProb * dProb);
            dPiSqPrct += (dPrct * dPrct);
        }
        //else
        //    printf("%d - %c(%03d) - probability - 0.000, percentage - 0.00 %%\n", itr1->first, itr1->second, itr1->second);
    }
    printf("%c(Pi2) = %lf - %lf %%\n(1 / 255 = %lf) (1 / 95 = %lf)\n", 0xE4, dPiSqProb, dPiSqPrct, (double)1 / 256, (double)1 / 95);

    /*INTTOCH chrSortFreq;
    for (CHTOINT::iterator itr1 = chrFreq.begin(); itr1 != chrFreq.end(); itr1++)
    {
        chrSortFreq.insert(make_pair(itr1->second, itr1->first));
    }*/

    /*printf("Total Characters: %d\n", nTotalCount);
    for (INTTOCH::iterator itr1 = chrSortFreq.begin(); itr1 != chrSortFreq.end(); itr1++)
    {
        printf("%d - %c(%02d) - probability - %.3lf, percentage - %.2lf %%\n", itr1->first, itr1->second, itr1->second,
            (double)itr1->first / nTotalCount, ((double)itr1->first * 100) / nTotalCount);
    }*/

    /*printf("TotalPrintable  Characters: %d\n", nTotalPrintableChar);
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
