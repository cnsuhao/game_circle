#ifndef CALCULATESPACE_H
#define CALCULATESPACE_H
#include "scription/scriptionseparate.h"
#include <math>
class CalculateSpace
{
    std::map<std::string,int> ValueMap;
public:
    int CalculateDetail(FileFactorPoint B, FileFactorPoint E);
    template <class T>
    T CalculateSpecial(T,T,std::string);
    template <class T>
    T CalculateSpecial(T,T,int);
    bool CharLegal(FileFactorPoint T);
    int & CallVariable(std::string L){if(ValueMap.count(L)==0) return ValueMap[L]=0;return ValueMap[L];}
    std::string Translate(int Y){std::stringstream K;std::string C;K<<Y;K>>C;return C;}
    int Translate(std::string C){std::stringstream K;int Tem;K<<C;K>>Tem;return Tem;}
    void JumpCurve(FileFactorPoint S,FileFactorPoint& T,FileFactorPoint E);
};

bool CalculateSpace::JumpCurve(FileFactorPoint S,FileFactorPoint& T,FileFactorPoint E)
{
    int Size=0;
    while(S!=E)
    {
        if(S->Is("("))
            Size+=1;
        else if(S->Is(")"))
            Size-=1;
        if(Szie==0)
        {
            T=S;
            return true;
        }else if(Size<0)
        {
            GetError(") Can not find a (",S->Line());
            return false;
        }
    }
    if(Size>0)
    {
        GetError("( can not find a )",-0);
        return false;
    }
    return true;
}

bool CalculateSpace::CharLegal(FileFactorPoint T)
{
    if(T->IsSymple())
    {
        if(T->Is("+")||T->Is("-")||T->Is("*")||T->Is("/")||T->Is("%")||T->Is("(")||T->Is(")")||T->Is("^"))
            return true;
        else
            return false;
    }else
        return true;
}


template <class T>
T CalculateSpace::CalculateSpecial(T N1,T N2,std::string Symple)
{
    if(Symple=="+")
        return N1+N2;
    else if(Symple=="-")
        return N1-N2;
    else if(Symple=="*")
        return N1*N2;
    else if(Symple=="/")
        return N1/N2;
    else if(Symple=="%")
        return N1%N2;
    else if(Symple=="^")
        return pow(N1,N2);
}

template <class T>
T CalculateSpace::CalculateSpecial(T N1,T N2,int Mode)// 0 is unknow , 2 is number , 3 is +, 4 is -,5 is * ,6 is /,7 is %,8 is ^
{
    switch(Mode)
    {
    case 3:
        return N1+N2;
    case 4:
        return N1-N2;
    case 5:
        return N1*N2;
    case 6:
        return N1/N2;
    case 7:
        return N1%N2;
    case 8:
        return pow(N1,N2);
    }
}


int CalculateSpace::CalculateDetail(FileFactorPoint B, FileFactorPoint E)
{
    if(B!=E)
    {
        int V1=0,M12=0,V2=0,M23=0,V3=0,Mode=0;
        while(B!=E)
        {
            if(CharLegal(B))
            {
                if(Mode==0)
                {
                    if(B->IsNumber())
                        V1=Translate(*B);
                    else if(B->IsSymple())
                    {
                        if(B->Is("("))
                            Jump(B,B,E);
                        else if(B->Is(")"))
                        {
                            GetError(") can not find a (",B->Line());
                            return -9999;
                        }else{
                            GetError("Symple is in the wrong place",B->Line());
                            return -9999;
                        }
                    }else
                        V1=CallVariable(*B);
                    ++Mode;
                }else if(Mode==1)
                {
                    if()
                }
            }else{
                GetError("Character <"+B->Detail()<<"> Can not Regenize. ",B->Line());
                break;
            }
            ++B;
        }
    }
}
#endif // CALCULATESPACE_H
