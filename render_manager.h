#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "render_target.h"


namespace rManager{
    const unsigned int shadow_width = 1024, shadow_height=1024;
    //initilizes frame buffer object
    render_target makeFBO();
    //binds a frame buffer object struct
    void bindFBO(render_target in);
    //initilizes render manager
    void init();
    //draws frame called every frame draw
    void drawFrame();
}
#endif