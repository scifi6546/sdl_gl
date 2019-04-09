#include "physics.h"
using namespace physics;
glm::vec3 camVector(float thetay,float thetax,glm::vec3 player_pos,float t){
    glm::vec3 out;
    out.x=-cos(thetay)*t + player_pos.x;
    out.y=-sin(thetax)*t+player_pos.y;
    out.z=-sin(thetay)*t+player_pos.z;
    printf("t: %f\n",t);
    printf("thetaX: %f thetay: %f\n",thetax,thetax);
    printf("player_pos: x:%f y:%f z:%f\n",player_pos.x,player_pos.y,player_pos.z);
    printf("out x:%f y:%f z:%f\n",out.x,out.y,out.z);
    return out;
}
std::vector<intVec3> physics::getLookPos(glm::vec3 player_pos,float thetaX,float thetaY){
    std::vector<intVec3>out;
    out.reserve(look_dist);
    for(int i=0;i<look_dist;i++){
        intVec3 temp;
        out.push_back(temp);
        //calculating six planes
        float t;
        //plane 0
        t=(((float)-i) +floor(player_pos.y)-player_pos.y)/-sin(thetaX);
        printf("plane 0 t: %f\n",t);
        if(t>0){
            //out[i].y=round(-sin(thetaX)*t+player_pos.y);
            glm::vec3 temp = camVector(thetaY,thetaX,player_pos,t);
             printf("temp x:%f y:%f z:%f\n",temp.x,temp.y,temp.z);
            if(abs(temp.x-player_pos.x)<(float)i+1.0f && abs(temp.z-player_pos.z)<(float)i+1.0f){
                out[i].x=int(floor(temp.x));
                out[i].y=int(floor(temp.y));
                out[i].z=int(floor(temp.z));
            }
        }
        
        //plane 1
        t=(((float)i)+1.0f+floor(player_pos.y)-player_pos.y)/-sin(thetaX);
        printf("plane 1 t: %f\n",t);
        if(t>0){
            glm::vec3 temp = camVector(thetaY,thetaX,player_pos,t);
            printf("temp x:%f y:%f z:%f\n",temp.x,temp.y,temp.z);
            if(abs(temp.x-player_pos.x)<(float)i+1.0f && abs(temp.z-player_pos.z)<(float)i+1.0f){
                out[i].x=int(floor(temp.x));
                out[i].y=int(floor(temp.y));
                out[i].z=int(floor(temp.z));
            }
        }
      
        //plane 2
        t=(((float)-i) +floor(player_pos.x)-player_pos.x)/-cos(thetaY);
        printf("plane 2 t: %f\n",t);
        if(t>0){
            glm::vec3 temp = camVector(thetaY,thetaX,player_pos,t);
            printf("temp x:%f y:%f z:%f\n",temp.x,temp.y,temp.z);
            if(abs(temp.y-player_pos.y)<(float)i+1.0f && abs(temp.z-player_pos.z)<(float) i +1.0f){
                out[i].x=int(floor(temp.x));
                out[i].y=int(floor(temp.y));
                out[i].z=int(floor(temp.z)); 
            }
        }
     
        //plane 3
        t=(((float)i)+1.0f+floor(player_pos.x)-player_pos.x)/-cos(thetaY);
        printf("plane 3 t: %f\n",t);
        if(t>0){
            glm::vec3 temp = camVector(thetaY,thetaX,player_pos,t);
            printf("temp x:%f y:%f z:%f\n",temp.x,temp.y,temp.z);
            if(abs(temp.y-player_pos.y)<(float)i+1.0f && abs(temp.z-player_pos.z)<(float) i +1.0f){
                out[i].x=int(floor(temp.x));
                out[i].y=int(floor(temp.y));
                out[i].z=int(floor(temp.z)); 
            }
        }
           

        //plane 4
        t=(((float)-i) +floor(player_pos.z)-player_pos.z)/-sin(thetaY);
        printf("plane 4 t: %f\n",t);
        if(t>0){
            glm::vec3 temp = camVector(thetaY,thetaX,player_pos,t);
            printf("temp x:%f y:%f z:%f\n",temp.x,temp.y,temp.z);
            if(abs(temp.x-player_pos.x)<(float)i+1.0f && abs(temp.y-player_pos.y)<(float) i +1.0f){
                out[i].x=int(floor(temp.x));
                out[i].y=int(floor(temp.y));
                out[i].z=int(floor(temp.z)); 
            }
        }

        //plane 5
        t=(((float)i)+1.0f+floor(player_pos.z)-player_pos.z)/-sin(thetaY);
        printf("plane 5 t: %f\n",t);
        if(t>0){
            glm::vec3 temp = camVector(thetaY,thetaX,player_pos,t);
            printf("temp x:%f y:%f z:%f\n",temp.x,temp.y,temp.z);
            if(abs(temp.x-player_pos.x)<(float)i+1.0f && abs(temp.y-player_pos.y)<(float) i +1.0f){
                out[i].x=(int) floor(temp.x);
                out[i].y=(int) floor(temp.y);
                out[i].z=(int) floor(temp.z); 
            }
        }
        printf("out[%i] x:%i, y:%i, z: %i\n",i,out[i].x,out[i].y,out[i].z);
    }
    return out;
}
physicsObj::physicsObj(){
    printf("wrong physiscs constructor used\n");
}
physicsObj::physicsObj(World *in,glm::vec3 pos_in){
    this->gameWorld=in;
    this->pos = pos_in;
}
glm::vec3 physicsObj::tick(glm::vec3 accel,float deltaT){
    this->storedVel+= accel+gravity;
    //limits velocity
    glm::vec3 tempmove = this->storedVel*deltaT;

    if(tempmove.x>1){
        this->storedVel.x=0.9/deltaT;
    }
    if(tempmove.x<-1){
        this->storedVel.x=-0.9/deltaT;
    }

    if(tempmove.y>1){
        this->storedVel.y=0.9/deltaT;
    }
    if(tempmove.y<-1){
        this->storedVel.y=-0.9/deltaT;
    }

    if(tempmove.z>1){
        this->storedVel.z=0.9/deltaT;
    }
    if(tempmove.z<-1){
        this->storedVel.z=-0.9/deltaT;
    }
    int pX = floor(this->pos.x);
    int pY = floor(this->pos.y);
    int pZ = floor(this->pos.z);
    float p2Xf,p2Yf,p2Zf;

    this->pos = this->pos+this->storedVel*deltaT;

    if(this->storedVel.x>0){
        p2Xf = this->pos.x+this->storedVel.x*deltaT+collideDist;
    }else{
        p2Xf = this->pos.x+this->storedVel.x*deltaT-collideDist;
    }
    if(this->storedVel.y>0){
        p2Yf=this->pos.y+this->storedVel.y*deltaT+collideDist;
    }else{
        p2Yf=this->pos.y+this->storedVel.y*deltaT-collideDist;
    }
    if(this->storedVel.z>0){
        p2Zf=this->pos.z+this->storedVel.z*deltaT+collideDist;
    }else{
        p2Zf=this->pos.z+this->storedVel.z*deltaT-collideDist;
    }

    int p2X = floor(p2Xf);
    int p2Y = floor(p2Yf);
    int p2Z = floor(p2Zf);

    bool XCol = pX!=p2X;
    bool YCol = pY!=p2Y;
    bool ZCol = pZ!=p2Z;
    //printf("Stored Velocity: x: %f y: %f z: %f\n",stored_velocity.x,stored_velocity.y,stored_velocity.z);
    if(XCol || YCol || ZCol){
        BLOCK_TYPES temp = gameWorld->getBlock(p2X,p2Y,p2Z);
        if(temp!=AIR){
            if(XCol){
                if(pX>p2X){
                    this->pos.x = (float) pX+collideDist; 
                }else{
                    this->pos.x = (float) p2X-collideDist;
                }
                this->storedVel.x=0.0f;
                this->storedVel.y/=slideConst/deltaT;
                this->storedVel.z/=slideConst/deltaT;
            }
            if(YCol){
                if(pY>p2Y){
                    this->pos.y = (float) pY+collideDist;
                }else{
                    this->pos.y = (float) p2Y-collideDist;
                }
                this->storedVel.y = 0.0f;

                this->storedVel.x/=slideConst/deltaT;
                this->storedVel.z/=slideConst/deltaT;
            }
            if(ZCol){
                if(pZ>p2Z){
                    this->pos.z = (float) pZ+collideDist;
                }
                else{
                    this->pos.z = (float) p2Z-collideDist;
                }
                this->storedVel.z = 0.0f;
                this->storedVel.x/=slideConst/deltaT;
                this->storedVel.y/=slideConst/deltaT;
            }
            //printf("COLLIDED\n");
        }
    }
    return this->pos;
}