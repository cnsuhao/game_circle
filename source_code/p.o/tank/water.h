#ifndef WATER_H
#define WATER_H
#include "../handle.h"
#include "../publicvalue.h"
template <class TC>
class Water:virtual public HandleSeed
{

public:
    virtual ~Water(){delete Data;}
    TC* Data;
    PublicLock PL;
    Handle<Water> LastPoint;
    Handle<Water> NextPoint;
    Water(){}
    Water(TC& P){Data=new TC(P);}
    Water(const TC& P){Data=new TC(P);}
    TC* operator ->(){return Data;}
    void SetNext(Handle<Water> K){NextPoint=K;}
    void SetLast(Handle<Water> P){LastPoint=P;}
    Handle<Water> Last(){return LastPoint;}
    Handle<Water> Next(){return NextPoint;}
    void Lock(){PL.Lock();}
    void UnLock(){PL.UnLock();}
    void CleanNext(){NextPoint.Unused();}
    void CleanLast(){LastPoint.Unused();}
};
#endif // WATER_H
