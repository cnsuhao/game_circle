#ifndef READSETTING_H
#define READSETTING_H
#include <string>
#include <fstream>
#include <map>
#include <list>

class Setting
{
    std::string File;
    std::map<std::string,std::map<std::string,std::list<std::string> > > Detail;
public:
    int Get(std::ifstream &,std::string &Resource);
    Setting(){}
    Setting(std::string N){Load(N);}
    void Load(std::string File);
    void CheckShow(std::fstream& Kc);
    bool IsReady(std::string N,std::string S);
    template <class T>
    bool Search(std::string N,std::string S,void (T::*Func)(std::string,std::string,std::string,int),T *t);
    bool FindFirst(std::string N,std::string S,std::string &T);
};

bool Setting::FindFirst(std::string N,std::string S,std::string &T)
{
    if(IsReady(N,S))
    {
        T=*Detail[N][S].begin();
        return true;
    }else{
        return false;
    }
}



template<class T>
bool Setting::Search(std::string N,std::string S,void (T::*Func)(std::string,std::string,std::string,int),T *t)
{
    if(IsReady(N,S))
    {
        std::list<std::string> &Tem=Detail[N][S];
        int i=1;
        for(std::list<std::string>::iterator Po=Tem.begin();Po!=Tem.end();++Po,++i)
        {
            (t->*Func)(N,S,*Po,i);
        }
        return true;
    }else{
        return false;
    }
}



bool Setting::IsReady(std::string N, std::string S)
{
    if(Detail.count(N)==1)
    {
        if(Detail[N].count(S)==1)
        {
            return true;
        }
    }
    return false;
}

void Setting::CheckShow(std::fstream &Kc)
{
    for(std::map<std::string,std::map<std::string,std::list<std::string> > >::iterator Po=Detail.begin();Po!=Detail.end();++Po)
    {
        Kc<<"<"<<Po->first<<">"<<":"<<endl;
        for(std::map<std::string,std::list<std::string> >::iterator Po2=Po->second.begin();Po2!=Po->second.end();++Po2)
        {
            Kc<<" <"<<Po2->first<<">:  "<<endl;
            for(std::list<std::string>::iterator Po3=Po2->second.begin();Po3!=Po2->second.end();++Po3)
            {
                Kc<<"         <"<<*Po3<<">  "<<endl;
            }
        }
    }
}

void Setting::Load(std::string F)
{
    File=F;
    Detail.clear();
    std::ifstream Txt(F.c_str());
    std::string Te;
    std::string Name;
    std::string Style;
    std::string Date;
    int Mode=1;;
    int NowMode=0;
    for(Mode=Get(Txt,Te);Mode!=0;Mode=Get(Txt,Te))
    {
        if(Mode==1)
        {
            if(Te=="NEW")
            {
                NowMode=1;
                Name.clear();
            }else if(Te=="END")
                NowMode=0;
        }else if(Mode==2)
        {
            Style=Te;
            NowMode=2;
        }else{
            if(NowMode==2)
            {
                Detail[Name][Style].push_back(Te);
            }else if(NowMode==1)
            {
                Name=Te;
            }
        }
    }
    Txt.close();
}


int Setting::Get(std::ifstream &File,std::string &R)
{
    std::string Tem;
    bool Continue=false;
    int Mode=3;
    char Tc;
    bool Normal=false;
    bool Start=false;
    while(!File.eof())
    {
        File.get(Tc);
        if(!Normal)
        {
            if(Tc=='#')
            {
                Mode=1;
                Start=true;
            }else if(Tc=='&')
            {
                Mode=2;
                Start=true;
            }else if(Tc=='[')
            {
                Continue=true;
                Start=true;
            }else if(Tc=='\\')
            {
                Normal=true;
                Start=true;
            }else{
                if(!Continue)
                {
                    if(Start)
                    {
                        if(Tc!=' '&&Tc!='\n'&&Tc!='\r')
                        {
                            Tem+=Tc;
                        }else{
                            R=Tem;
                            return Mode;
                        }
                    }else{
                        if(Tc!=' '&&Tc!='\n'&&Tc!='\r')
                        {
                            Tem+=Tc;
                            Start=true;
                        }
                    }

                }else{
                    if(Tc!=']')
                    {
                        Tem+=Tc;
                    }else{
                        R=Tem;
                        return Mode;
                    }
                }
            }
        }else{
            Tem+=Tc;
            Normal=false;
        }
    }
    R=Tem;
    return 0;
}
#endif // READSETTING_H
