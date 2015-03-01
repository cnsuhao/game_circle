#ifndef STARMOVE_H
#define STARMOVE_H
#include "starbase.h"
class StarMove
{
public:
    XYF Force;
    XYF Target;
    void Move(const long int& Time,StarBase *);
    StarMove():Force(0.0,0.0),Target(0.0,0.0){}
    void GetSpeed(const XYF& Tem){Target=Tem;}
    void GetForce(const XYF& Target2){Force+=Target2;}
    void Clean(){Force.Set(0.0,0.0);Target.Set(0.0,0.0);}
    void CleanForce(){Force.Set(0.0,0.0);}
    void CleanAll(){Force.Set(0.0,0.0);Target.Set(0.0,0.0);}
};

void StarMove::Move(const long& Time,StarBase * SB)
{
    Target+=Time/1000.0/SB->Range/SB->Range*Force;
    SB->Location+=Time/1000.0*Target;
}

#endif // STARMOVE_H
