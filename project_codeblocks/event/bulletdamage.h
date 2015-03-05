#ifndef BULLRTDAMAGE_H
#define BULLRTDAMAGE_H
#include "event.h"
#include "../base/object.h"
class BulletDamage:public Event
{
public:
    int Damage;
    BulletDamage():Event(0),Damage(100){}
    void Effect(Object*);
};
void BulletDamage::Effect(Object *O)
{
    O->GetState()->JieCao-=Damage;
}

#endif // BULLRTDAMAGE_H
