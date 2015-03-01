#ifndef ROUTER_H
#define ROUTER_H
#include "../p.o/handle.h"
#include "../p.o/scriptionbase.h"
class Router
{
public:
    CommentPoint Start;
    CommentPoint End;
    CommentPoint NextCP;
    CommentPoint Next(){return NextCP;}
    bool IsEnd(CommentPoint Tc){return Tc==End;}
    void Set(CommentPoint K,CommentPoint C){Start=K;End=C;NextCP=C;}
    void Set(CommentPoint K, CommentPoint C,CommentPoint D){Start=K;End=C;NextCP=D;}
    bool Is(CommentPoint P){return P==Start;}
    Router(){}
    Router(CommentPoint K,CommentPoint C){Set(K,C);}
    Router(CommentPoint K,CommentPoint C,CommentPoint D){Set(K,C,D);}
    Router(Router &C):Start(C.Start),End(C.End),NextCP(C.NextCP){}
    Router(const Router &C):Start(C.Start),End(C.End),NextCP(C.NextCP){}
    void Check(std::fstream &);
};
void Router::Check(std::fstream &P)
{
    P<<"Router :<"<<(Start->Detail())+"  "<<Start->Scription()<<"> in Line <"<<Start->Line()<<">."<<std::endl;
    P<<"    End At :<"<<(End->Comment->Data)<<"  "<<End->Scription()<<"> in Line <"<<End->Line()<<">."<<std::endl;
    P<<"    Jump To :<"<<(NextCP->Comment->Data)<<"  "<<NextCP->Scription()<<"> in Line <"<<NextCP->Line()<<">."<<std::endl;
}

class IfRouter:public HandleSeed
{
    CommentPoint If;
    CommentPoint Else;
    CommentPoint End;
public:
    IfRouter(CommentPoint I,CommentPoint El,CommentPoint En){}
    IfRouter(CommentPoint I,CommentPoint En){}
    IfRouter(){}
    void Set(CommentPoint I,CommentPoint El,CommentPoint En){If=I;Else=El;End=En;}
    void Set(CommentPoint I,CommentPoint En){If=I;Else=En;End=En;}
};
class OptionRouter:public HandleSeed
{
    CommentPoint OpTitle;
    CommentPoint OpTitleEnd;
public:
    std::list<CommentPoint> Option;
};

#endif // ROUTER_H
