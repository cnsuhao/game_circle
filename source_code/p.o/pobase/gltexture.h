#ifndef GLTEXTURE_H
#define GLTEXTURE_H
#include "../handle.h"
#include "../information.h"
#include <string>
#define PO_QUADS 1
#define PO_TRIANGLES 2
#define PO_POINTS 3
#define PO_LINES 4
#define PO_LINE_LOOP 5
class GLTexture :public HandleSeed
{
    friend class POMain;
    friend class PO;
    static std::map<std::string,Handle<GLTexture> > TextureMap;
    static std::list<std::string> DeleteList;
    static bool Change;
    std::string Adress;
    unsigned int C;
    bool ReadyToCount;
    GLTexture(const std::string& K,const int& P):Point(P),Adress(K),C(0),ReadyToCount(false){if(glIsTexture(P)==GL_TRUE){TextureMap.insert(std::make_pair(K,this));StartToCount();}}
public:
    unsigned Point;
    int W;
    int H;
    int Size;
    virtual void Display(unsigned int ES,float* TxP,int TSize,float* LoP,int LSize,float* Cop,int CSize,unsigned int* Or,unsigned int M);
    virtual void Display(unsigned int ES,float* TxP,int TSize,float* LoP,int LSize,unsigned int* Or,unsigned int M);
    virtual void Delete(){if(glIsTexture(Point)==GL_TRUE){glDeleteTextures(1,&Point);Point=0;}}
    void StartToCount(){ReadyToCount=true;}
    void GetHandle(){if(ReadyToCount)++C;}
    void HandleUnused(){if(ReadyToCount){--C;if(C==0){if(glIsTexture(Point)==GL_TRUE){DeleteList.push_back(Adress);Change=true;}}}}
    ~GLTexture(){Delete();}
};

std::map<std::string,Handle<GLTexture> > GLTexture::TextureMap;
std::list<std::string> GLTexture::DeleteList;
bool GLTexture::Change;


void GLTexture::Display(unsigned int ES, float *TxP, int TSize, float *LoP, int LSize, float *Cop, int CSize,unsigned int* Order,unsigned int All)
{
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(LSize,GL_FLOAT,0,LoP);
    glColorPointer(CSize,GL_FLOAT,0,Cop);
    glTexCoordPointer(TSize,GL_FLOAT,0,TxP);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Point);
    switch(ES)
    {
    case PO_QUADS:
        glDrawElements(GL_QUADS,All, GL_UNSIGNED_INT,Order);
        break;
    }
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void GLTexture::Display(unsigned int ES, float *TxP, int TSize, float *LoP, int LSize,unsigned int* Order,unsigned int All)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(LSize,GL_FLOAT,0,LoP);
    glTexCoordPointer(TSize,GL_FLOAT,0,TxP);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Point);
    switch(ES)
    {
    case PO_QUADS:
        glDrawElements(GL_QUADS,All, GL_UNSIGNED_INT,Order);
        break;
    }
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
#endif // POGIDATA_H
