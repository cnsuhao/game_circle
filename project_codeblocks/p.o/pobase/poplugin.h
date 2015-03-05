#ifndef POPLUGIN_H
#define POPLUGIN_H
#include "../handle.h"
#include <string>
#include <iostream>
class PO;
class POGI;
class POPlugin:public HandleSeed
{
public:
    virtual void Init(POGI*)=0;
    virtual void Set(std::string){std::cout<<"can't no t run set."<<std::endl;}
};

#endif // POPLUGIN_H
