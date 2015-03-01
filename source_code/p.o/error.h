#ifndef DIY_ERROR_H
#define DIY_ERROR_H
#include <string>
class PreRunError
{
public:
    std::string Data;
    PreRunError(std::string S):Data(S){}
    void operator =(std::string S){Data=S;}
    void operator =(char* C){std::string Tem(C);Data=Tem;}
    std::string operator+(std::string S){return Data+S;}
};

class RunInitError
{
public:
    std::string Data;
    RunInitError(std::string S):Data(S){}
    void operator =(std::string S){Data=S;}
    void operator =(char* C){std::string Tem(C);Data=Tem;}
    std::string operator+(std::string S){return Data+S;}
};

class RunError
{
public:
    std::string Data;
    RunError(std::string S):Data(S){}
    void operator =(std::string S){Data=S;}
    void operator =(char* C){std::string Tem(C);Data=Tem;}
    std::string operator+(std::string S){return Data+S;}
};

class ScriptionError
{
public:
    std::string File;
    int mLine;
    std::string Data;
    int Line(){return mLine;}
    std::string Detail(){return Data;}
    std::string Adress(){return File;}
    void SetAdress(std::string K){File=K;}
    ScriptionError(std::string S,int L=0):Data(S),mLine(L){}
    ScriptionError(const ScriptionError& Tem):Data(Tem.Data),mLine(Tem.mLine),File(Tem.File){}
    void operator =(std::string S){Data=S;}
    bool operator==(std::string C){return Data==C;}
    void operator =(char* C){std::string Tem(C);Data=Tem;}
    operator std::string(){return Data;}
    std::string operator+(std::string S){return Data+S;}
};
#endif // ERROR_H
