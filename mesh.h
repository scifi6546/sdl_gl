#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
const int numBuffers=4;
enum Buffers{POSITION,TEXCOORD,INDEX,NORMAL};
class Model{
    
    public:
        std::vector<glm::vec3> pos;//position
        std::vector<glm::vec2> texCoord;//texture chordinates
        std::vector<unsigned int> indices;
        std::vector<glm::vec3> normal;
             
        Model(std::vector<glm::vec3> pos,//position
            std::vector<glm::vec2> texCoord,//texture chordinates
            std::vector<unsigned int> indices,std::vector<glm::vec3> normal){
                this->pos = pos;
                this->texCoord=texCoord;
                this->indices=indices;
                this->normal=normal;
                
                
        }
        void add(Model to_add,glm::vec3 pos);
        Model(){

        }
    private:
};
class RunTimeModel{
    public:
        GLuint meshNum;
        int index;
        unsigned int numIndicies;
        GLuint *vertex_array_buffers;  
        bool exists=false;//checks if runtime model is not empty
        RunTimeModel(GLuint meshNum,int index,unsigned int numIndicies,GLuint *buffers){
            this->meshNum=meshNum;
            this->index=index;
            this->numIndicies=numIndicies;
            this->vertex_array_buffers=(GLuint*) calloc(numBuffers,sizeof(GLuint));
            for(int i=0;i<numBuffers;i++){
                vertex_array_buffers[i]=buffers[i];
            }
            exists=true;
        };
        RunTimeModel(){
            exists=false;
        }
        std::string printString(){
            std::string out = "Mesh Num: "+std::to_string(meshNum);
            out+="\nIndex: "+std::to_string(index);
            out+="\nnumIndicies: " + std::to_string(numIndicies)+"\n\n";
            return out;
        };
};
extern std::vector<unsigned int> numIndicies;
std::vector<RunTimeModel> initMesh(std::vector<Model> models);//inits mesh
void drawMesh(RunTimeModel model,glm::vec3 position);//draws a model specified by meshNum at position
void updateMesh(std::vector<Model> models,std::vector<RunTimeModel> &to_update);
void deleteMesh(std::vector<RunTimeModel> &models);
#endif