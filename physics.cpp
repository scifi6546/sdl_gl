#include "physics.h"
glm::vec3 physics::runFrame(glm::vec3 player_pos, glm::vec3 player_v, World * gameWorld, float deltaT){
    printf("delta Time: %f\n",deltaT);
    return player_pos+player_v*deltaT;
}