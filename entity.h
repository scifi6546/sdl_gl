#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <glm/glm.hpp>
#include "block.h"
#include "physics.h"
class Entity{
    public:
        Entity();
        Entity(glm::vec3,World* world_in,Text texture);
        void tick(float deltaT);
        void draw();
    protected:
        std::string file_name="models/base.obj";
        glm::vec3 position;
        Mesh model;
        Text texture;
        physics::physicsObj physObj;
};
#endif