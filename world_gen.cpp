#include "world_gen.h"
void world_gen::init_gen(){

}
std::vector<Block*> world_gen::getChunk(int x,int y, int z){//gets blocks of chunk
    std::vector<Block*> out;
    out.reserve(chunkSize*chunkSize*chunkSize);
    for(int i=x;i<chunkSize+x;i++){//x
        for(int j=y;j<chunkSize+y;j++){//y
            for(int k=z;k<chunkSize+z;k++){//z
                if(j<20){
                    out.push_back(new Block(glm::vec3(i,j,k),ROCK));
                }else if(j<22){
                    out.push_back(new Block(glm::vec3(i,j,k),GRASS));
                }else{
                    out.push_back(new Block(glm::vec3(i,j,k),AIR));
                }
            }
        }
    }
    return out;
}
float world_gen::prng(int x,int y){
    int m=123352;
    int a=1213782313;
    int c=9823101;

    return 2*((a*x*y+x+y-c)%(m/387))/(m/387)-1;
}

