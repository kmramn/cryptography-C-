
#include <Windows.h>
#include <winerror.h>

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <tchar.h>
#include <strsafe.h>

void wmain()
{
    wstring wszKey = { L"9y-J$iJYU!Gf>n`rW05g>,+X0I6_iHN)4'ngU'jB_Mfj&kO>sJX);x|g0R4" };
    vector<wstring> vecwszMsg = {
        L"I have seen the tender love that God has for His people and",
        L" it is very great I saw angels over the saints with their w",
        L"ings spread about them Each saint had an attending angel If",
        L" the saints wept through discouragement or were in danger t",
        L"he angels that ever attended them would fly quickly upward ",
        L"to carry the tidings and the angels in the city would cease",
        L" to sing Then Jesus would commission another angel to desce",
        L"nd to encourage watch over and try to keep them from going ",
        L"out of the narrow path but if they did not take heed to the",
        L" watchful care of these angels and would not be comforted b",
        L"y them but continued to go astray the angels would look sad",
        L" and weep They would bear the tidings upward and all the an",
        L"gels in the city would weep and then with a loud voice say ",
        L"Amen But if the saints fixed their eyes upon the prize befo",
        L"re them and glorified God by praising Him then the angels w",
        L"ould bear the glad tidings to the city and the angels in th",
        L"e city would touch their golden harps and sing with a loud ",
        L"voice Alleluia and the heavenly arches would ring with thei",
        L"r lovely songs This r quotes from seventh day adventistamen"
    };

    for (int i = 0; i < vecwszMsg.size(); i++)
    {
        int nKeySize = wszKey.size();
        wprintf(L"{ ");
        for (int j = 0; j < nKeySize; j++)
        {
            //wprintf(L"0x%02X,", vecwszMsg[i][j] ^ wszKey[j]);
            wprintf(L"%c", vecwszMsg[i][j] ^ wszKey[j]);
        }
        wprintf(L"},");
        wprintf(L"\n");
    }
}
