
#include <Windows.h>
#include <winerror.h>

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <iostream>
#include <vector>
#include <map>
#include <numeric>
using namespace std;

#include <tchar.h>
#include <strsafe.h>

typedef map<uint8_t, double> UN8TOD;

typedef map<uint8_t, unsigned int> UN8TOUI;
typedef struct CHRTBLCNT
{
    UN8TOUI mapChrTable;
    int nChrTotal;
};
typedef vector<CHRTBLCNT> VECKEYLENTBLCNT;
typedef map<int, VECKEYLENTBLCNT> NTOTKEYLENTBLCNT;

const uint8_t unFirstEngChr = 'A';
const uint8_t unLastEngChr = 'Z';
//string g_szEncryptedText("GODISGREATALLTHETIMEALLTHETIMEGODISGREATLOVEISNTJUSTSOMETHINGGODDOESRATHERLOVEORIGINATESFROMHIMITISTHEFOUNDATIONOFHISCHARACTERYOUCANNOTSEGMENTSUBTRACTORALTERITEVERYTHINGGODISINCLUDINGHISJUSTICEANDMERCYISROOTEDINTHISUNALTERABLEFACTGODISLOVEGODISLOVETHEREFOREEVERYDECISIONHEMAKESISCONSISTENTWITHTHISTRUTHANDTHEETERNALDESTINYFOREVERYPERSONWHOHASEVERLIVEDWILLBEFAIRWESOMETIMESGETINTOTROUBLEBYAPPLYINGHUMANLOGICTOSITUATIONSTHATCALLFORDIVINEWISDOMIVEFOUNDGREATSOLACEINJOHNINKNOWINGTHATEVERYTHINGABOUTGODFLOWSFROMANUNALTERABLEREALITYOFPERFECTLOVEDIVINELOVEMAKESITSMOSTTOUCHINGAPPEALSTOTHEHEARTWHENITCALLSUPONUSTOMANIFESTTHESAMETENDERCOMPASSIONTHATCHRISTMANIFESTEDTHATMANONLYWHOHASUNSELFISHLOVEFORHISBROTHERHASTRUELOVEFORGODSUPREMELOVEFORGODANDUNSELFISHLOVEFORONEANOTHERTHISISTHEBESTGIFTTHATOURHEAVENLYFATHERCANBESTOWTHISLOVEISNOTANIMPULSEBUTADIVINEPRINCIPLEAPERMANENTPOWERTHEUNCONSECRATEDHEARTCANNOTORIGINATEORPRODUCEITONLYINTHEHEARTWHEREJESUSREIGNSISITFOUNDWELOVEHIMBECAUSEHEFIRSTLOVEDUS");
//string g_szEncryptedText("IQFKUITGCVCNNVJGVKOGCNNVJGVKOGIQFKUITGCVNQXGKUPVLWUVUQOGVJKPIIQFFQGUTCVJGTNQXGQTKIKPCVGUHTQOJKOKVKUVJGHQWPFCVKQPQHJKUEJCTCEVGTAQWECPPQVUGIOGPVUWDVTCEVQTCNVGTKVGXGTAVJKPIIQFKUKPENWFKPIJKULWUVKEGCPFOGTEAKUTQQVGFKPVJKUWPCNVGTCDNGHCEVIQFKUNQXGIQFKUNQXGVJGTGHQTGGXGTAFGEKUKQPJGOCMGUKUEQPUKUVGPVYKVJVJKUVTWVJCPFVJGGVGTPCNFGUVKPAHQTGXGTARGTUQPYJQJCUGXGTNKXGFYKNNDGHCKTYGUQOGVKOGUIGVKPVQVTQWDNGDACRRNAKPIJWOCPNQIKEVQUKVWCVKQPUVJCVECNNHQTFKXKPGYKUFQOKXGHQWPFITGCVUQNCEGKPLQJPKPMPQYKPIVJCVGXGTAVJKPICDQWVIQFHNQYUHTQOCPWPCNVGTCDNGTGCNKVAQHRGTHGEVNQXGFKXKPGNQXGOCMGUKVUOQUVVQWEJKPICRRGCNUVQVJGJGCTVYJGPKVECNNUWRQPWUVQOCPKHGUVVJGUCOGVGPFGTEQORCUUKQPVJCVEJTKUVOCPKHGUVGFVJCVOCPQPNAYJQJCUWPUGNHKUJNQXGHQTJKUDTQVJGTJCUVTWGNQXGHQTIQFUWRTGOGNQXGHQTIQFCPFWPUGNHKUJNQXGHQTQPGCPQVJGTVJKUKUVJGDGUVIKHVVJCVQWTJGCXGPNAHCVJGTECPDGUVQYVJKUNQXGKUPQVCPKORWNUGDWVCFKXKPGRTKPEKRNGCRGTOCPGPVRQYGTVJGWPEQPUGETCVGFJGCTVECPPQVQTKIKPCVGQTRTQFWEGKVQPNAKPVJGJGCTVYJGTGLGUWUTGKIPUKUKVHQWPFYGNQXGJKODGECWUGJGHKTUVNQXGFWU");
//string g_szEncryptedText("IOILAIRJDBCLQWPGTNPMCLQWPGTNPMIOILAIRJDBNOAHQUNYMCUTXRUGTMLVIGTGLQEXUIVHJUTQVJRZKGNQIVEXIZQMMLUKTNVBJEKRCPDFWQQNTIPKSHKITAHWMTYTXKCNSRBUELPMPTXXJVRFFBQRFOBGRNWMXEWBBJISJOQDNVQPCQXLKNLKQUJZVBKCJDVFMJUKAIXUWQTJGQPTMLAWNFOBGRFETGFFFBIOILANOAHOQDNVTQVJWPGRJIWTEJYMTYIHKKSNRVJERDSGSNVKQNXLAVESWEKTMWPKSYUCVHFQLVHJHBGRSDTFEXWQPYKRZGVJUGREWVWPWMRPCSJYMTLNYMFWNOTDEKDQTWJVWOEYLUGSLHBKNYRBTOZETGBDDXRLDLVIHZPIPLTJQETTVQVUFWQQNXWPCTHDTNFTULKVNQMYIXGWOIAHNQUSGOTEFWAQLFFMKNORPPISNVQWNQOVHFWMXEWBBJISJIDOZWOQDKOWYSKUWOASXVCLYHZCBQHZGAQLBAOKSMTFJFBNOAHLKVNQMNOAHUCKJVQVSRRAVTTXKJISJIRPJDTUTTWPGHJDZVWMHVKTHDTNSZSWPUXWWOASLNGSYWPGSFPMVESGMTCTPXCSXLWPTMDBEHWLAVMFQQHEXWMFTMDBOASRVNYBKWJAXXVUEQIQUHQRDGFTUPKSGUWVHJUPCSYUCGLTYMHOWJWFSZSZGMJOWXEKRZIOIDVFUSVMNFNVPNOAHNQRTQMCNTWPGRYKQUIXWPGBJVBIIKWBJAYRCTHJDDGNQBNCTMHZEASEMUTTZBJIXOWXENVVQTFQQOPZOAGBZWIFIALVGPWLVEIUOMCPJUUCNJQBROBHZVHJXVEOSVMERFWMFHJDZVCFQVQTTUQIISDBGOWSZQDZFMKTTQTAISWPGHJDZVWMHZGJJVCURJLOPSNVQVFTXVFWJOWXEMLUDEHDCUEMHNKRXWTQVJGCUFTUOQDXHVVNTWPKSXRVKNYRBJEBRZNDYRKQNIHUPTMHEQRQGJWTYKIVTMHEQRQGBJRTXOJHNPUKGMWJGSFYMFTMHZGAWHAQUQVEJOFUMVRJPJNISJQPUSEMNIJIBJEDDAMHTZKCNNNVQWYKIVGTGQURJFWPCNOMFTTPMJOBFIPIGHIUSZUMFTMDBJEQRDGSFQLRAWGWPSRHQVIXQWVFTUGQUIHITYTXBJTTPIMEDRCTSJODGSOXAVWNWPIOIMMUUXLVXIYHAAOZWWEORHBQHNPEKTMDTNYTXZDUWGMPSFQLREWSTGXNWQGSFFKGPYWPGPWRUKSJDVFTMHXTOALAKOSWPCTLRLJAXPIFEQRWMABDGHRTPAGLKWWLEXXAHOWLVEHWLAVTMHKJAWDKVEWRNVHJIIVHJUQURJYMCLJGBJEGOWQDTIKJRNVBKNJYMTAGLLKNLHNHIHDKAIXRCTOSOGJOUHNQRYKZQULKPKSRHZKTXDTQNJZMJAAHXCRIRVCNISMCCJWPGCMDZCCYHZQFLRLCSWHDGAQHLDYHKZKSYLVXIYHAQUWIIKTMDVFLTYMHOWZMJAAHIHAYKMTWMRAGMJUKAASGKQMUDAUITQNCIQQWVAYHDGRDVBGPTIWWRORCTNJBPGAAHVYAWGPGWNOTDEBLBJUXWWIUNGMKNJYMTYUHZRLJAQVYYROKVJXAJEQSQPEAHZATJPXVAYLWPYTXZTEFVWPASGQOALLVCTNRVUHTXTFBJWWWCMHLYIYKBJEQLNGGNYQPGUREGRTIKJRNVBVHFWNQRRVWHBJDCVYFQLVRZWPOADEMKMUUMUSJGBJEWHWPTMHZGAWHOTEFWIPDUUMEITXAVRZWPUTMDBFERDVFYTXZEOSWMOPQDBKOSLVQRIHZVHFWGQURDGJAAHIUOZQLHOZQLCTNRVHOWBWWRKDQVHGBPCVNQOCCTUZGCYNVQWQHLIETIOQDTWPCTYKMUUUHZHIHLINVFLVUEJNMTFTUBTUYKEQUQGTGAWQBJAYWPGWTUTFBDZQUDTPPQWJYMTMZFPCCVXQTEINVGWSRBIOILBKSUUWREWWWUEJNBQLJDZPAQOBJAYLAROXVQDLJIZQMSDBWRJECVDTQWVFFLTVOQRWMFWRUPAYXZGTTFPTIXWNQRYKMEORSTGTJUMRRJVMPTFWQQNTIBJEHKITAHWMTOKWPGLNYQPGLRLDYHRVVERSTCTNRVQFHKZKSYEGEOSIWTMNWGVOYKMFIALVGLNNMPEXVGQUWFWPCJSBKOSVWHTMHLKVNQMEHFUIETJUEKLQHFRASGIPDDRCTMNQLCNIKMCRYZQNLGHMNEADBGDWHNKNJGIPDJQVQBQHLNEYWPGYTXBJANPPKGMQWVRJOGKNLXXQNMXUCNBLAFORECVLNYQPGIDGDYIDGCSXHMKNLKQOWMRQUISYQUIGOMFONQOVHJLZYOWNIUISWPGSNJPVOKWPGISWMNLNJMPCJVWHHJDDGNMHEJOHRVUTFQBNYIHXGNIVCROSJWFTMUWWGMVQOPQHBTUXWIPDUUIAEWICNCTQNKDJQKGWNOTDEXXZTOZQLGDGBBJEFQOGLXRNJEFYMPHJZPQLNYMUBDIIKTMLVEHWLAVWNOTDEXWZGNLWPGNJGIPDZSPGLIDJNEYRNKGMWBJELRWFFNJPVOKIIKTMDVFLFBPQLIXXQNJWMTNFOTKFJ");

UN8TOD g_mapundEngFreqTbl = {
    /*{'E', 12.702}, {'T', 9.056}, {'A', 8.167}, {'O', 7.507}, {'I', 6.966}, {'N', 6.749}, {'S', 6.327},
    {'H', 6.094}, {'R', 5.987}, {'D', 4.253}, {'L', 4.025}, {'C', 2.782}, {'U', 2.752}, {'M', 2.406},
    {'W', 2.360}, {'F', 2.228}, {'G', 2.015}, {'Y', 1.974}, {'P', 1.929}, {'B', 1.492}, {'V', 0.978},
    {'K', 0.772}, {'J', 0.153}, {'X', 0.150}, {'Q', 0.095}, {'Z', 0.074}*/
    { 'E', 16.93 }, { 'N', 10.53 }, { 'I', 8.02 }, { 'R', 6.89 }, { 'S', 6.42 }, { 'T', 5.79 }, { 'A', 5.58 }, { 'D', 4.98 }, { 'H', 4.98 }, { 'U', 3.83 }, { 'L', 3.60 }, { 'C', 3.16 }, { 'G', 3.02 }, { 'M', 2.55 }, { 'O', 2.24 }, { 'B', 1.96 }, { 'W', 1.78 }, { 'F', 1.49 }, { 'K', 1.32 }, { 'Z', 1.21 }, { 'V', 0.84 }, { 'P', 0.67 }, { 'Ü', 0.65 }, { 'Ä', 0.54 }, { 'ß', 0.37 }, { 'Ö', 0.30 }, { 'J', 0.24 }, { 'X', 0.05 }, { 'Y', 0.05 }, { 'Q', 0.02 }
};
//UN8TOD g_mapundEngFreqTbl = {
//    {'E', 12.02}, {'T', 9.10}, {'A', 8.12}, {'O', 7.68}, {'I', 7.31}, {'N', 6.95}, {'S', 6.28},
//    {'R', 6.02}, {'H', 5.92}, {'D', 4.32}, {'L', 3.98}, {'U', 2.88}, {'C', 2.71}, {'M', 2.61},
//    {'F', 2.30}, {'Y', 2.11}, {'W', 2.09}, {'G', 2.3}, {'P', 1.8}, {'B', 1.492}, {'V', 1.11},
//    {'K', 0.69}, {'X', 0.17}, {'Q', 0.11}, {'J', 0.10}, {'Z', 0.074}
//};

double MultipleAndSum(const UN8TOD& mapund1, const UN8TOD& mapund2)
{
    const UN8TOD* pmapund1 = &mapund1;
    const UN8TOD* pmapund2 = &mapund2;
    if (mapund1.size() > mapund2.size())
        std::swap(pmapund1, pmapund2);

    double dMultipleAndSum = 0;
    for (UN8TOD::const_iterator itr1 = pmapund1->begin(); itr1 != pmapund1->end(); itr1++)
    {
        UN8TOD::const_iterator itr2 = pmapund2->find(itr1->first);
        if (itr2 != pmapund2->end())
            dMultipleAndSum += (itr1->second * itr2->second);
    }
    return dMultipleAndSum;
}

double AvgSumOfSquresFreq(const VECKEYLENTBLCNT& vecKeyLenFreqTable)
{
    int nKeyPos = 0;
    double dChrSSFreqTot = 0;
    for (VECKEYLENTBLCNT::const_iterator itrFreqTblCount = vecKeyLenFreqTable.begin();
        itrFreqTblCount != vecKeyLenFreqTable.end(); itrFreqTblCount++)
    {
        double dSumOfSquers = 0;
        for (UN8TOUI::const_iterator itrCount = itrFreqTblCount->mapChrTable.begin();
            itrCount != itrFreqTblCount->mapChrTable.end(); itrCount++)
        {
            double dChrFreq = (double)itrCount->second / itrFreqTblCount->nChrTotal;
            dSumOfSquers += (dChrFreq * dChrFreq);
        }
        dChrSSFreqTot += dSumOfSquers;
        wprintf(L"Sig(Q%d) = %lf\n", nKeyPos++, dSumOfSquers);
    }
    double dAvgSumFreqTot = dChrSSFreqTot / vecKeyLenFreqTable.size(); // Average

    return dAvgSumFreqTot;
}

void BuildKeyPosFreqTbl(const vector<uint8_t>& vecEncryptedText, int nKeyLen, int nKeyPos,
    uint8_t unShiftVal, CHRTBLCNT& stFreqTableCount)
{
    int nTmpKeyLen = nKeyLen;
    uint8_t un8Char1;
    // Construct the frequency table for every key position
    for (vector<uint8_t>::const_iterator itrEncryptedText = vecEncryptedText.begin() + nKeyPos;
        itrEncryptedText != vecEncryptedText.end(); std::advance(itrEncryptedText, nTmpKeyLen))
    {
        uint8_t un8Char = *itrEncryptedText;
        if (unShiftVal != 0)
        {
            // Need to generalize to fit other language
            int nNoPostShift = unShiftVal - unFirstEngChr;
            un8Char = *itrEncryptedText - nNoPostShift;
            if (un8Char > unLastEngChr) un8Char = unFirstEngChr + (un8Char - unLastEngChr - 1);
        }

        UN8TOUI::iterator itrFreqCount = stFreqTableCount.mapChrTable.find(un8Char);
        if (itrFreqCount != stFreqTableCount.mapChrTable.end())
        {
            itrFreqCount->second++;
        }
        else
        {
            stFreqTableCount.mapChrTable.insert(make_pair(un8Char, 1));
        }
        stFreqTableCount.nChrTotal++;

        int nIndex = distance(vector<uint8_t>::const_iterator(vecEncryptedText.end()), itrEncryptedText);
        if (nTmpKeyLen > abs(nIndex)) nTmpKeyLen = abs(nIndex); // select the minimum so that it wont
                                                                // crash while using advance.
    }
}

void BuildKeyLenFreqTable(const vector<uint8_t>& vecEncryptedText, int nKeyLen, VECKEYLENTBLCNT& vecKeyLenFreqTable)
{
    for (int nKeyPos = 0; nKeyPos < nKeyLen; nKeyPos++)
    {
        CHRTBLCNT stFreqTableCount;
        stFreqTableCount.mapChrTable.clear();
        stFreqTableCount.nChrTotal = 0;

        BuildKeyPosFreqTbl(vecEncryptedText, nKeyLen, nKeyPos, 0, stFreqTableCount);

        vecKeyLenFreqTable.push_back(stFreqTableCount);
    }
}

int FindKeyLength(const vector<uint8_t>& vecEncryptedText)
{
    int nKeyLength = 0;

    //UN8TOUI mapFrequencyCount;
    NTOTKEYLENTBLCNT mapTotFereqTable;

    for (int nKeyLen = 1; nKeyLen <= 9; nKeyLen++)
    {
        VECKEYLENTBLCNT vecKeyLenFreqTable;
        vecKeyLenFreqTable.clear();

        BuildKeyLenFreqTable(vecEncryptedText, nKeyLen, vecKeyLenFreqTable);

        mapTotFereqTable.insert(make_pair(nKeyLen, vecKeyLenFreqTable));
    }

    double dEnglishSigmaSquare = MultipleAndSum(g_mapundEngFreqTbl, g_mapundEngFreqTbl) / 10000;

    // Calculate Sum of Squares for every key len
    for (NTOTKEYLENTBLCNT::const_iterator itrLenFreq = mapTotFereqTable.begin();
        itrLenFreq != mapTotFereqTable.end(); itrLenFreq++)
    {
        wprintf(L"Key Length %d\n", itrLenFreq->first);

        double dAvgSumFreqTot = AvgSumOfSquresFreq(itrLenFreq->second);

        wprintf(L"Tot Sig(Q) = %lf\n", dAvgSumFreqTot);
        if (dAvgSumFreqTot > dEnglishSigmaSquare) // 0.0655 for English letters
            nKeyLength = itrLenFreq->first;
    }

    return nKeyLength;
}

bool FindKey(const vector<uint8_t>& vecEncryptedText, int nKeyLen, vector<uint8_t>& vecKeyText)
{
    // Calculate the Sum of Square of the whihc is in percentage for the original english character.
    double dEngSumSquare = MultipleAndSum(g_mapundEngFreqTbl, g_mapundEngFreqTbl) / 10000;

    for (int i = 0; i < nKeyLen; i++)
    {
        int B = unFirstEngChr;
        for (B = unFirstEngChr; B <= unLastEngChr; B++)
        {
            CHRTBLCNT stChrTblCnt;
            stChrTblCnt.mapChrTable.clear();
            stChrTblCnt.nChrTotal = 0;

            BuildKeyPosFreqTbl(vecEncryptedText, nKeyLen, i, B, stChrTblCnt);

            UN8TOD mapundChrFreqTblCnt;
            for( UN8TOUI::iterator itrChrTbl = stChrTblCnt.mapChrTable.begin();
                itrChrTbl != stChrTblCnt.mapChrTable.end(); itrChrTbl++)
            {
                mapundChrFreqTblCnt.insert(
                    make_pair(itrChrTbl->first, ((double)itrChrTbl->second * 100/ stChrTblCnt.nChrTotal))
                );
            }

            double dEnchSumSquare = MultipleAndSum(g_mapundEngFreqTbl, mapundChrFreqTblCnt) / 10000;
            wprintf(L"Pos %d, Sig(Q%c) = %lf\n", i, B, dEnchSumSquare);

            //if (dEnchSumSquare >= dEngSumSquare) // Close to English frequency
            if (dEnchSumSquare > 0.05) // Above uniform or 1/g_mapundEngFreqTbl.size() or / 1/26
            {
                wprintf(L"-----\n");
                break;
            }
        }

        if (B <= unLastEngChr)
            vecKeyText[i] = B;
        //_getch();
    }
    return true;
}

void Decrypt(vector<uint8_t>& vecEncryptedText, vector<uint8_t> vecKey)
{
    for (int i = 0; i < vecEncryptedText.size(); i++)
    {
        vecEncryptedText[i] -= (vecKey[i % 5] - unFirstEngChr);
        if (vecEncryptedText[i] < unFirstEngChr) vecEncryptedText[i] = unLastEngChr - (unFirstEngChr - vecEncryptedText[i] - 1);
    }
}

void wmain()
{
    /*string szEncryptedText("IOILAIRJDBCLQWPGTNPMCLQWPGTNPMIOILAIRJDBNOAHQUNYMCUTXRUGTMLVIGTGLQE\
XUIVHJUTQVJRZKGNQIVEXIZQMMLUKTNVBJEKRCPDFWQQNTIPKSHKITAHWMTYTXKCNSRBUELPMPTXXJVRFFBQRFOBGRNWMXE\
WBBJISJOQDNVQPCQXLKNLKQUJZVBKCJDVFMJUKAIXUWQTJGQPTMLAWNFOBGRFETGFFFBIOILANOAHOQDNVTQVJWPGRJIWTE\
JYMTYIHKKSNRVJERDSGSNVKQNXLAVESWEKTMWPKSYUCVHFQLVHJHBGRSDTFEXWQPYKRZGVJUGREWVWPWMRPCSJYMTLNYMFW\
NOTDEKDQTWJVWOEYLUGSLHBKNYRBTOZETGBDDXRLDLVIHZPIPLTJQETTVQVUFWQQNXWPCTHDTNFTULKVNQMYIXGWOIAHNQU\
SGOTEFWAQLFFMKNORPPISNVQWNQOVHFWMXEWBBJISJIDOZWOQDKOWYSKUWOASXVCLYHZCBQHZGAQLBAOKSMTFJFBNOAHLKV\
NQMNOAHUCKJVQVSRRAVTTXKJISJIRPJDTUTTWPGHJDZVWMHVKTHDTNSZSWPUXWWOASLNGSYWPGSFPMVESGMTCTPXCSXLWPT\
MDBEHWLAVMFQQHEXWMFTMDBOASRVNYBKWJAXXVUEQIQUHQRDGFTUPKSGUWVHJUPCSYUCGLTYMHOWJWFSZSZGMJOWXEKRZIO\
IDVFUSVMNFNVPNOAHNQRTQMCNTWPGRYKQUIXWPGBJVBIIKWBJAYRCTHJDDGNQBNCTMHZEASEMUTTZBJIXOWXENVVQTFQQOP\
ZOAGBZWIFIALVGPWLVEIUOMCPJUUCNJQBROBHZVHJXVEOSVMERFWMFHJDZVCFQVQTTUQIISDBGOWSZQDZFMKTTQTAISWPGH\
JDZVWMHZGJJVCURJLOPSNVQVFTXVFWJOWXEMLUDEHDCUEMHNKRXWTQVJGCU");*/
    string szEncryptedText("OAOEPMINGACTPOOPANPOAPIEIEATTHIUDEEENGIOMAREOLGMALEEMNEIAPSIHLTOSNTONIAIACAUOSSUYSRITTIERDPOAFEENPEAOSAOANNOGRUBOOIANDDEOEUORAEATNTPICEARARENMOASSOLRSSTBJCIOEICDIONDIINPENONCAVPTEEVDHOSPANROOASTEACCELAPITCGRONONSSOSIPOONEZEAPMOEPAIIORTRSPATCBDDTAOOOKMJEETEEESNANLPSDCERCEMIOZNDTODDTERACBEFRSZRTSEDMCCASACTAITDORPONOBADMNRTXMNOUAERURCHRAEMBNRINRUNLONOREOLPEEIRCMOOOEEHEOILTSYLQORCEANANXAOTSPOARMTSELAGXMSPNTTETIRNIMRGRPOUORMLISEENEHDETPDOIMANUHIGTNCENOTNOTINERMAOUAMLIAINCPCSEUNCEMBDLSSSAAIEOAEEAFSIEPMATOONSEGCOSEPIRAEEDRBEEPDRODLNDNOIEONRPPNPILAPCOACPICEAXLNKIPLANFTULXREFLX");
    vector<uint8_t> vecun8EncryptedText(szEncryptedText.begin(), szEncryptedText.end());

    int nKeyLength = FindKeyLength(vecun8EncryptedText);

    vector<uint8_t> vecKey;
    vecKey.resize(nKeyLength);
    bool bRet = FindKey(vecun8EncryptedText, nKeyLength, vecKey);

    Decrypt(vecun8EncryptedText, vecKey);
    for (int i = 0; i < vecun8EncryptedText.size(); i++)
    {
        wprintf(L"%C", vecun8EncryptedText[i]);
    }
    wprintf(L"\n");
}
