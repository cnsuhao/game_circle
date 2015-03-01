#ifndef RESOURCEADRESS_H
#define RESOURCEADRESS_H
#include <map>
#include "poscriptionseparate.h"
class ResourceAdress
{

public:
    std::map<std::string,std::string> Adress;
    void Load(std::string);
};
void ResourceAdress::Load(std::string AdressK)
{
    std::list<std::string> PN;
    std::list<std::string> PA;
    FileFactor FF;
    int Line;
    try{
        Separate(AdressK,FF,Line);
    }catch(ScriptionError Tem)
    {
        Tem.SetAdress(AdressK);
        throw Tem;
    }
    bool Checking=false;
    try{
        std::string Go;
        while(1)
        {
            Go=FF.Read();
            if(Go=="#")
            {
                Checking=true;
                Go=FF.Read();
                if(Go=="PA")
                {
                    Go=FF.Read();
                    PA.push_back(Go);
                }else if(Go=="PN")
                {
                    Go=FF.Read();
                    PN.push_back(Go);
                }else if(Go=="DPA")
                {
                    PA.pop_back();
                }else if(Go=="DPN")
                {
                    PN.pop_back();
                }else if(Go=="R")
                {
                    std::string A;
                    std::string N;
                    for(std::list<std::string>::iterator Po=PA.begin();Po!=PA.end();++Po)
                        A+=*Po;
                    for(std::list<std::string>::iterator Po=PN.begin();Po!=PN.end();++Po)
                        N+=*Po;
                    Go=FF.Read();
                    N+=Go;
                    Go=FF.Read();
                    A+=Go;
                    Adress[N]=A;
                }
                Checking=false;
            }else{
                throw ScriptionError("Wrong Scription");
            }
        }
    }catch(ScriptionError Tem)
    {
        if(Tem=="Reach End")
        {
            if(Checking)
            {
                ScriptionError TemC("Wrong Scrption",Tem.Line());
                TemC.SetAdress(AdressK);
                throw TemC;
            }
        }else if(Tem=="Not Init")
        {
            ScriptionError TemC("File Is Not Avalible",Tem.Line());
            TemC.SetAdress(AdressK);
            throw TemC;
        }
    }
}

#endif // RESOURCEADRESS_H
