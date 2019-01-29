#include "physics.h"
glm::vec3 stored_velocity=glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 physics::runFrame(glm::vec3 player_pos, glm::vec3 player_v, World * gameWorld, float deltaT){
    stored_velocity += player_v*playerMoveSpeed+physics::gravity;
    //limits velocity
    glm::vec3 tempmove = stored_velocity*deltaT;

    if(tempmove.x>1){
        stored_velocity.x=0.9/deltaT;
    }
    if(tempmove.x<-1){
        stored_velocity.x=-0.9/deltaT;
    }

    if(tempmove.y>1){
        stored_velocity.y=0.9/deltaT;
    }
    if(tempmove.y<-1){
        stored_velocity.y=-0.9/deltaT;
    }

    if(tempmove.z>1){
        stored_velocity.z=0.9/deltaT;
    }
    if(tempmove.z<-1){
        stored_velocity.z=-0.9/deltaT;
    }
    int pX = floor(player_pos.x);
    int pY = floor(player_pos.y);
    int pZ = floor(player_pos.z);
    float p2Xf,p2Yf,p2Zf;

    player_pos = player_pos+stored_velocity*deltaT;

    if(stored_velocity.x>0){
        p2Xf = player_pos.x+stored_velocity.x*deltaT+collideDist;
    }else{
        p2Xf = player_pos.x+stored_velocity.x*deltaT-collideDist;
    }
    if(stored_velocity.y>0){
        p2Yf=player_pos.y+stored_velocity.y*deltaT+collideDist;
    }else{
        p2Yf=player_pos.y+stored_velocity.y*deltaT-collideDist;
    }
    if(stored_velocity.z>0){
        p2Zf=player_pos.z+stored_velocity.z*deltaT+collideDist;
    }else{
        p2Zf=player_pos.z+stored_velocity.z*deltaT-collideDist;
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
                    player_pos.x = (float) pX+collideDist; 
                }else{
                    player_pos.x = (float) p2X-collideDist;
                }
                stored_velocity.x=0.0f;
                stored_velocity.y/=slideConst/deltaT;
                stored_velocity.z/=slideConst/deltaT;
            }
            if(YCol){
                if(pY>p2Y){
                    player_pos.y = (float) pY+collideDist;
                }else{
                    player_pos.y = (float) p2Y-collideDist;
                }
                stored_velocity.y = 0.0f;

                stored_velocity.x/=slideConst/deltaT;
                stored_velocity.z/=slideConst/deltaT;
            }
            if(ZCol){
                if(pZ>p2Z){
                    player_pos.z = (float) pZ+collideDist;
                }
                else{
                    player_pos.z = (float) p2Z-collideDist;
                }
                stored_velocity.z = 0.0f;

                stored_velocity.x/=slideConst/deltaT;
                stored_velocity.y/=slideConst/deltaT;
            }
            //printf("COLLIDED\n");
        }
    }
    return player_pos;
}