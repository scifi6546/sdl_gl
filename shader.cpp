#include "shader.h"
#include "loadfile.h"
#include "error.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
static const unsigned int NUM_SHADERS=2;
GLuint program;
GLuint shaders[NUM_SHADERS];
glm::vec3 camera_pos;
GLuint camera_uni_pos;
GLuint translate_uni_pos;
GLuint look_uni_pos;
GLuint image_uni_pos;
GLuint ambient_c_pos;
GLuint ambient_i_pos;

GLuint sun_pos_pos;
GLuint sun_intensity_pos;
GLuint sun_c_pos;
int shaderInit(){
    std::string filename = "./shaders/shader";
    program=glCreateProgram();
    glError = glGetError();
    std::string file = loadFile(filename + ".vs");
    shaders[0] = createShader(file,GL_VERTEX_SHADER);
    file = loadFile(filename + ".fs");
    shaders[1] = createShader(file,GL_FRAGMENT_SHADER);
    for(unsigned int i=0;i<NUM_SHADERS;i++){
        glAttachShader(program,shaders[i]);
    }
    glBindAttribLocation(program,0,"position");
    glBindAttribLocation(program,1,"texcoord");
    glLinkProgram(program);
    int status;
    status = checkShaderError(program,GL_LINK_STATUS,true,"Error: Program failed to link");
    if(status!=0)
        return status;

    glValidateProgram(program);
    status = checkShaderError(program,GL_VALIDATE_STATUS,true,"program failed to validate");
    if(status!=0)
        return status;
    bind();
    glError=glGetError();  
    //setting uniforms
    camera_uni_pos =  glGetUniformLocation(program,"camera");
    translate_uni_pos =  glGetUniformLocation(program,"translate");
    look_uni_pos =  glGetUniformLocation(program,"look");
    image_uni_pos = glGetUniformLocation(program,"diffuse");
    ambient_c_pos = glGetUniformLocation(program,"ambient_color");
    ambient_i_pos = glGetUniformLocation(program,"ambient_intensity");

    sun_intensity_pos = glGetUniformLocation(program,"sun_intensity");
    sun_pos_pos = glGetUniformLocation(program,"sun_pos");
    sun_c_pos = glGetUniformLocation(program,"sun_color");

    glError=glGetError();
    printf("camera_uni_pos = %i\n",camera_uni_pos);
    printf("translate_uni_pos = %i\n",translate_uni_pos);
    printf("look_uni_pos = %i\n",look_uni_pos);
    printf("program:%i\n",shaders[0]);

    return 0;
}
int checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string errorMessage){
        GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE){
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        printf("%s: %s" ,errorMessage.c_str(),error);
        //std::cerr << errorMessage << ": '" << error << "'" << std::endl;
        return success;
    }
    return 0;
}
GLuint createShader(std::string &text,GLenum shaderType){
    GLuint shader = glCreateShader(shaderType);
    if(shader==0){
        printf("shader creation failed");
    }
    const GLchar* shaderstrings[1];
    shaderstrings[0]=text.c_str();
    GLint shaderstringlengths[1];
    shaderstringlengths[0]= text.length();

    glShaderSource(shader,1,shaderstrings,shaderstringlengths);
    glCompileShader(shader);
    checkShaderError(shader,GL_COMPILE_STATUS,false,"Error: shader not compiled");
    return shader;
}
void sendCamera(glm::mat4 cam){
    //finding uniform in shaderinit()
    glUniformMatrix4fv(camera_uni_pos,1,GL_FALSE,glm::value_ptr(cam));
}
void sendTranslate(glm::mat4 trans){
    //finding uniform in shaderinit()
    glUniformMatrix4fv(translate_uni_pos,1,GL_FALSE,glm::value_ptr(trans));
}

void sendLook(glm::mat4 look){
    //finding uniform in shaderinit()
    glUniformMatrix4fv(look_uni_pos,1,GL_FALSE,glm::value_ptr(look));
}
void sendAmbient(glm::vec3 color,GLfloat intensity,glm::vec3 sun_pos,GLfloat sun_intensity,glm::vec3 sun_color){
    glUniform3f(ambient_c_pos,color.x,color.y,color.z);
    glUniform1f(ambient_i_pos,intensity);

    glUniform1f(sun_intensity_pos,sun_intensity);
    glUniform3f(sun_pos_pos,sun_pos.x,sun_pos.y,sun_pos.z);
    glUniform3f(sun_c_pos,sun_color.x,sun_color.y,sun_color.z);
}
void setTexture(int unit){
    //printf("unit = %i\n",unit);
    glUniform1i(image_uni_pos,unit);
    glError = glGetError();
    if(glError!=0){
        printf("error %i\n",glError);
    }
}

void bind(){
    for(unsigned int i=0;i<NUM_SHADERS;i++){
        glDetachShader(program,shaders[i]);
        glDeleteShader(shaders[i]);
    }
     glUseProgram(program);
}