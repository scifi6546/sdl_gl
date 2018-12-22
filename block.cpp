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
Chunk::Chunk(glm::vec3 root_pos){
    if(DEBUG)
    printf("root_pos: x:%f y:%f z:%f\n",root_pos.x,root_pos.y,root_pos.z);
    this->root_pos=root_pos;
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
    this->setMeshes();
}
Chunk::Chunk(std::vector<char> heights,glm::vec3 root_pos){
    printf("OTHER CONSTRUCTOR STARTED!\n");
    this->root_pos=root_pos;
    cubes.reserve(chunkSize*chunkSize*chunkSize);
    for(int i =0;i<chunkSize;i++){//x
        for(int j=0;j<chunkSize;j++){//z
            for(int k=0;k<heights[i+j*chunkSize];i++){
                cubes.push_back(Block(glm::vec3(i,k,j),GRASS));
            }

        }
    }
}

void Chunk::setMeshes(){
    miniChunks.reserve((chunkSize/renderChunkSize)*
    (chunkSize/renderChunkSize)*(chunkSize/renderChunkSize));

    for(int i =0;i<chunkSize;i+=renderChunkSize){//x
        for(int j =0;j<chunkSize;j+=renderChunkSize){//y
            for(int k=0;k<chunkSize;k+=renderChunkSize){//z
                //renderChunk temp = renderChunk(cubes,i,j,k,this->root_pos);
                //miniChunks.push_back(temp);
                miniChunks.push_back(new renderChunk(cubes,i,j,k,this->root_pos));
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
renderChunk::renderChunk(std::vector<Block> &blocks,int x_start,
            int y_start,int z_start,glm::vec3 root_pos){//root_pos is the inner lower right corner of the 
            
            this->root_pos=root_pos;                                                  //render chunk  
            updateChunk(blocks,x_start,y_start,z_start);
}
void renderChunk::updateChunk(std::vector<Block> &blocks,int x_start,int y_start,int z_start){
    printf("root_pos: x:%f, y:%f z:%f\n",this->root_pos.x,this->root_pos.y,this->root_pos.z);
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
                        this->blocksMesh.add(blockmesh.model[l],glm::vec3(i,j,k)+this->root_pos);
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
renderChunk::~renderChunk(){
    printf("Render Chunk Deleted!\n");
    std::vector<RunTimeModel> temp = {this->chunkModel};
    deleteMesh(temp);
    this->blockLocations.clear();
}
World::World(){
    this->loadedChunk.reserve(CHUNK_RENDER_DIST*CHUNK_RENDER_DIST);
    for(int i =-CHUNK_RENDER_DIST;i<=CHUNK_RENDER_DIST;i++){//x
        for(int j = -CHUNK_RENDER_DIST;j<=CHUNK_RENDER_DIST;j++){//z
            //this->loadedChunk.push_back((Chunk*)calloc(1,sizeof(Chunk)));
            //Chunk *temp =; 
            this->loadedChunk.push_back(new Chunk(glm::vec3( i*chunkSize,0,j*chunkSize)));
            //this->testChunk.push_back(Chunk(glm::vec3(i*chunkSize,0,j*chunkSize)));

        }
    }
}
void World::draw(){
    for(int i =0;i<this->loadedChunk.size();i++){
        this->loadedChunk[i]->draw();
        //this->testChunk[i].draw();
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
    this->loadedChunk.erase(this->loadedChunk.begin(),
        this->loadedChunk.begin()+2*CHUNK_RENDER_DIST+1);
    //loading new chunks at bottom
    for(int i =-CHUNK_RENDER_DIST;i<=CHUNK_RENDER_DIST;i++){
        this->loadedChunk.push_back(new Chunk(glm::vec3(rootx+(CHUNK_RENDER_DIST)*chunkSize,0,rootz+i*chunkSize)));
    }
}
void World::shiftXm(){
    
    printf("shifted X Minus");
    rootx-=chunkSize;
    this->loadedChunk.erase(this->loadedChunk.end()-(2*CHUNK_RENDER_DIST+1),this->loadedChunk.end());
    for(int i =CHUNK_RENDER_DIST;i>=-1*CHUNK_RENDER_DIST;i--){
        this->loadedChunk.insert(this->loadedChunk.begin(),
            new Chunk(glm::vec3(rootx-CHUNK_RENDER_DIST*chunkSize,0,rootz+i*chunkSize)));
    }
    
}
void World::shiftZp(){
    
    rootz+=chunkSize;
    for(int i =-1*CHUNK_RENDER_DIST;i<=CHUNK_RENDER_DIST;i++){
        int erase_index = (i+CHUNK_RENDER_DIST)*(2*CHUNK_RENDER_DIST+1);
        this->loadedChunk.erase(this->loadedChunk.begin()+erase_index);
        int insert_index=(i+CHUNK_RENDER_DIST)*(2*CHUNK_RENDER_DIST+1)+2*CHUNK_RENDER_DIST;
        this->loadedChunk.insert(this->loadedChunk.begin()+insert_index,
            new Chunk(glm::vec3(rootx+i*chunkSize,0,rootz+(CHUNK_RENDER_DIST)*chunkSize)));
    }
    
}
void World::shiftZm(){
    rootz-=chunkSize;
    for(int i =-1*CHUNK_RENDER_DIST;i<=CHUNK_RENDER_DIST;i++){
        int erase_index=(i+CHUNK_RENDER_DIST)*(2*CHUNK_RENDER_DIST+1)+2*CHUNK_RENDER_DIST;
        this->loadedChunk.erase(this->loadedChunk.begin()+erase_index);
        int insert_index=(i+CHUNK_RENDER_DIST)*(2*CHUNK_RENDER_DIST+1);
        this->loadedChunk.insert(this->loadedChunk.begin()+insert_index,
            new Chunk(glm::vec3(rootx+i*chunkSize,0,rootz-CHUNK_RENDER_DIST*chunkSize)));
    }
}