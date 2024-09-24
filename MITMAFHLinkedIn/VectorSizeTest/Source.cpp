
#include <stdio.h>

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

void main()
{
    for (int i = 0; i < 10; i++)
    {
        int j = 0;
        j++;
        cout << j << endl;
    }
    return;
    vector<unsigned char> v1;
    //v1.reserve(0x0000001cffffffff);
    //v1.resize(0x0000017FFFFFFFFull);
    //v1.resize(0x00FFFFFFFFFFFFFFull);
    //cout << v1.max_size() << endl;
    //std::vector<int> large(0x0000000FFFFFFFFull, 0);
    deque<unsigned char> d1;
    d1.resize(0x00FFFFFFFFFFFFFF);
    cout << d1.max_size() << endl;
}