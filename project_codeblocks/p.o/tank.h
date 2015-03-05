#ifndef TANK_H
#define TANK_H
#include "tank/water.h"
template<class TC>
class Tank
{

public:
    unsigned long Number;
    Handle<Water<TC> > Start;
    Handle<Water<TC> > EndPoint;
    class Ladle
    {
    public:
        Handle<Water<TC> > Point;
        TC* operator ->(){return Point->Data;}
        TC& operator*(){return *(Point->Data);}
        Ladle operator ++(){Point->Lock();Point=Point->Next();Point->Last()->UnLock();return *this;}
        Ladle operator --(){Point->Lock();Point=Point->Last();Point->Next()->UnLock();return *this;}
        Ladle operator =(Ladle K){Point=K.Point;return *this;}
        bool operator== (Ladle K){return Point==K.Point;}
        bool operator!= (Ladle K){return Point!=K.Point;}
        Ladle(){}
        Ladle(Handle<Water<TC> > K){Point=K;}
        Ladle(const Ladle & O):Point(O.Point){}
        Ladle(Ladle & O){Point=O.Point;}
        operator bool(){return Point;}
    };
    unsigned long Size(){return Number;}
    bool Empty(){return !Number;}
    Tank():Number(0){EndPoint=new Water<TC>();Start=new Water<TC>();EndPoint->SetLast(Start);Start->SetNext(EndPoint);}
    Ladle Begin(){Start->Lock();Ladle K(Start->Next());Start->UnLock();return K;}
    Ladle End(){Ladle K(EndPoint);return K;}
    bool IsEnd(Ladle& P){return EndPoint==P.Point;}
    void PushBack(const TC&);
    void PopFront();
    void Erase(Ladle& K);
    void Clear();
};
template<class TC>
void Tank<TC>::Clear()
{
    while(!Empty())
        PopFront();
}



template<class TC>
void Tank<TC>::PopFront()
{
    if(!Empty())
    {
        Start->Lock();
        Handle<Water<TC> > N1=Start->Next();
        N1->Lock();
        Handle<Water<TC> > N2=N1->Next();
        N2->Lock();

        Start->SetNext(N2);
        N2->SetLast(Start);

        N2->UnLock();
        N1->UnLock();
        Start->UnLock();

        Number-=1;
    }
}

/*template<class TC>
void Tank<TC>::PushFront(const TC & P)
{
    Handle<Water<TC> > K=new Water<TC>(P);
    Start->SetLast(K);
    K->SetNext(Start);
    Start=K;
}*/

template <class TC>
void Tank<TC>::PushBack(const TC &P)
{
    Handle<Water<TC> > K=new Water<TC>(P);
    EndPoint->Lock();
    Handle<Water<TC> > L=EndPoint->Last();
    EndPoint->UnLock();

    L->Lock();
    EndPoint->Lock();

    L->SetNext(K);
    K->SetLast(L);

    K->SetNext(EndPoint);
    EndPoint->SetLast(K);

    L->UnLock();
    EndPoint->UnLock();
    Number+=1;
}
template <class TC>
void Tank<TC>::Erase(Ladle& P)
{
    if(!Empty())
    {
        if(P.Point!=Start&&P.Point!=EndPoint)
        {
            P.Point->Lock();
            Handle<Water<TC> > L=P.Point->Last();
            Handle<Water<TC> > N=P.Point->Next();
            P.Point->UnLock();

            L->Lock();
            P.Point->Lock();
            N->Lock();


            L->SetNext(N);
            N->SetLast(L);


            N->UnLock();
            P.Point->UnLock();
            P.Point=L;
            L->UnLock();
            Number-=1;
        }
    }
}

#endif // TANK_H
