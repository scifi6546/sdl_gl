#include "entity.h"
#include "render_public.h"
#include <stdio.h>
Entity::Entity(){
    printf("wrong entityconstructor used\n");
}
Entity::Entity(glm::vec3 in,World* world_in,Text texture){
    this->position=in;
    //std::vector<Model> temp;
    this->texture=texture;
    std::vector<glm::vec3>pos={
        glm::vec3(0,0,0),
        glm::vec3(1,0,0),
        glm::vec3(1,1,0),
        glm::vec3(0,1,0)};

    std::vector<glm::vec2> texcoord={
        glm::vec2(0,0),
        glm::vec2(1,0),
        glm::vec2(1,1),
        glm::vec2(0,1)};
    std::vector<glm::vec3> normal={
        glm::vec3(0,0,-1),
        glm::vec3(0,0,-1),
        glm::vec3(0,0,-1),
        glm::vec3(0,0,-1)};

    std::vector<unsigned int> indicies={0,1,2,0,3,2};
    Model tempModel = Model(pos,texcoord,indicies,normal);
    model = genMesh(tempModel,this->texture,this->position);
    //model.push_back(Model(pos,texcoord,indicies,normal));
    //this->model=genMesh(this->file_name,this->texture,this->position);
    physObj = physics::physicsObj(world_in,in);
    
}
void Entity::tick(float deltaT){
    //printf("deltaT: %f\n",deltaT);
    //this->position=physics::runFrame(this->position,glm::vec3(0.0f,0.0f,0.0f),
    //world,deltaT);
    //printf("entity ticked!\n");
    //this->position=physObj.tick(glm::vec3(0.0f,0.0f,0.0f),deltaT);
    this->model.pos=this->position;
    //printf("Entity Ticked, pos: x:%f y: %f z: %f\n",this->position.x,this->position.y,this->position.z);
}
void Entity::draw(){
    drawMeshP(this->model);
    printf("Entity Drawn\n");
}