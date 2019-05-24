#include "entity.h"
#include "render_public.h"
#include <stdio.h>
Entity::Entity(){
    printf("wrong constructor used\n");
}
Entity::Entity(glm::vec3 in,World* world_in){
    this->position=in;
    std::vector<Model> temp;
    temp.push_back(Model(this->file_name));
    this->model=initMesh(std::vector<Model>(temp))[0];
    physObj = physics::physicsObj(world_in,in);
}
void Entity::tick(float deltaT){
    //this->position=physics::runFrame(this->position,glm::vec3(0.0f,0.0f,0.0f),
    //world,deltaT);
    //printf("entity ticked!\n");
    this->position=physObj.tick(glm::vec3(0.0f,0.0f,0.0f),deltaT);
}
void Entity::draw(){
    drawMesh(this->model,this->position);
}