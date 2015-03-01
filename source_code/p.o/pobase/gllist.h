#ifndef GLLIST_H
#define GLLIST_H
#include "../handle.h"
#include "../information.h"
#include <string>
class GLList:public HandleSeed
{
    unsigned int List;
    void GetList(){if(glIsList(List))glDeleteLists(List,1);List=glGenLists(1);}
public:
    GLList():List(0){}
    void Compile(){GetList();glNewList(List,GL_COMPILE);}
    static void Finish(){glEndList();}
    void Display(){glCallList(List);}
    ~GLList(){if(glIsList(List)){glDeleteLists(List,1);List=0;}}
};

#endif // GLLIST_H
