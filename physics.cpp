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
