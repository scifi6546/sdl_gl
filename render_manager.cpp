#include "game_engine.h"

#include "render_manager.h"
unsigned int depthMapFBO;//depth map frame buffer
unsigned int depthMap;//depth map texture
void rManager::init(){
    glGenFramebuffers(1,&depthMapFBO);
    glGenTextures(1,&depthMap);
    glBindTexture(GL_TEXTURE_2D,depthMap);
    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,shadow_width,shadow_height,
        0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

}
void rManager::drawFrame(){
    draw();
    GLenum error = glGetError();
    if(error)
        printf("ERROR!\n\n\n");
}