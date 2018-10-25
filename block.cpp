#include "block.h"
#include "texture.h"
#include <stdlib.h> 
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

std::vector<RunTimeModel>models;
BlockMesh blockmesh;

Block::Block(glm::vec3 pos,BLOCK_TYPES blocktype){
    this->pos = pos;
    this->blockType = blocktype;
}
BlockMesh::BlockMesh(){
    model.reserve(1);
    std::vector<glm::vec3> pos;
    pos.reserve(4);
    std::vector<glm::vec2> texcoord;
    texcoord.reserve(4);
    std::vector<unsigned int> indicies;
    indicies.reserve(6);

    pos.push_back(glm::vec3(0,0,0));
    pos.push_back(glm::vec3(1,0,0));
    pos.push_back(glm::vec3(1,1,0));
    pos.push_back(glm::vec3(0,1,0));

    texcoord.push_back(glm::vec2(0,0));
    texcoord.push_back(glm::vec2(1,0));
    texcoord.push_back(glm::vec2(1,1));
    texcoord.push_back(glm::vec2(0,1));

    indicies={0,1,2,0,3,2};
    model.push_back(Model(pos,texcoord,indicies));

    //face 1
    pos[0]=glm::vec3(1,0,0);
    pos[1]=glm::vec3(1,0,1);
    pos[2]=glm::vec3(1,1,1);
    pos[3]=glm::vec3(1,1,0);

    indicies={0,1,2,0,3,2};
    model.push_back(Model(pos,texcoord,indicies));

    //face 2
    pos[0]=glm::vec3(1,0,1);
    pos[1]=glm::vec3(0,0,1);
    pos[2]=glm::vec3(0,1,1);
    pos[3]=glm::vec3(1,1,1);

    indicies={0,1,2,0,3,2};
    model.push_back(Model(pos,texcoord,indicies));

    //face 3
    pos[0]=glm::vec3(0,0,1);
    pos[1]=glm::vec3(0,0,0);
    pos[2]=glm::vec3(0,1,0);
    pos[3]=glm::vec3(0,1,1);

    indicies={0,1,2,0,3,2};
    model.push_back(Model(pos,texcoord,indicies));

    //face 4
    pos[0]=glm::vec3(1,1,0);
    pos[1]=glm::vec3(1,1,1);
    pos[2]=glm::vec3(0,1,1);
    pos[3]=glm::vec3(0,1,0);

    indicies={0,1,2,0,3,2};
    model.push_back(Model(pos,texcoord,indicies));

    //face 5
    pos[0]=glm::vec3(1,0,0);
    pos[1]=glm::vec3(1,0,1);
    pos[2]=glm::vec3(0,0,1);
    pos[3]=glm::vec3(0,0,0);

    indicies={0,1,2,0,3,2};
    model.push_back(Model(pos,texcoord,indicies));
    


}
std::vector<Model> BlockMesh::getModel(){
    return model;
}
Chunk::Chunk(){
    cubes.reserve(chunkSize*chunkSize*chunkSize);
    for(int i =0;i<chunkSize;i++){//x
        for(int j=0;j<chunkSize;j++){//y
            for(int k=0;k<chunkSize;k++){//z
                int temps =(k)%6;
                if(temps>=3)
                    temps=0;
                else    
                    temps =1;

                BLOCK_TYPES temp = static_cast<BLOCK_TYPES>(temps);
                //std::cout<<"temp: "<<temp<<"\n";
                cubes.push_back(Block(glm::vec3(i,j,k),temp));
                //cubes.push_back(Block(glm::vec3(i,j,k),AIR));
            }
        }
    }
    models = initMesh(blockmesh.getModel());
    setMeshes();
}

void Chunk::setMeshes(){
    miniChunks.reserve((chunkSize/renderChunkSize)*
    (chunkSize/renderChunkSize)*(chunkSize/renderChunkSize));

    for(int i =0;i<chunkSize;i+=renderChunkSize){//x
        for(int j =0;j<chunkSize;j+=renderChunkSize){//y
            for(int k=0;k<chunkSize;k+=renderChunkSize){//z
                miniChunks.push_back(renderChunk(cubes,i,j,k));
            }
        }
    }
}
void Chunk::draw(){
    //drawMesh(models[0],glm::vec3(0,0,0));
    for(int i =0;i<miniChunks.size();i++){
        miniChunks[i].draw();
    }
}
renderChunk::renderChunk(std::vector<Block> blocks,int x_start,
            int y_start,int z_start){//root_pos is the inner lower right corner of the 
                                                                  //render chunk  
            updateChunk(blocks,x_start,y_start,z_start);
}
void renderChunk::updateChunk(std::vector<Block> blocks,int x_start,int y_start,int z_start){
    int x,y,z;
    Model tempmodel;
    char prohibited = 0;
    char blockBoundries=0;
    int blockBounds[6];
    for(int i =x_start;i<renderChunkSize+x_start;i++){//x
        for(int j=y_start;j<renderChunkSize+y_start;j++){//y
            for(int k=z_start;k<renderChunkSize+z_start;k++){//z
                x = i*chunkSize*chunkSize;
                y = j*chunkSize;
                z = k;

                
                for(int l=0;l<6;l++){
                    blockBounds[l]=0;
                }
                if(k!=0){//cheching face 0;
                    if(blocks[x+y+z-1].blockType==AIR&&blocks[x+y+z].blockType!=AIR){
                        blockBounds[0]=1;
                    }
                } else if(blocks[x+y+z].blockType!=AIR){
                        blockBounds[0]=1;
                }               

                if(i<chunkSize-1){ //checking face 1
                    if(blocks[(i+1)*chunkSize*chunkSize+y+z]
                        .blockType ==AIR && blocks[x+y+z].blockType!=AIR)
                        blockBounds[1]=1;
                }else if(blocks[x+y+z].blockType!=AIR){
                    blockBounds[1]=1;
                }
                    
                    //checking face 2
                if(k!=chunkSize-1){
                    if(blocks[x+y+z+1].blockType == AIR
                        && blocks[x+y+z].blockType!=AIR){
                        blockBounds[2]=1;
                    }
                }else if(blocks[x+y+z].blockType!=AIR){
                    blockBounds[2]=1;
                }

                    //checking face 3
                if(i!=0){
                    if(blocks[(i-1)*chunkSize*
                        chunkSize+y+z].blockType==AIR
                        &&blocks[x+y+z].blockType!=AIR){
                        blockBounds[3]=1;
                    }
                }else if(blocks[x+y+z].blockType!=AIR){
                    blockBounds[3]=1;
                }

                //checking face 4
                if(j<chunkSize-1){
                    if(blocks[x+(j+1)*chunkSize+z].blockType==AIR
                    && blocks[x+y+z].blockType!=AIR){
                        blockBounds[4]=1;
                    }
                }else if(blocks[x+y+z].blockType!=AIR){
                    blockBounds[4]=1;
                }

                    //checking face 5
                if(j>0){
                    if(blocks[x+(j-1)*chunkSize+z].blockType==AIR
                    &&blocks[x+y+z].blockType!=AIR){
                        blockBounds[5]=1;
                    }
                }else if(blocks[x+y+z].blockType!=AIR){
                    blockBounds[5]=1;
                }

                for(int l=0;l<6;l++){
                    if(blockBounds[l]==1){
                        this->blocksMesh.add(blockmesh.model[l],glm::vec3(i,j,k));
                        //this->blocks.push_back(models[l]);
                        //this->blockLocations.push_back(glm::vec3(i,j,k));
                    }
                }

            }
        }
    }
    if(!this->chunkModel.exists){
        std::vector<Model> temp_model={blocksMesh};
        std::vector<RunTimeModel> tempRun;
        tempRun=initMesh(temp_model);
        this->chunkModel=tempRun[0];
    } else{
         std::vector<Model> temp_model={blocksMesh};
        std::vector<RunTimeModel> tempRun;
        updateMesh(temp_model,tempRun);
        this->chunkModel=tempRun[0];
    }
}
void renderChunk::draw(){
    drawMesh(this->chunkModel,glm::vec3(0,0,0));
}
