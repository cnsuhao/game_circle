#ifndef DIY_AI_H
#define DIY_AI_H
#include "../p.o/handle.h"
#include "../personage/personage.h"
#include "../realm/realm.h"
class AI:public HandleSeed
{
    
    public:
        Handle<Personage> Target;
        virtual void Accessorial(Personage*,Realm*,long){}
        AI(Handle<Personage> P):Target(P){}
};

#endif // AI_H
