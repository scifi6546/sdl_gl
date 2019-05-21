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
void rManager::makeFBO(render_target &in){
    
    error = glGetError();
    glGenFramebuffers(1,&in.bufer_object.FBO_OJECT);
    printf("in_fbo_object: %i",in.bufer_object.FBO_OJECT);
    glBindFramebuffer(GL_FRAMEBUFFER,in.bufer_object.FBO_OJECT);
    in.bufer_object.attTexture=genTextureEmp();
    error = glGetError();
    /*
    glGenTextures(1,&in.bufer_object.COLOR_MAP);
    glBindTexture(GL_TEXTURE_2D,in.bufer_object.COLOR_MAP);
    error = glGetError();
    //Creating Color Map
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    */
    //glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,
    //    GL_TEXTURE_2D,in.bufer_object.COLOR_MAP,0);

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,in.bufer_object.attTexture.color_texture,0);
    error = glGetError();

    //creating depth map
    //glGenTextures(1,&in.bufer_object.DEPTH_MAP);
    //glBindTexture(GL_TEXTURE_2D,in.bufer_object.DEPTH_MAP);

    //glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH24_STENCIL8,800,600,0,GL_DEPTH_STENCIL,GL_UNSIGNED_INT_24_8,NULL);
    //error = glGetError();
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,
        GL_TEXTURE_2D,in.bufer_object.attTexture.depth_texture,0);
    //glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,
    //    GL_TEXTURE_2D,in.bufer_object.DEPTH_MAP,0);
    
    //glBindTexture(GL_TEXTURE_2D,0);
    error = glGetError();

    glBindFramebuffer(GL_FRAMEBUFFER,0);
    error = glGetError();
    
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
    //printf("bound buffer (after binding): %i ",in);
}
render_target gameWorld;//game world will be rendered to here
render_target bufferWorld;//Buffer shader
void initRender(){
    //unsigned int *inFBO = new unsigned int[2];
    //glGenFramebuffers(2,inFBO);
    initDisplay(display_width,display_height,"temp_title");

    

    shaderInit();
    initCam(60.0,display_width,display_height,.01,500);
    
    createShaderT({"shaders/shader.vs","shaders/shader.fs"},gameWorld);
    createShaderT({"shaders/buffer_shader.vs","shaders/buffer_shader.fs"},bufferWorld);
    rManager::makeFBO(gameWorld);
    std::vector<RunTimeModel> in = initMesh({buffer});
    buffer_model=in[0];
    error = glGetError();
    
}
void drawFrame(){
    
    rManager::bindFBO(gameWorld);
    //useGameShader();
    error = glGetError();
  
    useShader(gameWorld);
    //clearDisplay(0.0,.1,.6,1.0);
    
    //drawMesh(buffer_model,glm::vec3(1.0,100.0,0.0));
    draw();
    //glGetIntegerv(GL_FRAMEBUFFER_BINDING,&in);
    //printf("bound buffer (after rendering): %i\n",in);
    
    error = glGetError();
    if(error)
        printf("ERROR!\n\n\n");
    
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    useShader(bufferWorld);
    //useBufferShader();
    useFrameCam();
    //bindTexture(0,gameWorld,"diffuse");
    bindTexture(gameWorld.bufer_object.attTexture,gameWorld,"diffuse");
    //bindTexture(gameWorld.bufer_object.COLOR_MAP,gameWorld,"diffuse");
    //bindTexture(gameWorld.bufer_object.COLOR_MAP);
    drawMeshBuffer(buffer_model,glm::vec3(1.0,100.0,0.0));
    resetMouse(getWidth(),getHeight());
    updateDisplay();
    error=glGetError();
}
void sendCameraPos(glm::vec3 position){
    translateCam(position);
}
void sendCameraLook(float thetax,float thetay){
    rotate_cam(thetax,thetay);
}