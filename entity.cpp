#include "entity.h"
#include "render_public.h"
#include <stdio.h>
Entity::Entity(glm::vec3 pos_in,World* world_in,Text texture){
    model = genMesh(file_name,texture,pos_in);
    physObj = physics::physicsObj(world_in,pos_in);
}
void Entity::draw(){
    this->model.pos=this->position;
    drawMeshP(this->model);
    //printf("drawn model\n");
}
void Entity::tick(float deltaT,std::vector<entity_small> *entities){
    glm::vec3 pos_temp=glm::vec3(0.0f,0.0f,0.0f);
    for(int i=0;i<entities->size();i++){
        if(entities->at(i).team==PLAYER){
            pos_temp=entities->at(i).pos-this->position;
            float len=sqrt((pos_temp.x*pos_temp.x)+(pos_temp.y*pos_temp.y)+
                (pos_temp.z*pos_temp.z));
            pos_temp.x/=len;
            pos_temp.y/=len;
            pos_temp.z/=len;

            pos_temp*=0.05f;
        }
    }
    this->position=physObj.tick(pos_temp,deltaT);
    //printf("ticked\n");
}
entity_small Entity::getSmallEnt(){
    entity_small ret;
    ret.pos=this->position;
    ret.team=ENEMY;
}