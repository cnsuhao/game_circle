#ifndef GLUNIFYDATA_H
#define GLUNIFYDATA_H
#include <string>
#include <list>
#include "../handle.h"
class UnitefyData:public HandleSeed
{
    friend class POMain;
    static std::list<std::string> PictureDelete;
    static bool PictureChange;
    static std::list<std::string> ListDelete;
    static bool ListChange;
    unsigned int C;
    std::string Address;
public:
    void GetHandle(){C++;}
    void HandleUnused(){--C;}
    UnitefyData():C(0){}
};

static std::list<std::string> UnitefyData::PictureDelete;
static bool UnitefyData::PictureChange;
static std::list<std::string> UnitefyData::ListDelete;
static bool UnitefyData::ListChange;

#endif // GLUNIFYDATA_H
