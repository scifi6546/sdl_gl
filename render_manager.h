#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace rManager{
    const unsigned int shadow_width = 1024, shadow_height=1024;

    void init();
    void drawFrame();
}
#endif