#ifndef UNITESTYLE_H
#define UNITESTYLE_H
#include <fstream>
class URStyle
{
public:
    std::string Adress;
    int Style;
    URStyle(const URStyle& URS):Adress(URS.Adress),Style(URS.Style){}
    void operator=(const URStyle& URS){Adress=URS.Adress;Style=URS.Style;}
    URStyle():Style(0){}
    bool IsAvalible(){return Style!=0;}
    bool IsPicture(){return Style==1;}
    bool IsList(){return Style==2;}
    void SetPicture(std::string P){Adress=P;Style=1;}
    void SetPicture(){Style=1;}
    void SetList(std::string K){Adress=K;Style=2;}
    void SetList(){Style=2;}
    void CheckDetail(std::fstream& P,std::string Pre="");
    std::string Detail(){return Adress;}
};

void URStyle::CheckDetail(std::fstream &P,std::string Pre)
{
    P<<Pre<<"<"<<Adress<<">     ";
    if(IsList())
        P<<"_List"<<std::endl;
    else if(IsPicture())
        P<<"_Picture"<<std::endl;
    else
        P<<"_Unknow"<<std::endl;
}

#endif // UNITESTYLE_H
