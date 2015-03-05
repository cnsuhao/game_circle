#ifndef DIY_BASECLASS_H
#define DIY_BASECLASS_H
#define XYZ XYZ<float>
#include <math.h>
#include <fstream>
class XYF
{
    public:
        float X;
        float Y;
        float Distance(const XYF& Tem){return sqrt((X-Tem.X)*(X-Tem.X)+(Y-Tem.Y)*(Y-Tem.Y));}
        float Distance(const XYF& T1,const XYF& T2);
        float Long(void){return sqrt(X*X+Y*Y);}
        float Long2(void){return X*X+Y*Y;}
        void Set(float a,float b){X=a;Y=b;}
        XYF Uint(const float& Multiply);
        XYF(float x=0.0 , float y=0.0 ):X(x),Y(y){}
        void operator+=(const XYF& B)  {X+=B.X;Y+=B.Y;}
        void operator-=(const XYF& B)  {X-=B.X;Y-=B.Y;}
};
class XYZF
{
    public:
        float X;
        float Y;
        float Z;
        void Turn(float x,float y,float z);//弧度制，以该轴负方向为正方向，逆时针旋转
        void Set(float x,float y,float z)   {X=x;Y=y;Z=z;}
        float Distance(const XYZF& Tem) const   {return sqrt((X-Tem.X)*(X-Tem.X)+(Y-Tem.Y)*(Y-Tem.Y)+(Z-Tem.Z)*(Z-Tem.Z));}
        float Distance(const XYZF& T1,const XYZF& T2) const;
        float Long(void){return sqrt(X*X+Y*Y+Z*Z);}
        float Long2(void){return X*X+Y*Y+Z*Z;}
        XYZF Uint(float Multiple=1.0)     {float Line=sqrt(X*X+Y*Y+Z*Z);if(Line!=0){XYZF Tem;Tem.X=X/Line*Multiple;Tem.Y=Y/Line*Multiple;Tem.Z=Z/Line*Multiple;return Tem;}else{XYZF Tem(0.0,0.0,0.0);return Tem;}}
        XYZF(const XYZF& T){X=T.X;Y=T.Y;Z=T.Z;}
        XYZF ToCoordinate(const XYZF& x,const XYZF& y,const XYZF& z)const  {XYZF Tem2((*this)*x,(*this)*y,(*this)*z);return Tem2;}//将原始坐标系中的点或向量转换成目标坐标系中的坐标
        XYZF FromCoordinate(const XYZF& x,const XYZF& y,const XYZF& z)const  {XYZF Tem(x*X+y*Y+z*Z);return Tem;}//将目标坐标系中的点或向量转换成原始坐标系中的坐标
        XYZF(float x=0.0,float y=0.0,float z=0.0):X(x),Y(y),Z(z){}
        float operator* (const XYZF& Temp)const {return X*Temp.X+Y*Temp.Y+Z*Temp.Z;}
        XYZF operator* (const float t)const     {XYZF tem(X*t,Y*t,Z*t);return tem;}
        XYZF operator+ (const XYZF& b)const     {XYZF tem(X+b.X , Y+b.Y , Z+b.Z);return tem;}
        XYZF operator- (const XYZF& b)const     {XYZF tem(X-b.X , Y-b.Y , Z-b.Z);return tem;}
        XYZF operator& (const XYZF& b)const     {XYZF tem(Y*b.Z-Z*b.Y,Z*b.X-X*b.Z,X*b.Y-Y*b.X);return tem;}
        void operator= (const XYZF& B)  {Set(B.X,B.Y,B.Z);}
        void operator+=(const XYZF& B)  {X+=B.X;Y+=B.Y;Z+=B.Z;}
        void operator-=(const XYZF& B)  {X-=B.X;Y-=B.Y;Z-=B.Z;}

};
class Coordinate
{
    public:
        XYZF Left;
        XYZF Location;
        XYZF Up;
        XYZF Front;
        XYZF ToCoordinate(const XYZF&) const ;
        XYZF VectorToCoordinate(const XYZF&) const ;
        Coordinate ToCoordinate(const Coordinate*) const;
        XYZF FromCoordinate(const XYZF&) const ;
        XYZF VectorFromCoordinate(const XYZF&) const ;
        Coordinate FromCoordinate(const Coordinate*) const;
        inline void Reflash(void);
        void Set(Coordinate&);
        void Set(Coordinate*);

        Coordinate():Left(1.0,0.0,0.0),Up(0.0,1.0,0.0),Front(0.0,0.0,1.0),Location(0.0,0.0,0.0){}
        Coordinate(const Coordinate& C)
        {
            Left=C.Left;
            Up=C.Up;
            Front=C.Front;
            Location=C.Location;
        }
        //operator Coordinate(){return *this;}
};
float XYF::Distance(const XYF& T1,const XYF& T2)
{
    XYF P(T2.X-T1.X,T2.Y-T1.Y);
    float A;
    float B;
    char S=0;
    if(P.X==0.0){S+=1;}
    if(P.Y==0.0){S+=2;}
    switch(S)
    {
        case 0:B=1.0/(T1.Y-P.Y/P.X*T1.X);A=-B*P.Y/P.X;break;
        case 1:B=0.0;A=-1.0/T1.X;break;
        case 2:A=0.0;B=-1.0/T1.Y;break;
        case 3:return Distance(T1);
    }
    return fabs(A*X+B*Y+1.0)/sqrt(pow(A,2.0)+pow(B,2.0));
}

XYF XYF::Uint(const float& Multiply=1.0)
{
    float Line=Long();
    XYF Tem;
    if(Line!=0)
    {
        Tem.X=X/Line*Multiply;
        Tem.Y=Y/Line*Multiply;
        //return Tem;
    }
    return Tem;
}
void XYZF::Turn(float x,float y,float z)//弧度制，以该轴负方向为正方向，逆时针旋转
{
    XYZF Tem(X,Y,Z);
    XYZF RT=Tem;
    Tem.Set(RT.X,RT.Y*cos(x)-RT.Z*sin(x),RT.Z*cos(x)+RT.Y*sin(x));
    RT=Tem;
    Tem.Set(RT.X*cos(y)+RT.Z*sin(y),RT.Y,RT.Z*cos(y)-RT.X*sin(y));
    RT=Tem;
    Tem.Set(RT.X*cos(z)-RT.Y*sin(z),RT.Y*cos(z)+RT.X*sin(z),RT.Z);
    *this=Tem;
}
std::ostream& operator <<(std::ostream& C,XYZF& T){C<<"<"<<T.X<<","<<T.Y<<","<<T.Z<<">";return C;}
std::ostream& operator<<(std::ostream& C,Coordinate& P){C<<P.Location<<" , "<<P.Up<<" , "<< P.Left <<" , "<<P.Front;return C;}
float XYZF::Distance(const XYZF& T1,const XYZF& T2) const
{
    XYZF L1=T2-T1;
    XYZF L2=*this-T1;
    float P=L2*L1.Uint();
    return (L1*P-L2).Long();
}

inline void Coordinate::Reflash(void)//the Up is the standard;
{
    Left=(Up&Front).Uint();
    Front=(Left&Up).Uint();
}
XYZF Coordinate::ToCoordinate(const XYZF& Tem) const//point to Coordinate
{
    XYZF Ter=Tem-Location;
    Ter=Ter.ToCoordinate(Left,Up,Front);
    return Ter;
}
XYZF Coordinate::VectorToCoordinate(const XYZF& Tem) const//vector to Coordinate
{
    XYZF Ter;
    Ter=Ter.ToCoordinate(Left,Up,Front);
    return Ter;
}
XYZF operator* (const float t,const XYZF& a)    {XYZF tem(a.X*t,a.Y*t,a.Z*t);return tem;}
float operator* (const XYF& Tem,const XYF& Temp)    {return Tem.X*Temp.X+Tem.Y*Temp.Y;}
XYF operator* (const XYF& a,const float t)      {XYF tem(a.X*t,a.Y*t);return tem;}
XYF operator* (const float t,const XYF& a)      {XYF tem(a.X*t,a.Y*t);return tem;}
XYF operator+ (const XYF& a,const XYF& b)       {XYF tem(a.X+b.X , a.Y+b.Y);return tem;}
XYF operator- (const XYF& a,const XYF& b)       {XYF tem(a.X-b.X , a.Y-b.Y);return tem;}
/*Coordinate Coordinate::ToCoordinate(const Coordinate* Temc) const
{
    Coordinate Tem;
    Tem.Location=Location-Temc->Location;
    Tem.Up=Temc->Up.ToCoordinate(Left,Up,Front);
    Tem.Front=Temc->Front.ToCoordinate(Left,Up,Front);
    Tem.Reflash();
    return Tem;
}*/
void Coordinate::Set(Coordinate* C)
{
    Up=C->Up;
    Front=C->Front;
    Left=C->Left;
    Location=C->Location;
}
void Coordinate::Set(Coordinate& C)
{
    Up=C.Up;
    Front=C.Front;
    Left=C.Left;
    Location=C.Location;
}
XYZF Coordinate::FromCoordinate(const XYZF& Tem) const
{
    XYZF Ter=Tem;
    Ter=Ter.FromCoordinate(Left,Up,Front)+Location;
    return Ter;
}
XYZF Coordinate::VectorFromCoordinate(const XYZF& Tem) const
{
    XYZF Ter=Tem;
    Ter=Ter.FromCoordinate(Left,Up,Front);
    return Ter;
}
Coordinate Coordinate::FromCoordinate(const Coordinate* Temc) const
{
    Coordinate Tem;
    Tem.Location=Temc->Location-Location;
    Tem.Up=Temc->Up.FromCoordinate(Left,Up,Front);
    Tem.Front=Temc->Front.FromCoordinate(Left,Up,Front);
    Tem.Reflash();
    return Tem;
}
#endif
