#ifndef SCRIPTIONBASENEW_H
#define SCRIPTIONBASENEW_H
#include <string>
#include <list>
#include <map>
#include <sstream>
#include "error.h"
#include "poscriptionseparate.h"
#define Scr_True "SCRTTURE"
#define Scr_False "SCRFALSE"
#define Scr_Base_Opt_N "N"
#define Scr_Base_Opt_S "S"
#define Scr_Base_Opt_SR "SR"
#define Scr_Base_Opt_C "C"
#define Scr_Base_Opt_CR "CR"
#define Scr_Base_Opt_IF "IF"
#define Scr_Base_Mod_N 0
#define Scr_Base_Mod_D 1
#define Scr_Base_Mod_V 2
class SceneMes
{
    std::string Data;
    int mLine;
public:
    std::string Detail(){return Data;}
    int Line(){return mLine;}
    bool operator ==(std::string K){return Data==K;}
    SceneMes(std::string K,int C=0):Data(K),mLine(C){}
    SceneMes(){}
};

class ScriptionData
{
    std::map<std::string,int> ScriptionValue;
    int Size;

public:
    FileFactor FF;
    ScriptionData():Size(1){}
    void AddValue(std::string P);
    int& Usevalue(std::string P);
    virtual void Send(std::string K){}
    virtual std::string AskForRespon(std::string P,int Line=0){ScriptionPacket::Push("Unknow solution of information <"+P+">.",Line);}
    virtual std::string Unite(std::list<std::string>& K);
    std::string StatementAnalyze(std::list<std::string>& K){return Scr_True;}
    void Load(std::string K){Separate(K,FF);}
    FileFactorPoint Begin(){return FF.Begin();}
    FileFactorPoint End(){return FF.End();}
};

class ScriptionOperator
{
public:
    FileFactorPoint Operator;
    FileFactorPoint ScriptionBegin;
    FileFactorPoint ScriptionEnd;
    int Line(){return Operator->Line();}
    std::string Scription(){return Unite(ScriptionBegin,ScriptionEnd);}
    ScriptionOperator(const ScriptionOperator& K):ScriptionBegin(K.ScriptionBegin),Operator(K.Operator),ScriptionEnd(K.ScriptionEnd){}
    ScriptionOperator(FileFactorPoint S,FileFactorPoint E);
    bool Is(std::string K){return (*Operator)==K;}
    FileFactorPoint Begin(){return ScriptionBegin;}
    FileFactorPoint End(){return ScriptionEnd;}
    void CheckDetail(std::fstream& K,std::string Pre="   -"){K<<Pre+Operator->Detail()+":"+Unite(ScriptionBegin,ScriptionEnd)<<std::endl;}
};
typedef std::vector<ScriptionOperator>::iterator OperatorPoint;

class ScriptionComment
{
public:
    FileFactorPoint Comment;
    FileFactorPoint ScriptionBegin;
    FileFactorPoint ScriptionEnd;
    std::vector<ScriptionOperator> OperatorList;
    ScriptionComment(FileFactorPoint S,FileFactorPoint E);
    ScriptionComment(const ScriptionComment& K):ScriptionBegin(K.ScriptionBegin),Comment(K.Comment),ScriptionEnd(K.ScriptionEnd),OperatorList(K.OperatorList){}
    ScriptionComment(){}
    std::string Scription(){return Unite(ScriptionBegin,ScriptionEnd);}
    OperatorPoint Begin(){return OperatorList.begin();}
    OperatorPoint End(){return OperatorList.end();}
    int Line(){return Comment->Line();}
    std::string Detail(){return Comment->Detail();}
    void Set(FileFactorPoint C,FileFactorPoint S){CreatOperator(C,S);}
    void CreatOperator(FileFactorPoint Tem,FileFactorPoint Tem2);
    bool Is(std::string K){return (*Comment)==K;}
    void CheckDetail(std::fstream& K,std::string Pre=" *");
};
typedef std::vector<ScriptionComment>::iterator CommentPoint;

class ScriptionBlock
{

public:
    ScriptionBlock(FileFactorPoint C,FileFactorPoint S){Set(C,S);}
    ScriptionBlock(){}
    std::vector<ScriptionComment> CommentList;
    void CreatComment(FileFactorPoint Tem,FileFactorPoint Tem2);
    void Set(FileFactorPoint C,FileFactorPoint S){CreatComment(C,S);}
    CommentPoint Begin(){return CommentList.begin();}
    CommentPoint End(){return CommentList.end();}
    void CheckDetail(std::fstream& K);
};
void ScriptionBlock::CheckDetail(std::fstream& K)
{
    for(CommentPoint OP=Begin();OP!=End();++OP)
    {
        OP->CheckDetail(K);
    }
}
void ScriptionComment::CheckDetail(std::fstream& K,std::string Pre)
{
    K<<Pre+Comment->Detail()+":"+Unite(ScriptionBegin,ScriptionEnd)<<std::endl;
    for(OperatorPoint OP=Begin();OP!=End();++OP)
    {
        OP->CheckDetail(K);
    }
}

ScriptionComment::ScriptionComment(FileFactorPoint S, FileFactorPoint E)
{
    if(E-S<3)
    {
        ScriptionPacket::Push("Comment is not comlete",S->Line());
    }else{
        Comment=S+1;
        ScriptionBegin=S+2;
        FileFactorPoint Tem;
        if(*(S+2)=="{")
        {
            bool Using=false;
            Tem=S+2;
            while(Tem!=E)
            {
                if(Tem->Is("}"))
                {
                    Using=true;
                    break;
                }
                ++Tem;
            }
            if(Using)
            {
                ++Tem;
                ScriptionEnd=Tem;
                CreatOperator(Tem,E);
            }else{
                ScriptionPacket::Push("Symple {...} is not Complete.",Tem->Line());
            }
        }else{
            Tem=S+3;
            ScriptionEnd=S+3;
            if(Tem!=E)
            {
                CreatOperator(Tem,E);
            }
        }
    }
}

ScriptionOperator::ScriptionOperator(FileFactorPoint S, FileFactorPoint E)
{
    if(E-S<2)
    {
        ScriptionPacket::Push("Operator is not complete.",S->Line());
    }else{
        if(*S!="-")
        {
            ScriptionPacket::Push("Operator meet bad head.",S->Line());
        }else{
            Operator=S+1;
            ScriptionBegin=S+2;
            ScriptionEnd=E;
        }
    }
}

void ScriptionComment::CreatOperator(FileFactorPoint Tem,FileFactorPoint Tem2)
{
    OperatorList.clear();
    FileFactorPoint S;
    FileFactorPoint E;
    FileFactorPoint T=Tem;
    bool Find=false;
    bool Continue=false;
    if(Tem!=Tem2)
    {
        while(T!=Tem2)
        {
            if(*T=="-")
            {
                if(!Continue)
                {
                    if(!Find)
                    {
                        S=T;
                        Find=true;
                    }else{
                        E=T;
                        OperatorList.push_back(ScriptionOperator(S,E));
                        Find=false;
                        continue;
                    }
                }
            }else if(*T=="{")
            {
                Continue=true;
            }else if(*T=="}")
            {
                Continue=false;
            }
            ++T;
        }
        OperatorList.push_back(ScriptionOperator(S,Tem2));
    }
}

void ScriptionBlock::CreatComment(FileFactorPoint Tem,FileFactorPoint Tem2)
{
    CommentList.clear();
    //error<<"CreatComment:<"<<Unite(Tem,Tem2)<<">"<<endl;
    if(Tem!=Tem2)
    {
        if(*Tem!="*")
        {
            ScriptionPacket::Push("Comment meet bad head.",Tem->Line());
        }else{
            FileFactorPoint S=Tem;
            ++Tem;
            if(Tem==Tem2)
            {
                ScriptionPacket::Push("Comment is not complete2",Tem->Line());
            }else{
                while(Tem!=Tem2)
                {
                    if(*Tem=="*")
                    {
                        CommentList.push_back(ScriptionComment(S,Tem));
                        S=Tem;
                    }
                    ++Tem;
                }
                CommentList.push_back(ScriptionComment(S,Tem2));
            }
        }
    }
}

std::string ScriptionData::Unite(std::list<std::string> &K)
{
    std::string Tem;
    std::list<std::string>::iterator Po=K.begin();
    for(;Po!=K.end();++Po)
    {
        Tem+=*Po;
    }
    return Tem;
}


void ScriptionData::AddValue(std::string P)
{
    ScriptionValue[P]=0;
}

int& ScriptionData::Usevalue(std::string P)
{
    if(ScriptionValue.count(P)==0)
        ScriptionValue[P]=0;
    return ScriptionValue[P];
}
#endif // SCRIPTIONBASENEW_H
