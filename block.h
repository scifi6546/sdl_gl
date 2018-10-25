#ifndef Block_h
#define Block_h
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "mesh.h"
class BlockMesh{
    public:
        BlockMesh();
        std::vector<Model> getModel();
        std::vector<Model> model;
};
enum BLOCK_TYPES{AIR,GRASS};
class Block{
    public:
        Block(glm::vec3 pos,BLOCK_TYPES blocktype);
        glm::vec3 pos;
        BLOCK_TYPES blockType;
};
class renderChunk{
    public:
        Model blocksMesh;//contains mesh for entire renderchunk
        std::vector<RunTimeModel> blocks;
        std::vector<glm::vec3> blockLocations;
        RunTimeModel chunkModel;
        renderChunk(std::vector<Block> blocks,int x_start,
            int y_start,int z_start);
        void updateChunk(std::vector<Block> blocks,int x_start,int y_start,int z_start);
        void draw();
};
extern BlockMesh blockmesh; //mesh containing all faces of block
extern std::vector<RunTimeModel>models;
const int chunkSize=256;
const int renderChunkSize = 32;
class Chunk{
    public:
        Chunk();
        void setMeshes();
        void draw();
    private:
        std::vector<renderChunk> miniChunks;
        std::vector<Block> cubes;

        
        //std::vector<RunTimeModel> renderedBlocks;
        //std::vector<glm::vec3> renderedBlocksPos;
        //BlockMesh blockmesh;
        
};

#endif