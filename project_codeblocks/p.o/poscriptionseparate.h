#ifndef POSCRIPTION_H
#define POSCRIPTION_H
#include <fstream>
#include <string>
#include <map>
#define SPE_NUL 0
#define SPE_SYM 1
#define SPE_NUM 2
#define SPE_CHA 3
#define SPE_SPE 4
#define SPE_CL 5
#define SPE_CON 6
#define SPE_BBL 7
#define SPE_BBR 8
#define SPE_SBR 9
#define SPE_SBL 10
#include <vector>
#include "po.h"
namespace ScriptionPacket
{
class ScriptionError
{
public:
    std::string Data;
    int Line;
    ScriptionError(std::string K,int Y=-1):Data(K),Line(Y){}
    ScriptionError(const ScriptionError& SE):Data(SE.Data),Line(SE.Line){}
};
class ScriptionErrorPacket
{
public:
    std::list<ScriptionError> AllError;
    void Push(std::string C,int K=-1){ScriptionError Tem(C,K);AllError.push_back(Tem);}
}SEP;
void Push(std::string C,int K=-1){SEP.Push(C,K);}
bool Ready(){return SEP.AllError.empty();}
void Display(std::fstream &L)
{
    int U=1;
    for(std::list<ScriptionError>::iterator Po=SEP.AllError.begin();Po!=SEP.AllError.end();++Po,++U)
    {
        L<<"<"<<U<<"> Error:"<<std::endl;
        L<<"   "<<Po->Data<<std::endl;
        if(Po->Line>0)
        L<<"         -------In Line <"<<Po->Line<<">"<<std::endl;
    }
}
}




class ScriptionFactor
{
public:
    int mLine;
    std::string Data;
    int Mode;
    int Line(){return mLine;}
    int Size(){return Data.size();}
    std::string Detail(){return Data;}
    const char* c_str(){return Data.c_str();}
    operator std::string(){return Data;}
    ScriptionFactor operator=(ScriptionFactor& Tem){mLine=Tem.mLine;Data=Tem.Data;return *this;}
    bool operator==(std::string T){return Data==T;}
    bool operator!=(std::string K){return Data!=K;}
    bool Is(std::string K){return K==Data;}
    bool IsNumber(){return Mode==SPE_NUM;}
    bool IsSymple(){return Mode==SPE_SYM;}
    ScriptionFactor operator=(std::string K){Data=K;return *this;}
    ScriptionFactor(std::string D,int L=0,int M=0):Data(D),mLine(L),Mode(M){}
    ScriptionFactor(ScriptionFactor& Tem):mLine(Tem.mLine),Data(Tem.Data),Mode(Tem.Mode){}
    ScriptionFactor(const ScriptionFactor& Tem):mLine(Tem.mLine),Data(Tem.Data),Mode(Tem.Mode){}
};
typedef std::vector<ScriptionFactor>::iterator FileFactorPoint;

class FileFactor
{
    std::string FileName;
    FileFactorPoint Point;
    FileFactor operator=(FileFactor&){}
public:
    std::vector<ScriptionFactor> FileDetail;
    std::string Adress(){return FileName;}
    void SetAdress(std::string K){FileName=K;}
    FileFactor(){}
    FileFactor(FileFactor& Tem):FileName(Tem.FileName),FileDetail(Tem.FileDetail){}
    bool IsEnd(){return Point==FileDetail.end();}
    void Clear(){FileDetail.clear();}
    void Push(ScriptionFactor& Tem){FileDetail.push_back(Tem);}
    FileFactorPoint Begin(){return FileDetail.begin();}
    FileFactorPoint End(){return FileDetail.end();}
    void Push(std::string D,int L,int M){ScriptionFactor Tem(D,L,M);Push(Tem);}
};

class ScriptionChar
{
    char TemC;
public:
    int Style();
    char operator= (char K){TemC=K;return K;}
    operator char(){return TemC;}
    ScriptionChar(char Tem=0):TemC(Tem){}
    bool IsAvalible(){int M=Style();if(M!=SPE_NUL&&M!=SPE_SPE&&M!=SPE_CL)return true;return false;}
    bool IsSpace(){if(Style()==SPE_SPE)return true;return false;}
    bool IsChangeLine(){if(Style()==SPE_CL)return true;return false;}
    bool IsUnUse(){if(Style()==SPE_NUL)return true;return false;}
    bool operator==(char K){if(TemC==K)return true;return false;}
};

void Separate(std::string FileAdress,FileFactor& Resoult)
{
    Resoult.Clear();
    std::ifstream File(FileAdress.c_str());
    int Line=1;
    if(File)
    {
        std::string TemS;
        int Mode=SPE_NUL;
        ScriptionChar TemC;
        bool UsingLastChar=false;
        TemC=File.get();
        while(!File.eof())
        {
            if(Mode==SPE_CON)
            {
                if(TemC!=']')
                {
                    if(TemC.IsChangeLine())
                        Line+=1;
                    TemS+=TemC;
                }else{
                    Mode=SPE_NUL;
                    Resoult.Push(TemS,Line,Mode);
                    TemS.clear();
                }
            }else if(Mode==SPE_NUL)
            {
                if(TemC.IsChangeLine())
                    Line+=1;
                else if(!TemC.IsSpace())
                {
                    if(TemC=='[')
                    {
                        Mode=SPE_CON;
                    }else{
                        Mode=TemC.Style();
                        TemS+=TemC;
                    }
                }
            }else{
                if(!TemC.IsAvalible())
                {
                    Resoult.Push(TemS,Line,Mode);
                    Mode=SPE_NUL;
                    TemS.clear();
                }else{
                    if(TemC.Style()!=Mode)
                    {
                        if(Mode==SPE_NUM&&TemC=='.')
                        {
                            TemS+=TemC;
                        }else if(TemC.Style()==SPE_NUM&&Mode==SPE_CHA)
                        {
                            TemS+=TemC;
                        }else{
                            UsingLastChar=true;
                            Resoult.Push(TemS,Line,Mode);
                            Mode=SPE_NUL;
                            TemS.clear();
                        }
                    }else{
                        TemS+=TemC;
                    }
                }
            }
            if(UsingLastChar)
            {
                UsingLastChar=false;
            }else
                TemC=File.get();
        }
        if(Mode!=SPE_NUL)
        {
            Resoult.Push(TemS,Line,Mode);
        }
    }else{
        ScriptionPacket::Push("Can not open  file <"+FileAdress+">, please check");
    }
}
std::string Unite(FileFactorPoint S,FileFactorPoint E)
{
    std::string Tem;
    for(;S!=E;)
    {
        Tem+=*S;
        ++S;
        if(S!=E)
            Tem+="_";
    }
    return Tem;
}

int ScriptionChar::Style()
{
    if(TemC==0)
        return SPE_NUL;
    else if(TemC==' '||TemC=='\t'||TemC=='\r')
        return SPE_SPE;
    else if(TemC=='\n')
        return SPE_CL;
    else if((TemC>='a'&&TemC<='z')||(TemC>='A'&&TemC<='Z'))
        return SPE_CHA;
    else if(TemC>='0'&&TemC<='9')
        return SPE_NUM;
    else if(TemC=='{')
        return SPE_BBL;
    else if(TemC=='}')
        return SPE_BBR;
    else if(TemC=='(')
        return SPE_SBL;
    else if(TemC==')')
        return SPE_SBR;
    else return SPE_SYM;
}
#endif // POSCRIPTION_H
