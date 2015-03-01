#ifndef ELVESSPACEBOLISHENSHE_H
#define ELVESSPACEBOLISHENSHE_H
#include "../elvesspace.h"
#include "../../p.o/picture.h"
class Elv_Bolishenshe:public ElvesSpace
{
public:
    Picture P;
    void Init();
    //void ElvesAnalyze(long);
    void ElvesShow(long);
    //int Check(ElvesBase *);
};

void Elv_Bolishenshe::Init()
{
    //error<<""<<endl;
    P.Load("texture/elvesspace/bolishenshe.jpg");
}

void Elv_Bolishenshe::ElvesShow(long T)
{
    P.Show(-1.0,1.0,1.0,-1.0);
    ElvesSpace::ElvesShow(T);
}

#endif // ELVESSPACEBOLISHENSHE_H
