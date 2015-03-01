#ifndef INFORMATIONVIEWER_H
#define INFORMATIONVIEWER_H
#include "information.h"
#include "tank.h"
#define MaxInformationSize 20
class InformationViewer:virtual public HandleSeed
{
    Tank<Handle<Information> > Library;
public:
    virtual bool Key(){return false;}
    virtual bool Mouse(){return false;}
    virtual bool Window(){return false;}
    virtual bool Special(){return false;}
    virtual bool All(){return false;}
    void GetInformation(Handle<Information>);
    template<class T>
    void Analyze(void (T::*)(Information*),T*);
    void Analyze(void (*)(Information*));
    template<class T>
    void Analyze(void (*)(Information*,T),T);
    template<class T,class B>
    void Analyze(void (T::*)(Information*,B),T*,B);
    InformationViewer(){}
};
void InformationViewer::GetInformation(Handle<Information> K)
{
    Library.PushBack(K);
    if(Library.Size()>=MaxInformationSize)
    {
        Library.PopFront();
    }
}
template<class T>
void InformationViewer::Analyze(void (T::*C)(Information*),T* F)
{
    while(Library.Size()>0)
    {
        Information* P=Library.Begin()->Data;
        (F->*C)(P);
        Library.PopFront();
    }
}
void InformationViewer::Analyze(void (*C)(Information*))
{
    while(Library.Size()>0)
    {
        Information* P=Library.Begin()->Data;
        (*C)(P);
        Library.PopFront();
    }
}
template<class T>
void InformationViewer::Analyze(void (*C)(Information*,T),T K)
{
    while(Library.Size()>0)
    {
        Information* P=Library.Begin()->Data;
        (*C)(P,K);
        Library.PopFront();
    }
}
template<class T,class B>
void InformationViewer::Analyze(void (T::*C)(Information*,B),T* U,B F)
{
    while(Library.Size()>0)
    {
        Information* P=Library.Begin()->Data;
        (U->*C)(P,F);
        Library.PopFront();
    }
}
#endif // INFORMATIONVIEWER_H
