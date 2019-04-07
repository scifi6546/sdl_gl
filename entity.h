#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <glm/glm.hpp>
#include "mesh.h"
#include "block.h"
#include "physics.h"
class Entity{
    public:
        Entity();
        Entity(glm::vec3,World* world_in);
        void tick(float deltaT);
        void draw();
    protected:
        std::string file_name="models/base.obj";
        glm::vec3 position;
        RunTimeModel model;
        physics::physicsObj physObj;
};
#endif