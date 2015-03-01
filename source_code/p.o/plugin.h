#ifndef PLUGIN_H
#define PLUGIN_H
#include <string>
#include <set>
#include "handle.h"
#include "information.h"
#include "informationviewer.h"
#include "pobase/pomain.h"
class PO;
class Plugin:virtual public HandleSeed,public InformationViewer
{
    std::string Name;
public:
    Plugin(std::string K):Name(K){}
    std::string Scription(){return Name;}
    virtual void Init(PO*){}
    virtual void Layer3D(POMain*){}
    virtual void Layer2D(POMain*){}
    virtual void LayerBland(POMain*){}
    virtual void LayerSpecial(POMain*){}
    virtual void Accessorial(POMain*){}
    Handle<GLTexture> CreatPicture(std::string,POMain*);
    //Handle<GLTexture> CreatTTF(std::string,POMain*);
    void DeleteAllPicture(POMain*);
};

/*Handle<GLTexture> Plugin:: CreatTTF(std::string P,POMain* K)
{
    return K->CreatTTF(P);
}*/

Handle<GLTexture> Plugin::CreatPicture(std::string P, POMain * K)
{
    return K->CreatPicture(P);
}

#endif // PLUGIN_H
