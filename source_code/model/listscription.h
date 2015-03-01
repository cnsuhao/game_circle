#ifndef LISTSCRIPTION_H
#define LISTSCRIPTION_H
#include "../p.o/pobase/gllist.h"
Handle<GLList> LoadListScription(std::string)
{
        FileFactor FF;
        FF.Separate(Ad);
        ScriptionBlock SB(FF.Begin(),FF.End());
        int PointStyle=1;//1 means V2, 2 means V2C3 ,3 means V2C
        for(CommentPoint CP=SB.Begin(),CP!=SB.End(),++CP)
        {
            if(CP->Is("Call"))
        }
    }
}

#endif // LISTSCRIPTION_H
