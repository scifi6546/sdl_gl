#include "entity.h"
#include "render_public.h"
#include <stdio.h>
Entity::Entity(){
    printf("wrong constructor used\n");
}
Entity::Entity(glm::vec3 in,World* world_in,Text texture){
    this->position=in;
    std::vector<Model> temp;
    this->texture=texture;
    this->model=genMesh(this->file_name,this->texture,glm::vec3(0.0,0.0,0.0));
    physObj = physics::physicsObj(world_in,in);
    
}
void Entity::tick(float deltaT){
    //this->position=physics::runFrame(this->position,glm::vec3(0.0f,0.0f,0.0f),
    //world,deltaT);
    //printf("entity ticked!\n");
    this->position=physObj.tick(glm::vec3(0.0f,0.0f,0.0f),deltaT);
    this->model.pos=this->position;
}
void Entity::draw(){
    drawMeshP(this->model);
}