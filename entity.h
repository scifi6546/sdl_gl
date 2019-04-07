#ifndef ENTITY_H
#define ENTITY_H
#include <glm/glm.hpp>
#include "mesh.h"
class Entity{
    public:
        Entity();
        Entity(glm::vec3);
        void tick();
        void draw();
    protected:
        glm::vec3 position;
        RunTimeModel model;
};
#endif