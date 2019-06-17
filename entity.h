#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <glm/glm.hpp>
#include "block.h"
#include "physics.h"
//enum showing team of player
enum PLAYER_TEAM{PLAYER,ENEMY};
struct entity_small{
    PLAYER_TEAM team;
    glm::vec3 pos;
};
class Entity{
    public:
        Entity();
        Entity(glm::vec3,World* world_in,Text texture);
        void tick(float deltaT,std::vector<entity_small> *entities);
        void draw();
        entity_small getSmallEnt();
    protected:
        const std::string file_name="models/enemy.obj";
        glm::vec3 position;
        Mesh model;
        Text texture;
        physics::physicsObj physObj;
};
#endif