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
glm::vec3 Player::tick(float deltaT,eventPacket e,std::vector<entity_small> *entities){
    glm::vec3 temp_move = e.player_move;
    temp_move.x*=0.2f;
    temp_move.y*=0.2f;
    temp_move.z*=0.2f;
    this->pos=physObj.tick(temp_move,deltaT);
    this->handleMouse(e);
    printf("pos: x: %f y: %f z: %f",pos.x,pos.y,pos.z);
    return this->pos;
}
entity_small Player::getSmallEnt(){
    entity_small ent;
    ent.pos=getPos();
    ent.team=PLAYER;
    return ent;
}
glm::vec3 Player::getPos(){
    return this->pos;
}
void Player::handleMouse(eventPacket in){
    if(in.mouse==LEFT){
        printf("clicked!\n");
        std::vector<intVec3> look = physics::getLookPos(this->pos,in.thetaX,in.thetaY);
        for(int i=0;i<look.size();i++){
            BLOCK_TYPES block = world->getBlock(look[i]);
            if(block!=AIR){
                printf("block set\n");
                world->setBlock(look[i],AIR);
            }
        }
    }
}