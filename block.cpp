#include "block.h"
#include "texture.h"
#include "world_gen.h"
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
Chunk::Chunk(std::vector<Block*> blocks,glm::vec3 root_pos){
    printf("OTHER CONSTRUCTOR STARTED!\n");
    this->root_pos=root_pos;

    cubes.reserve(blocks.size());
    for(int i=0;i<blocks.size();i++){
        cubes.push_back(*blocks[i]);
    }
    models = initMesh(blockmesh.getModel());
    this->setMeshes();
}

void Chunk::setMeshes(){
    miniChunks.reserve((chunkSize/renderChunkSize)*
    (chunkSize/renderChunkSize)*(chunkSize/renderChunkSize));

    for(int i =0;i<chunkSize;i+=renderChunkSize){//x
        for(int j =0;j<chunkSize;j+=renderChunkSize){//y
            for(int k=0;k<chunkSize;k+=renderChunkSize){//z
                //renderChunk temp = renderChunk(cubes,i,j,k,this->root_pos);
                //miniChunks.push_back(temp);
                std::vector<Block> temp(cubes);
                miniChunks.push_back(new renderChunk(temp,i,j,k,this->root_pos));
            }
        }
    }
}
void Chunk::draw(){
    if(DEBUG)
    printf("chunk drawed x=%f y=%f z=%f\n",this->root_pos.x,this->root_pos.y,this->root_pos.z);
    
    //drawMesh(models[0],glm::vec3(0,0,0));
    for(int i =0;i<miniChunks.size();i++){
        miniChunks[i]->draw();
    }
}
Chunk::~Chunk(){
    miniChunks.clear();
    cubes.clear();
    std::cout<<"chunk deleted\n";
}
renderChunk::renderChunk(std::vector<Block> blocks,int x_start,
            int y_start,int z_start,glm::vec3 root_pos){//root_pos is the inner lower right corner of the 
            
            this->root_pos=root_pos;                                                  //render chunk  
            updateChunk(blocks,x_start,y_start,z_start);
}
void renderChunk::updateChunk(std::vector<Block> blocks,int x_start,int y_start,int z_start){
    //printf("root_pos: x:%f, y:%f z:%f\n",this->root_pos.x,this->root_pos.y,this->root_pos.z);
    int x,y,z;
    Model tempmodel;
    int blockBounds[6];
    int i,j,k;
    for(i =x_start;i<renderChunkSize+x_start;i++){//x
        for(j=y_start;j<renderChunkSize+y_start;j++){//y
            for(k=z_start;k<renderChunkSize+z_start;k++){//z
                x = i*chunkSize*chunkSize;
                y = j*chunkSize;
                z = k;

                
                for(int l=0;l<6;l++){
                    blockBounds[l]=0;
                }
                if(k!=0){//cheching face 0;
                    if(blocks[x+y+z-1].blockType==AIR &&blocks[x+y+z].blockType!=AIR){
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
                        Model temp = blockmesh.model[l];
                        float lf = l;
                        float x0=lf/6.0;
                        float x1=lf/6.0+1.0/6.0;

                        float y0=((float) (blocks[x+y+z].blockType-1))/(float) NUM_BLOCKS;
                        float y1=((float)blocks[x+y+z].blockType-1)/NUM_BLOCKS+1.0/(float)NUM_BLOCKS;
                        temp.texCoord[0]=glm::vec2(x0,y0);
                        temp.texCoord[1]=glm::vec2(x1,y0);
                        temp.texCoord[2]=glm::vec2(x1,y1);
                        temp.texCoord[3]=glm::vec2(x0,y1);

                    
                        this->blocksMesh.add(temp,glm::vec3(i,j,k)+this->root_pos);
                    }
                }

                //setting the texture correctly


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
renderChunk::~renderChunk(){
    printf("Render Chunk Deleted!\n");
    std::vector<RunTimeModel> temp = {this->chunkModel};
    deleteMesh(temp);
    this->blockLocations.clear();
}
World::World(){
    
    this->loadedChunk.reserve(CHUNK_RENDER_DIST*CHUNK_RENDER_DIST);
    for(int i=0;i<4;i++){//y
        std::vector<Chunk*> t;
        this->loadedChunk.push_back(t);
        for(int j =-CHUNK_RENDER_DIST;j<=CHUNK_RENDER_DIST;j++){//x
            for(int k = -CHUNK_RENDER_DIST;k<=CHUNK_RENDER_DIST;k++){//z
            //this->loadedChunk.push_back((Chunk*)calloc(1,sizeof(Chunk)));
            //Chunk *temp =; 
            std::vector<Block*> tempBlocks = world_gen::getChunk(j*chunkSize,i*chunkSize,k*chunkSize);
                this->loadedChunk[i].push_back(new Chunk(tempBlocks,glm::vec3( j*chunkSize,i*chunkSize,k*chunkSize)));
            //this->testChunk.push_back(Chunk(glm::vec3(i*chunkSize,0,j*chunkSize)));

            }
        }
    }
    
}
void World::draw(){
    for(int i=0;i<loadedChunk.size();i++){
        for(int j =0;j< this->loadedChunk[i].size();j++){
            this->loadedChunk[i][j]->draw();
            //this->testChunk[i].draw();
        }
    }
    
}
void World::tick(glm::vec3 player_pos){
    if(player_pos.x-rootx>=chunkSize){
        this->shiftXp();
    }
    if(player_pos.x-rootx<=-1*chunkSize){
        this->shiftXm();
    }
    if(player_pos.z-rootz>=chunkSize){
        this->shiftZp();
    }
    if(player_pos.z-rootz<=-1*chunkSize){
        this->shiftZm();
    }
}
void World::shiftXp(){
    printf("shifted X Plus");
    rootx+=chunkSize;
    
    //loading new chunks at bottom
    for(int i =0;i<this->loadedChunk.size();i++){
        this->loadedChunk[i].erase(this->loadedChunk[i].begin(),
        this->loadedChunk[i].begin()+2*CHUNK_RENDER_DIST+1);
        for(int j =-CHUNK_RENDER_DIST;j<=CHUNK_RENDER_DIST;j++){
            std::vector<Block*> temp=world_gen::getChunk(rootx+(CHUNK_RENDER_DIST)*chunkSize,i*chunkSize,rootz+j*chunkSize);
            this->loadedChunk[i].push_back(new Chunk(temp,glm::vec3(rootx+(CHUNK_RENDER_DIST)*chunkSize,i*chunkSize,rootz+j*chunkSize)));
        }
    }
    
}
void World::shiftXm(){
    
    printf("shifted X Minus");
    rootx-=chunkSize;
    
    for(int i=0;i<loadedChunk.size();i++){
        this->loadedChunk[i].erase(this->loadedChunk[i].end()-(2*CHUNK_RENDER_DIST+1),this->loadedChunk[i].end());
        for(int j =CHUNK_RENDER_DIST;j>=-1*CHUNK_RENDER_DIST;j--){
            std::vector<Block*> temp=world_gen::getChunk(rootx-CHUNK_RENDER_DIST*chunkSize,i*chunkSize,rootz+j*chunkSize);
            this->loadedChunk[i].insert(this->loadedChunk[i].begin(),
                new Chunk(temp,glm::vec3(rootx-CHUNK_RENDER_DIST*chunkSize,i*chunkSize,rootz+j*chunkSize)));
    }
    }
    
    
}
void World::shiftZp(){
    
    rootz+=chunkSize;
    for(int i=0;i<loadedChunk.size();i++){
        for(int j =-1*CHUNK_RENDER_DIST;j<=CHUNK_RENDER_DIST;j++){
            int erase_index = (j+CHUNK_RENDER_DIST)*(2*CHUNK_RENDER_DIST+1);
            this->loadedChunk[i].erase(this->loadedChunk[i].begin()+erase_index);
            int insert_index=(j+CHUNK_RENDER_DIST)*(2*CHUNK_RENDER_DIST+1)+2*CHUNK_RENDER_DIST;

            std::vector<Block*> temp=world_gen::getChunk(rootx+j*chunkSize,i*chunkSize,
                rootz+(CHUNK_RENDER_DIST)*chunkSize);
                        
            this->loadedChunk[i].insert(this->loadedChunk[i].begin()+insert_index,
                new Chunk(temp,glm::vec3(rootx+j*chunkSize,i*chunkSize,
                rootz+(CHUNK_RENDER_DIST)*chunkSize)));
        }
    }
    
    
}
void World::shiftZm(){
    rootz-=chunkSize;
    for(int i =0;i<loadedChunk.size();i++){
        for(int j =-1*CHUNK_RENDER_DIST;j<=CHUNK_RENDER_DIST;j++){
            int erase_index=(j+CHUNK_RENDER_DIST)*(2*CHUNK_RENDER_DIST+1)+2*CHUNK_RENDER_DIST;
            this->loadedChunk[i].erase(this->loadedChunk[i].begin()+erase_index);
            int insert_index=(j+CHUNK_RENDER_DIST)*(2*CHUNK_RENDER_DIST+1);
            std::vector<Block*> temp=world_gen::getChunk(rootx+j*chunkSize,
                i*chunkSize,rootz-CHUNK_RENDER_DIST*chunkSize);

            this->loadedChunk[i].insert(this->loadedChunk[i].begin()+insert_index,
                new Chunk(temp,glm::vec3(rootx+j*chunkSize,i*chunkSize,rootz-CHUNK_RENDER_DIST*chunkSize)));
        }
    }
    
}