#include "world_gen.h"
void world_gen::init_gen(){

}
std::vector<Block*> world_gen::getChunk(int x,int y, int z){//gets blocks of chunk
    std::vector<Block*> out;
    std::vector<int> height = getHeights(x,z);
    out.reserve(chunkSize*chunkSize*chunkSize);
    float temp;
    for(int i=x;i<chunkSize+x;i++){//x
        for(int j=y;j<chunkSize+y;j++){//y
            for(int k=z;k<chunkSize+z;k++){//z
            temp = (float) height[(i-x)*chunkSize+k-z];
            
            int t_h=temp;
           // printf("temp: %f t_h: %i \n",temp,t_h);
                if(j<=t_h-2){
                    out.push_back(new Block(glm::vec3(i,j,k),ROCK));
                }else if(j<=t_h){
                    //decide whether ot not to place grass or snow
                    if(j<SNOW_LEVEL)
                        out.push_back(new Block(glm::vec3(i,j,k),GRASS));
                    else
                    {
                        out.push_back(new Block(glm::vec3(i,j,k),SNOW));
                    }
                    
                }else{
                    //fill lower heights with water
                    out.push_back(new Block(glm::vec3(i,j,k),AIR));
                }
            }
        }
    }
    return out;
}
//memory layout
/*
z --->
x
 |
 |
 |
\/

*/
std::vector<int> world_gen::getHeights(int x, int z){
    std::vector<int> out;
    out.reserve(chunkSize*chunkSize);
    for(int i=x;i<x+chunkSize;i++){//x
        for(int j=z;j<z+chunkSize;j++){//z
            int height = 0;
            for(int scale = 5; scale<=45;scale+=10){
                height+=getNoise(i,j,scale);
            }

            out.push_back(height);
        }
    }
    return out;
}

float world_gen::lerp(float x0,float x1,float x_needed,
    float z0,float z1,float z_needed,
    float ya,float yb,float yc, float yd){

    float p1=((ya-yb)/(x0-x1))*(x_needed-x0)+ya;
    float p2=((yd-yc)/(x0-x1))*(x_needed-x0)+yd;

    return ((p1-p2)/(z0-z1))*(z_needed-z0)+p1;
}
float world_gen::prng(int x,int y){
    long m=453565;
    long a=11514;
    long c=1594;
    INT32_MAX;
    float mf=m;
    //float mod=(sin((x*y+a*y+x*c+c)/mf)+1.0)*0.5;
    float mod=(abs(a*x*y+y*x*c+187692+x+y-a*x*c*123))%m;
    return mod/mf;
    //return .5;
}
int world_gen::getNoise(int x, int z, float scale){
    float ya,yb,yc,yd;

            float x1,x2;
            float z1,z2;
            x1=floor(x/scale);
            x2=x1+1;
            
            z1=floor(z/scale);
            z2=z1+1;

            ya=prng(x1,z1)*scale*2.0;
            yb=prng(x2,z1)*scale*2.0;
            yc=prng(x2,z2)*scale*2.0;
            yd=prng(x1,z2)*scale*2.0;
            float i_f= x;
            float j_f = z;
            float rel=lerp(x1,x2,i_f/scale,
                z1,z2,j_f/scale,ya,yb,yc,yd);
    return rel;
}

