#ifndef world_gen_h
#define world_gen_h
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "block.h"
#include "mesh.h"
namespace world_gen{
    const int WATER_LEVEL=130;
    const int SNOW_LEVEL=160;
    void init_gen();//initilizes world generator
    std::vector<Block*> getChunk(int x,int y, int z);//gets blocks of chunk
    std::vector<int>  getHeights(int x,int z);//gets heights of blocks
    int getNoise(int x,int z,float scale);//gets noise at a point
    float prng(int x,int y);//returns number between 1 and -1;
    
    float lerp(float x1,float x2,float x_needed,
    float z1,float z2,float y_needed,
    float ya,float yb,float yc, float yd);
    //linear interpolation
}
#endif