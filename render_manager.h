#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "render_target.h"
//public functions
//initilizes render manager
void initRender();
//draws frame called every frame draw
void drawFrame();
/*
NOT TESTED OR IMPLEMENTED
sends the camera position (world coordinates) to the rendering engine 
*/
void sendCameraPos(glm::vec3 position);

/*
NOT TESTED OR IMPLEMENTED
Sends the camera look to the rendering engine
*/
void sendCameraLook(float thetax,float thetay);
//private functions
namespace rManager{
    const unsigned int shadow_width = 1024, shadow_height=1024;
    //initilizes frame buffer object and modifies in
    void makeFBO(render_target &in);
    //binds a frame buffer object struct
    void bindFBO(render_target in);
}
#endif