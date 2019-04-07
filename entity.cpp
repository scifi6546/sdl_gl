#include "entity.h"
#include <stdio.h>
Entity::Entity(){
    printf("wrong constructor used\n");
}
Entity::Entity(glm::vec3 in){
    this->position=in;
}