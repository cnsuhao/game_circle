#include <iostream>
using namespace std;
#include "tank.h"

int main()
{
    Tank<int> TI;
    for(int i=0;i<10;++i)
        TI.PushBack(i);
    for(Tank<int>::Ladle Po=TI.Begin();!TI.IsEnd(Po);++Po)
    {
        cout<<*Po<<endl;
    }
    for(Tank<int>::Ladle Po=TI.Begin();!TI.IsEnd(Po);++Po)
    {
        cout<<*Po<<endl;
    }
}
