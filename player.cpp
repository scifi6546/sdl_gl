#include "player.h"
#include "stdio.h"

Player::Player(){
    printf("woring constructor used\n");
}
Player::Player(glm::vec3 pos_in,World *world_in){
    this->pos=pos_in;
    this->world = world_in;
    this->physObj=physics::physicsObj(world_in,pos_in);
}
glm::vec3 Player::tick(float deltaT,eventPacket e){
    glm::vec3 temp_move = e.player_move;
    temp_move.x*=0.2f;
    temp_move.y*=0.2f;
    temp_move.z*=0.2f;
    this->pos=physObj.tick(temp_move,deltaT);
    printf("this->pos: %f,%f,%f\n",this->pos.x,this->pos.y,this->pos.z);
    return this->pos;
}
glm::vec3 Player::getPos(){
    return this->pos;
}