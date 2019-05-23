#include "render_public.h"
#include "render_manager.h"
#include "mesh.h"
#include "texture.h"
//NOT TO BE EXPOSED TO END USER

/*
A vector containing all runtime models and accociated id's
The first element is id second is runtime model
*/
std::vector<std::pair<unsigned int,RunTimeModel>> Models;
/*
A vector containing all textures and associated id's
The first element is the id and the second is associated texture
The id's are ascending order
*/
std::vector<std::pair<unsigned int,Texture>> Textures;
/*
This inserts a texture into the Textures vec
*/
Text insertTexture(Texture in){
    unsigned int new_id = Textures.size();
    Textures.push_back(std::pair(new_id,in));
    Text out;
    out.id=new_id;
    return out;
}
/*
Checks the integreity of the texture vector
*/
bool checkTextInteg(){
    int last_id = std::get<0>(Textures[0]);
    for(int i=0;i<Textures.size();i++){
        int new_id = std::get<0>(Textures[i]);
        if(new_id!=last_id+1){
            return false;
        }
        last_id=new_id;
    }
    return true;
}
/*
This Inserts a mesh into the Models vector
*/
Mesh insertMesh(RunTimeModel in){
    unsigned int new_id = Models.size();
    Models.push_back(std::pair(new_id,in));
    Mesh out;
    out.id=new_id;
    return out;
}
/*
This gets a model from the Models vector
*/
RunTimeModel getModel(Mesh in){
    return std::get<1>(Models[in.id]);
}
void initRenderP(){
    initRender();
}
void quitRender(){
    quitRender_INT();
}
Text genTextureP(std::string filename){
    Texture temp = genTexture(filename);
    return insertTexture(temp);
}

Mesh genMesh(Model in,Text texture,glm::vec3 pos){
    RunTimeModel temp = initMesh({in})[0];
    Mesh out = insertMesh(temp);
    out.texture_use=texture;
    out.pos=pos;
    return out;
}
bool isMeshValid(Mesh in){
    if(in.id<0){
        return false;
    }
    return true;
}
void draw(Mesh in){
    drawMesh(getModel(in),in.pos);
}