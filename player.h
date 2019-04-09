#ifndef PLAYER_H
#define PLAYER_H
#include "block.h"
#include "physics.h"
#include "event.h"
class Player{
    public:
        Player();
        Player(glm::vec3 pos_in,World *world_in);
        glm::vec3 tick(float deltaT,eventPacket e);
        glm::vec3 getPos();
    private:
        glm::vec3 pos;
        World *world;
        physics::physicsObj physObj;

};
#endif