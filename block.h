#ifndef Block_h
#define Block_h
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "mesh.h"
const bool DEBUG=false;
class BlockMesh{
    public:
        BlockMesh();
        std::vector<Model> getModel();
        std::vector<Model> model;
};
enum BLOCK_TYPES{AIR,GRASS,ROCK};
const int NUM_BLOCKS=2;
class Block{
    public:
        Block(glm::vec3 pos,BLOCK_TYPES blocktype);
        glm::vec3 pos;
        BLOCK_TYPES blockType;
};
class renderChunk{
    public:
        Model blocksMesh;//contains mesh for entire renderchunk
        
        std::vector<glm::vec3> blockLocations;
        RunTimeModel chunkModel;
        glm::vec3 root_pos;
        renderChunk(std::vector<Block> blocks,int x_start,
            int y_start,int z_start,glm::vec3 root_pos);
        void updateChunk(std::vector<Block> blocks,int x_start,int y_start,int z_start);
        void draw();
        ~renderChunk();
};
extern BlockMesh blockmesh; //mesh containing all faces of block
extern std::vector<RunTimeModel>models;
const int chunkSize=32;
const int renderChunkSize = chunkSize;//renderChunkSize has to equal chunk size I do not know why
const int CHUNK_RENDER_DIST=5;
class Chunk{
    public:
        Chunk(glm::vec3 root_pos);
        Chunk(std::vector<Block*> blocks,glm::vec3 root_pos);//heights 2 by 2 grid  x cols z rows
        /*
        Array Example
         XXXXXXXX
        Z
        Z
        Z
        Z

        */
        void setMeshes();
        void draw();
        ~Chunk();
    private:
        std::vector<renderChunk*> miniChunks;
        std::vector<Block> cubes;
        glm::vec3 root_pos;


        
        //std::vector<RunTimeModel> renderedBlocks;
        //std::vector<glm::vec3> renderedBlocksPos;
        //BlockMesh blockmesh;
        
};
class World{
    public:
        std::vector<std::vector<Chunk*>> loadedChunk;//outer vector is layers of inner layer
        std::vector<Chunk> testChunk;
        void draw();
        World();
        void tick(glm::vec3 player_pos);
        void shiftXp();//shifts chunk towards positive x
        void shiftXm();//shifts x towards negative x
        void shiftZp();
        void shiftZm();
    private:
        int rootx=0;
        int rootz=0;

};

#endif