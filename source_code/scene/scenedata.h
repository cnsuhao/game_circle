#ifndef SCENEDATA_H
#define SCENEDATA_H
#include "../p.o/popicture.h"
#include "../p.o/dialog.h"

class SceneData
{
public:
    std::map<std::string,int> ValueMap;
    std::map<std::string,POPicture > PictureResource;
};

#endif // SCENEDATA_H
