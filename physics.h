#include <glm/glm.hpp>
#include "block.h"
#ifndef PHYSICS_H
#define PHYSICS_H
namespace physics{
    glm::vec3 runFrame(glm::vec3 player_pos, glm::vec3 player_v, World *gameWorld); 
} // name physics

#endif