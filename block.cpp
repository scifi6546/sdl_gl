#include "block.h"
#include "texture.h"
#include "physics.h"
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
    std::vector<glm::vec3> normal;
    normal.reserve(6);
//face 0
    pos.push_back(glm::vec3(0,0,0));
    pos.push_back(glm::vec3(1,0,0));
    pos.push_back(glm::vec3(1,1,0));
    pos.push_back(glm::vec3(0,1,0));

    texcoord.push_back(glm::vec2(0,0));
    texcoord.push_back(glm::vec2(1,0));
    texcoord.push_back(glm::vec2(1,1));
    texcoord.push_back(glm::vec2(0,1));

    normal.push_back(glm::vec3(0,0,-1));
    normal.push_back(glm::vec3(0,0,-1));
    normal.push_back(glm::vec3(0,0,-1));
    normal.push_back(glm::vec3(0,0,-1));

    indicies={0,1,2,0,3,2};
    model.push_back(Model(pos,texcoord,indicies,normal));

    //face 1
    pos[0]=glm::vec3(1,0,0);
    pos[1]=glm::vec3(1,0,1);
    pos[2]=glm::vec3(1,1,1);
    pos[3]=glm::vec3(1,1,0);

    normal[0]=glm::vec3(1,0,0);
    normal[1]=glm::vec3(1,0,0);
    normal[2]=glm::vec3(1,0,0);
    normal[3]=glm::vec3(1,0,0);
    

    indicies={0,1,2,0,3,2};
    model.push_back(Model(pos,texcoord,indicies,normal));

    //face 2
    pos[0]=glm::vec3(1,0,1);
    pos[1]=glm::vec3(0,0,1);
    pos[2]=glm::vec3(0,1,1);
    pos[3]=glm::vec3(1,1,1);

    indicies={0,1,2,0,3,2};
    normal[0]=glm::vec3(0,0,1);
    normal[1]=glm::vec3(0,0,1);
    normal[2]=glm::vec3(0,0,1);
    normal[3]=glm::vec3(0,0,1);

    model.push_back(Model(pos,texcoord,indicies,normal));

    //face 3
    pos[0]=glm::vec3(0,0,1);
    pos[1]=glm::vec3(0,0,0);
    pos[2]=glm::vec3(0,1,0);
    pos[3]=glm::vec3(0,1,1);

    indicies={0,1,2,0,3,2};
    normal[0]=glm::vec3(-1,0,0);
    normal[1]=glm::vec3(-1,0,0);
    normal[2]=glm::vec3(-1,0,0);
    normal[3]=glm::vec3(-1,0,0);
    model.push_back(Model(pos,texcoord,indicies,normal));

    //face 4
    pos[0]=glm::vec3(1,1,0);
    pos[1]=glm::vec3(1,1,1);
    pos[2]=glm::vec3(0,1,1);
    pos[3]=glm::vec3(0,1,0);

    indicies={0,1,2,0,3,2};

    normal[0]=glm::vec3(0,1,0);
    normal[1]=glm::vec3(0,1,0);
    normal[2]=glm::vec3(0,1,0);
    normal[3]=glm::vec3(0,1,0);
    model.push_back(Model(pos,texcoord,indicies,normal));

    //face 5
    pos[0]=glm::vec3(1,0,0);
    pos[1]=glm::vec3(1,0,1);
    pos[2]=glm::vec3(0,0,1);
    pos[3]=glm::vec3(0,0,0);

    indicies={0,1,2,0,3,2};

    normal[0]=glm::vec3(0,-1,0);
    normal[1]=glm::vec3(0,-1,0);
    normal[2]=glm::vec3(0,-1,0);
    normal[3]=glm::vec3(0,-1,0);
    model.push_back(Model(pos,texcoord,indicies,normal));
    


}
std::vector<Model> BlockMesh::getModel(){
    return model;
}
Chunk::Chunk(std::vector<Block*> blocks,glm::vec3 root_pos){
    //printf("%f,%f,%f\n",root_pos.x,root_pos.y,root_pos.z);
    this->root_pos=root_pos;

    cubes.reserve(blocks.size());
    for(int i=0;i<blocks.size();i++){
        this->isBlock+=blocks[i]->blockType;
        cubes.push_back(*blocks[i]);
    }
    models = initMesh(blockmesh.getModel());
    this->setMeshes();
}

void Chunk::setMeshes(){
    if(miniChunks.size()>0){
        miniChunks.clear();
    }
    if(this->isBlock==0){
        return;
    }
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
    if(this->isBlock==0){
        return;
    }
    //if(DEBUG)
    //printf("chunk drawed x=%f y=%f z=%f\n",this->root_pos.x,this->root_pos.y,this->root_pos.z);
    
    //drawMesh(models[0],glm::vec3(0,0,0));
    for(int i =0;i<miniChunks.size();i++){
        miniChunks[i]->draw();
    }
}
BLOCK_TYPES Chunk::getBlock(int x, int y, int z){
    if(this->isBlock==0){
        return AIR;
    }
    int root_x = round(this->root_pos.x);
    int root_y = round(this->root_pos.y);
    int root_z = round(this->root_pos.z);

    int x_index = (x-root_x)*chunkSize*chunkSize;
    int y_index = (y-root_y)*chunkSize;
    int z_index = (z-root_z);
    Block temp = this->cubes[x_index+y_index+z_index];
    if(round(temp.pos.x)==x && round(temp.pos.y)==y && round(temp.pos.z)==z){
        return temp.blockType;
    }
    printf("ERROR WRONG POS!!!\n");
    printf("POS NEEDED: x: %i y: %i z: %i POS GOT: %i\n",x,y,z,round(temp.pos.x));
    printf("root x: %i root y: %i root z: %i\n",root_x,root_y,root_z);
    return AIR;
}
void Chunk::setBlock(int x, int y, int z, BLOCK_TYPES block){
    if(this->isBlock==0){
        return;
    }
    int root_x = round(this->root_pos.x);
    int root_y = round(this->root_pos.y);
    int root_z = round(this->root_pos.z);

    int x_index = (x-root_x)*chunkSize*chunkSize;
    int y_index = (y-root_y)*chunkSize;
    int z_index = (z-root_z);

    this->cubes[x_index+y_index+z_index] =  Block(glm::vec3(x,y,z),block);
    this->setMeshes();
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
World::World(glm::vec3 player_pos){
    this->player_pos=player_pos;
    this->loadedChunk.reserve(numVertChunks);
    for(int i=0;i<numVertChunks;i++){//y
        std::vector<Chunk*> t;
        this->loadedChunk.push_back(t);
        for(int j =-CHUNK_RENDER_DIST;j<=CHUNK_RENDER_DIST;j++){//x
            for(int k = -CHUNK_RENDER_DIST;k<=CHUNK_RENDER_DIST;k++){//z
            std::vector<Block*> tempBlocks = world_gen::getChunk(j*chunkSize,i*chunkSize,k*chunkSize);
                //printf("x: %i y: %i z: %i\n",j,i,k);
                this->loadedChunk[i].push_back(
                    new Chunk(tempBlocks,glm::vec3( j*chunkSize,i*chunkSize,k*chunkSize)));
            }
        }
    }
    
}
void World::draw(){
    //printf("drawn!!\n");
    bindTexture(0);
    for(int i=0;i<loadedChunk.size();i++){
        for(int j =0;j<this->loadedChunk[i].size();j++){
            //printf("i: %i, j: %i\n",i,j);
            this->loadedChunk[i][j]->draw();
            //this->testChunk[i].draw();
        }
    }
    drawWater();
    
}
void World::drawWater(){
    bindTexture(1);
    Model waterModel;
    waterModel.pos=std::vector<glm::vec3>(4);
    waterModel.pos[0]=glm::vec3(-1.0f*CHUNK_RENDER_DIST*chunkSize+this->rootx,
        world_gen::WATER_LEVEL-0.01f,
        -1.0f*CHUNK_RENDER_DIST*chunkSize+this->rootz);
    waterModel.pos[1]=glm::vec3(1.0f*CHUNK_RENDER_DIST*chunkSize+this->rootx,
        world_gen::WATER_LEVEL-0.01f,
        -1.0f*CHUNK_RENDER_DIST*chunkSize+this->rootz);
    waterModel.pos[2]=glm::vec3(1.0f*CHUNK_RENDER_DIST*chunkSize+this->rootx,
        world_gen::WATER_LEVEL-0.01f,
        1.0f*CHUNK_RENDER_DIST*chunkSize+this->rootz);
    waterModel.pos[3]=glm::vec3(-1.0f*CHUNK_RENDER_DIST*chunkSize+this->rootx,
        world_gen::WATER_LEVEL-0.01f,
        1.0f*CHUNK_RENDER_DIST*chunkSize+this->rootz);

    
    waterModel.indices={0,1,2,0,3,2};
    waterModel.texCoord={glm::vec2(-1.0f,-1.0f),glm::vec2(1.0f,-1.0f),glm::vec2(1.0f,1.0f),glm::vec2(-1.0f,1.0f)};
    waterModel.normal={glm::vec3(0.0f,1.0f,1.0f),glm::vec3(0.0f,1.0f,1.0f),glm::vec3(0.0f,1.0f,1.0f),glm::vec3(0.0f,1.0f,1.0f)};
    std::vector<Model> temp={waterModel};
    std::vector<RunTimeModel> tempRun = initMesh(temp);
    drawMesh(tempRun[0],glm::vec3(0.0,0.0,0.0));
   
}
glm::vec3 World::tick(glm::vec3 input_move, float delta_time){
    player_pos = physics::runFrame(player_pos,input_move,this,delta_time); 
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
    return player_pos;
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
    printf("shifted z plus\n"); 
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
    printf("shifted zm\n");
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
void World::printChunkPos(){
    printf("x,y,z\n");
    glm::vec3 tempPos;
    for(int i=0;i<this->loadedChunk.size();i++){
        for(int j=0;j<this->loadedChunk[i].size();j++){
            Chunk* tempC = this->loadedChunk[i][j];
            tempPos=tempC->getRoot(); 
            printf("%f,%f,%f\n",tempPos.x,tempPos.y,tempPos.z);
        }
    }
}
BLOCK_TYPES World::getBlock(int x, int y, int z){
    int y_index = floor(y/chunkSize);
    if(y>=chunkSize*numVertChunks||y<0){
        return AIR;
    }

    float temp = x-rootx;
    float tempCSize = chunkSize;

    int x_index = floor(temp/tempCSize)+CHUNK_RENDER_DIST; 
    x_index=x_index*(2*CHUNK_RENDER_DIST+1);

    float tempz = z-rootz;
    int z_index = floor((tempz)/tempCSize)+CHUNK_RENDER_DIST;

    Chunk* needed = 
        this->loadedChunk[y_index][x_index+z_index];
    return needed->getBlock(x,y,z);
}
void World::setBlock(int x, int y, int z, BLOCK_TYPES block){
    int y_index = floor(y/chunkSize);
    if(y>=chunkSize*numVertChunks||y<0){
        return;
    }

    float temp = x-rootx;
    float tempCSize = chunkSize;

    int x_index = floor(temp/tempCSize)+CHUNK_RENDER_DIST; 
    x_index=x_index*(2*CHUNK_RENDER_DIST+1);

    float tempz = z-rootz;
    int z_index = floor((tempz)/tempCSize)+CHUNK_RENDER_DIST;

    Chunk* needed = 
        this->loadedChunk[y_index][x_index+z_index];
    needed->setBlock(x,y,z,block);
}