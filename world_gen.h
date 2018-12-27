#ifndef world_gen_h
#define world_gen_h
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "block.h"
#include "mesh.h"
namespace world_gen{
    void init_gen();//initilizes world generator
    std::vector<Block*> getChunk(int x,int y, int z);//gets blocks of chunk
    float prng(int x,int y);//returns number between 1 and -1;
}
#endif