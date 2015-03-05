#ifndef SCENEFILE_H
#define SCENEFILE_H
#include "../p.o/scription/scriptionseparate.h"
#include "blockcontrol.h"
#include <map>
#include <fstream>
class SceneFile:public HandleSeed
{
public:
    FileFactor Tem;
    BlockControl InitComment;
    std::map<std::string,Handle<BlockControl> > BlockList;
    void LoadFile(std::string);
    void CheckDetail(std::fstream& K);
    Handle<BlockControl> GetBlock(std::string P){Handle<BlockControl> Tem;if(BlockList.count(P)!=0) return BlockList[P];return Tem;}
    SceneFile(){}
};

void SceneFile::LoadFile(std::string K)
{
    InitComment.Clear();
    BlockList.clear();
    Tem.Separate(K);
    ScriptionBlock Tect(Tem.Begin(),Tem.End());
    CommentReversePoint SCP=Tect.RBegin();
    CommentReversePoint Po=Tect.RBegin();
    for(;Po!=Tect.REnd();++Po)
    {
        if(Po->Is("Scene"))
        {
            BlockList.insert(std::make_pair(Po->Scription(),new BlockControl(SCP,Po)));
            SCP=Po;
            ++SCP;
        }
    }
    if(SCP!=Po)
        InitComment.CreatComment(SCP,Po);
}

void SceneFile::CheckDetail(std::fstream &K)
{
    K<<"File Adress <"<<Tem.Adress()<<">:"<<std::endl;
    K<<"InitBlock : "<<std::endl;
    InitComment.CheckDetail(K);
    for(std::map<std::string,Handle<BlockControl> >::iterator Po=BlockList.begin();Po!=BlockList.end();++Po)
    {
        K<<"  Block Name <"<<Po->first<<">"<<std::endl;
        Po->second->CheckDetail(K);
    }
}

#endif // SCENEFILE_H
