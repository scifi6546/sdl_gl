#include "game_engine.h"
#include "display.h"
#include "render_manager.h"
#include "mesh.h"
#include "event.h"
#include "texture.h"
#include "camera.h"
#include "shader.h"
unsigned int frameBufferFBO;
unsigned int frameBufferTex;//depth map texture
unsigned int mainBufferFBO;
GLenum error;

Model buffer=Model(
    {glm::vec3(-1.0,-1.0,0.0),glm::vec3(1.0,-1.0,0.0),
        glm::vec3(1.0,1.0,0.0),glm::vec3(1.0,-1.0,1.0)},
    {glm::vec2(-1.0,-1.0),glm::vec2(1.0,-1.0),
        glm::vec2(1.0,1.0),glm::vec2(1.0,-1.0)},{0,1,2,0,3,2},
    {glm::vec3(0.0,0.0,-1.0),glm::vec3(0.0,0.0,-1.0),
        glm::vec3(0.0,0.0,-1.0),glm::vec3(0.0,0.0,-1.0)});
RunTimeModel buffer_model;
render_target rManager::makeFBO(){
    render_target temp;
    
    error = glGetError();
    glGenFramebuffers(1,&temp.bufer_object.FBO_OJECT);
    printf("temp_fbo_object: %i",temp.bufer_object.FBO_OJECT);
    glBindFramebuffer(GL_FRAMEBUFFER,temp.bufer_object.FBO_OJECT);
    error = glGetError();
    glGenTextures(1,&temp.bufer_object.COLOR_MAP);
    glBindTexture(GL_TEXTURE_2D,temp.bufer_object.COLOR_MAP);
    error = glGetError();
    //Creating Color Map
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,temp.bufer_object.COLOR_MAP,0);

    error = glGetError();
    //creating depth map
    glGenTextures(1,&temp.bufer_object.DEPTH_MAP);
    glBindTexture(GL_TEXTURE_2D,temp.bufer_object.DEPTH_MAP);

    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH24_STENCIL8,800,600,0,GL_DEPTH_STENCIL,GL_UNSIGNED_INT_24_8,NULL);
    error = glGetError();
    
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,temp.bufer_object.DEPTH_MAP,0);
    
    glBindTexture(GL_TEXTURE_2D,0);
    error = glGetError();

    glBindFramebuffer(GL_FRAMEBUFFER,0);
    error = glGetError();
    return temp;
    
}

void rManager::bindFBO(render_target in){

    error = glGetError();
    if(error!=0){
        printf("glError (before binding)!!!\n\n");
    }
    glBindFramebuffer(GL_FRAMEBUFFER,in.bufer_object.FBO_OJECT);//Error on this line!
    //printf("FBO OBJECT: %i\n",in.FBO_OJECT);
    error = glGetError();
    if(error!=0){
        printf("glError (after binding)!!!\n\n");
    }
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
        printf("framebuffer incomplete error!\nerror!\n");
    //printf("bound buffer (after binding): %i ",temp);
}
render_target gameWorld;//game world will be rendered to here
void rManager::init(){
    //unsigned int *tempFBO = new unsigned int[2];
    //glGenFramebuffers(2,tempFBO);
    gameWorld = rManager::makeFBO();
    std::vector<RunTimeModel> temp = initMesh({buffer});
    buffer_model=temp[0];
    error = glGetError();
    
}
void rManager::drawFrame(){
    
    rManager::bindFBO(gameWorld);
    useGameShader();
    error = glGetError();
  
    //clearDisplay(0.0,.1,.6,1.0);
    
    //drawMesh(buffer_model,glm::vec3(1.0,100.0,0.0));
    draw();
    //glGetIntegerv(GL_FRAMEBUFFER_BINDING,&temp);
    //printf("bound buffer (after rendering): %i\n",temp);
    
    error = glGetError();
    if(error)
        printf("ERROR!\n\n\n");
    
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    useBufferShader();
    useFrameCam();
    bindTexture(gameWorld.bufer_object.COLOR_MAP);
    drawMeshBuffer(buffer_model,glm::vec3(1.0,100.0,0.0));
    resetMouse(getWidth(),getHeight());
    updateDisplay();
    error=glGetError();
}