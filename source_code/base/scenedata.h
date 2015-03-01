#ifndef SCENEDATA_H
#define SCENEDATA_H
#include "../p.o/popicture.h"
#include "../p.o/handle.h"
#include "../p.o/scriptionbase.h"
#include "../p.o/dialog.h"
#include "router.h"
#include "../p.o/po.h"
class SceneData
{
public:
    std::map<std::string,int> ValueMap;
    std::map<std::string,std::string> Resource;
    std::map<std::string,POPicture > AllPicture;
    bool NextScene;
    std::string Target;
    void LoadResource(std::string,POMain*);
    void AddResource(std::list<std::string>&,std::list<std::string>&,std::list<std::string>&,std::string,std::string);
    void CheckDetail(fstream&);
    std::string Calculate(FileFactorPoint B,FileFactorPoint E);
    void CallNextScene(std::string K){NextScene=true;Target=K;}
    int CalculateDetail(FileFactorPoint B, FileFactorPoint E);
    POPicture SearchResource(std::string P,FileFactorPoint B,FileFactorPoint E,std::string S="");
    POPicture SearchResource(std::string P){if(AllPicture.count(P)==0){ScriptionPacket::Push("Can Not Find The Resource "+P+" ",-1);POPicture K;return K;}return AllPicture[P];}
    std::string Translate(int Y){std::stringstream K;std::string C;K<<Y;K>>C;return C;}
    int Ask(std::string I){if(ValueMap.count(I)==0)ValueMap[I]=0;return ValueMap[I];}
    int Number(std::string K){std::stringstream Kp;Kp<<K;int Tem;Kp>>Tem;return Tem;}
    int Ask(FileFactorPoint K){if(K->IsNumber())return Number(*K);else return Ask(*K);}
    void Init(POMain*);
    bool NeedJump(){return NextScene;}
    std::string TargetScene(){return Target;}
    virtual void SentMessage(std::string K){}
    virtual std::string RespondMessage(std::string K){}
    std::string Result(int Tem){if(Tem)return Scr_True;else return Scr_False;}
    std::string Result(bool K){if(K)return Scr_True;else return Scr_False;}
    std::list<ScriptionError> AllError;
    void PushError(std::string K,int P){ScriptionError Tem(K,P);AllError.push_back(Tem);}
    bool Error(){return !AllError.empty();}
    void OutPutError(std::fstream &P);
};
int SceneData::CalculateDetail(FileFactorPoint B, FileFactorPoint E)
{
    //error<<"CalculateDetail : "<<Unite(B,E)<<endl;
    int V1=0;
    int V2=0;
    int Mode=0;// 0 is unknow , 2 is number , 3 is +, 4 is -,5 is * ,6 is /,7 is %
    bool Add=true;
    while(B!=E)
    {
        if(Mode==2)
        {
            if(*B=="+")Mode=3;
            else if(*B=="-")Mode=4;
            else if(*B=="*")Mode=5;
            else if(*B=="/")Mode=6;
            else if(*B=="%")Mode=7;
            else{
                ScriptionPacket::Push("Wrong math Scription <"+B->Detail()+">.",B->Line());
                return -99999999;
            }
        }else if(Mode>=3&&Mode<=7||Mode==0)
        {
            int Value=0;
            if(*B=="+"||*B=="-"||*B=="*"||*B=="/"||*B=="%")
            {
                ScriptionPacket::Push("Wrong math Scription <"+B->Detail()+">.",B->Line());
                return -99999999;
            }else if(*B=="(")
            {
                int K=0;
                FileFactorPoint B2=B;
                FileFactorPoint E2=E;
                while(B2!=E)
                {
                    if(*B2=="(")
                        K+=1;
                    else if(*B2==")")
                        K-=1;
                    if(K==0)
                    {
                        E2=B2;
                        break;
                    }
                }
                if(K!=0)
                {
                    ScriptionPacket::Push("The Symple (...) Is Not Complate.",B->Line());
                    return -9999999;
                }
                Value=CalculateDetail(B,E2);
            }else if(*B=="Rand")
            {
                Value=rand();
            }else{
                Value=Ask(B);
            }
            if(Mode==3||Mode==4)
            {
                if(Add)
                    V1+=V2;
                else
                    V1-=V2;
                if(Mode==3)
                    Add=true;
                else if(Mode==4)
                    Add=false;
                V2=Value;
            }else{
                if(Mode==5)
                    V2*=Value;
                else if(Mode==6)
                    V2/=Value;
                else if(Mode==7)
                    V2=V2%Value;
                else if(Mode==0)
                    V1=Value;
            }
            Mode=2;
        }
        ++B;
    }
    if(Mode!=0&&Mode!=2)
    {
        ScriptionPacket::Push("Wrong Math Scription",B->Line());
        return -99999;
    }else{
        if(Add)
            V1+=V2;
        else
            V1-=V2;
    }
    return V1;
}

std::string SceneData::Calculate(FileFactorPoint B, FileFactorPoint E)
{
    //error<<"Using Calculate:"<<Unite(B,E)<<endl;
    if(E-B>0)
    {
        while(E!=B)
        {
            if(E-B==1)
            {
                //error<<"SingleStatement:"<<Unite(B,E)<<endl;
                int Tem=Ask(B);
                return Translate(Tem);
            }else if(E-B>2)
            {
                std::string K=*(B+1);
                //error<<"MultiStatement:"<<Unite(B,E)<<endl;
                //error<<"Symple:"<<K<<endl;
                if(K=="=="||K=="<="||K==">="||K=="<"||K==">")
                {
                    int V1=Ask(B);
                    int V2=Ask(B+2);
                    if(K=="==") return Result(V1==V2);
                    if(K=="<=") return Result(V1<=V2);
                    if(K==">=") return Result(V1>=V2);
                    if(K=="<") return Result(V1<V2);
                    if(K==">") return Result(V1>V2);
                }else if(K=="=")
                {
                    if(B->IsNumber())
                    {
                        ScriptionPacket::Push("Statement <"+Unite(B,E)+"is wrong.",B->Line());
                        return std::string("WRONG");
                    }else{
                        Ask(*B);
                        FileFactorPoint Kp=B+2;
                        FileFactorPoint P=Kp;
                        while(Kp!=E)
                        {
                            if(*Kp==";")
                                break;
                            ++Kp;
                        }
                        ValueMap[*B]=CalculateDetail(P,Kp);
                        B=Kp;
                        if(Kp==E)
                            break;
                    }
                }
            }else{
                ScriptionPacket::Push("Statement <"+Unite(B,E)+"is wrong.",B->Line());
                return std::string("WRONG");
            }
            ++B;
        }
    }
    return std::string("NULL");
}

POPicture SceneData::SearchResource(std::string P,FileFactorPoint B,FileFactorPoint E, std::string S)
{
    POPicture Tem;
    if(B!=E)
    {
        if(*B=="{")
        {
            if(*(B+1)=="@")
            {
                std::string K;
                for(B+=2;B!=E-1;++B)
                    K+=*B;
                K=K+P+S;
                if(AllPicture.count(K)==0)
                    ScriptionPacket::Push("Resource is :<"+P+"> is not Find!");
                Tem=AllPicture[K];
            }
        }
    }
    return Tem;
}
void SceneData::AddResource(std::list<std::string> &Pre, std::list<std::string> &Sur,std::list<std::string> &File, std::string Target,std::string AllFile)
{
    std::string N;
    std::string F;
    for(std::list<std::string>::iterator PP=Pre.begin();PP!=Pre.end();++PP)
    {
        N+=*PP;
    }
    for(std::list<std::string>::iterator PP=Sur.begin();PP!=Sur.end();++PP)
    {
        N+=*PP;
    }
    F=AllFile;
    for(std::list<std::string>::iterator PP=File.begin();PP!=File.end();++PP)
    {
        F+=*PP;
    }
    F+=Target;
    if(Resource.count(N)==0)
        Resource[N]=F;
    else{
        ScriptionPacket::Push("The Same Resource Define:"+N);
    }
}

void SceneData::LoadResource(std::string K,POMain* L)
{
    ScriptionData SD;
    bool Need=false;
    Resource.clear();
    std::string ALLFile;
    std::string Target;
    std::string Name;
    std::list<std::string> File;
    std::list<std::string> Pre;
    std::list<std::string> Sur;
    SD.Load(K);
    FileFactorPoint Po=SD.Begin();
    if(Po!=SD.End())
    {
        while(Po!=SD.End())
        {
            if(*Po=="#")
            {
                if(SD.End()-Po<2)
                {
                    ScriptionPacket::Push("Comment <"+Unite(Po,SD.End())+"> Is Complete.",Po->Line());
                }else{
                    if(Need)
                    {
                        AddResource(Pre,Sur,File,Target,ALLFile);
                        Need=false;
                    }
                    Pre.clear();
                    Sur.clear();
                    File.clear();
                    Pre.push_back(*(Po+1));
                    Po+=2;
                }
            }else if(*Po=="*")
            {
                if(SD.End()-Po<3)
                {
                    ScriptionPacket::Push("Comment <"+Unite(Po,SD.End())+"> Is Complete.",Po->Line());
                }else{
                    std::string T=*(Po+1);
                    if(Need)
                    {
                        AddResource(Pre,Sur,File,Target,ALLFile);
                        Pre.pop_back();
                        Sur.clear();
                        Need=false;
                    }
                    if(T=="FA")
                        ALLFile=*(Po+2);
                    else if(T=="AFA")
                        File.push_back(*(Po+2));
                    else if(T=="CFA")
                        File.clear();
                    else if(T=="PFA")
                    {
                        if(!File.empty())
                            File.pop_back();
                    }
                    else if(T=="P")
                    {
                        Pre.push_back("Pic");
                        Target=*(Po+2);
                        Need=true;
                    }else if(T=="SP")
                    {
                        Pre.push_back("SmaPic");
                        Target=*(Po+2);
                        Need=true;
                    }else if(T=="B")
                    {
                        Pre.push_back("Black");
                        Target=*(Po+2);
                        Need=true;
                    }
                    Po+=3;
                }
            }else if(*Po=="-")
            {
                if(SD.End()-Po<2)
                {
                    ScriptionPacket::Push("Operator <"+Unite(Po,SD.End())+"> Is Not Complete.",Po->Line());
                }else{
                    Sur.push_back(*(Po+1));
                    Po+=2;
                }
            }else{
                ScriptionPacket::Push("Unknow Operator!",Po->Line());
            }
        }
        if(Need)
        {
            AddResource(Pre,Sur,File,Target,ALLFile);
        }
    }
    Init(L);
}
void SceneData::Init(POMain* L)
{
    AllPicture.clear();
    for(std::map<std::string,std::string>::iterator Po=Resource.begin();Po!=Resource.end();++Po)
    {
        POPicture K=L->CreatPicture(Po->second);
        AllPicture[Po->first]=K;
    }
}

void SceneData::CheckDetail(fstream & P)
{
    for(std::map<std::string,std::string>::iterator Po=Resource.begin();Po!=Resource.end();++Po)
    {
        P<<"<"<<Po->first<<"> -> <"<<Po->second<<">"<<endl;
    }
}

class SceneBase:public ScriptionBlock,public HandleSeed
{
protected:
    POPicture Black;
    POPicture Right;
    POPicture Left;
    POPicture Small;
    Dialog Dia;
    Dialog Option;
public:
    virtual std::string GetParameter(SceneData* ,FileFactorPoint P,FileFactorPoint K);
    void Clean(){Right.Unused();Left.Unused();Small.Unused();Dia.Clear();Option.Clear();}
    SceneBase(){Dia.MaxChar(40);}
    SceneBase(FileFactorPoint B,FileFactorPoint E):ScriptionBlock(B,E){Dia.MaxChar(40);Option.MaxChar(30);}
    void Clear(){Dia.Clear();Right.Unused();Left.Unused();Small.Unused();}
    virtual void SetStart(){}
    //bool BaseAnalyze(CommentPoint*,OperatorPoint*,ScriptionData*);
    virtual bool Run(SceneData*){}
    //bool IsEnd(){return Point==End();}
    virtual void Click(){}
    virtual void Up(){}
    virtual void Down(){}
    virtual void Control(Handle<Information> I){}
};
std::string SceneBase::GetParameter(SceneData *SD,FileFactorPoint P, FileFactorPoint K)
{
    std::string Resource;
    if(P!=K)
    {
        if(P->Is("{"))
        {
            if((P+1)->Is("%"))
            {
                Resource=SD->Calculate(P+2,K-1);
            }else if((P+1)->Is("@"))
                Resource=Unite(P+2,K-1);
        }else
            Resource=Unite(P,K);
    }
    return Resource;
}

void SceneData::OutPutError(std::fstream &P)
{
    for(std::list<ScriptionError>::iterator Po=AllError.begin();Po!=AllError.end();++Po)
    {
        P<<Po->Data<<endl;
        if(Po->Line()>0)
        {
            P<<" --------------  In Line <"<<Po->Line()<<">"<<endl;
        }
    }
}

#endif // SCENEDATA_H
