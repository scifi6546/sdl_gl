#include "shader.h"
#include "loadfile.h"
#include "error.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
const GLsizei uni_name_size=16;
namespace gameShader{
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
}
namespace bufferShader{
    static const unsigned int NUM_SHADERS=2;
    GLuint program;
    GLuint shaders[NUM_SHADERS];
    GLuint cameraMat_pos;
}

int initGameShader();
int initBufferShader();

void deleteGameShader();
void deleteBufferShader();
enum SHADER_TYPE{VERTEX_SHADER,FRAGMENT_SHADER};
void createShaderT(std::vector<std::string> file_names,render_target &target){
    std::vector<GLuint> shaders;
    target.program=glCreateProgram();
    for(int i =0;i<file_names.size();i++){
        std::string shader_text=loadFile(file_names[i]);
        GLuint temp_shader;
        if(i==VERTEX_SHADER){
            temp_shader=createShader(shader_text,GL_VERTEX_SHADER);
        }else if(i==FRAGMENT_SHADER){
            temp_shader=createShader(shader_text,GL_FRAGMENT_SHADER);
        }
        glAttachShader(target.program,temp_shader);

        
    }

    glLinkProgram(target.program);

    glValidateProgram(gameShader::program);
    
    int status = checkShaderError(gameShader::program,GL_VALIDATE_STATUS,true,"program failed to validate");

    //getting attributes
    GLchar name[uni_name_size];
    GLint num_attrs=0;
    glGetProgramiv(target.program,GL_ACTIVE_ATTRIBUTES,&num_attrs);
    for(int i=0;i<num_attrs;i++){
        GLsizei name_length;//length of name
        GLint size;//size of variable
        GLenum type;//type of variable
        glGetActiveAttrib(target.program,(GLuint) i,uni_name_size,&name_length,&size,&type,name);
        struct attribute attr_temp;
        attr_temp.name = std::string(name,name_length);
        attr_temp.location=glGetAttribLocation(target.program,attr_temp.name.c_str());
        attr_temp.type=type;
        target.Attributes.push_back(attr_temp);
    }

    GLint num_unis=0;
    //getting uniforms
    glGetProgramiv(target.program,GL_ACTIVE_UNIFORMS,&num_unis);
    for(int i=0;i<num_unis;i++){
        GLsizei name_length;//length of name
        GLint size;//size of variable
        GLenum type;//type of variable
        glGetActiveUniform(target.program,(GLuint) i,uni_name_size,&name_length,&size,&type,name);
        struct uniform uni_temp;
        uni_temp.name = std::string(name,name_length);
        uni_temp.location=glGetUniformLocation(target.program,uni_temp.name.c_str());
        uni_temp.type=type;
        target.Unis.push_back(uni_temp);
    }
}
int shaderInit(){
    initBufferShader();
    return initGameShader();
}
int initGameShader(){
    std::string filename = "./shaders/shader";
    gameShader::program=glCreateProgram();
    glError = glGetError();
    std::string file = loadFile(filename + ".vs");
    gameShader::shaders[0] = createShader(file,GL_VERTEX_SHADER);
    file = loadFile(filename + ".fs");
    gameShader::shaders[1] = createShader(file,GL_FRAGMENT_SHADER);
    for(unsigned int i=0;i<gameShader::NUM_SHADERS;i++){
        glAttachShader(gameShader::program,gameShader::shaders[i]);
    }
    glBindAttribLocation(gameShader::program,0,"position");
    glBindAttribLocation(gameShader::program,1,"texcoord");
    glLinkProgram(gameShader::program);
    int status;
    status = checkShaderError(gameShader::program,GL_LINK_STATUS,true,"Error: Program failed to link");
    if(status!=0)
        return status;

    glValidateProgram(gameShader::program);
    status = checkShaderError(gameShader::program,GL_VALIDATE_STATUS,true,"program failed to validate");
    if(status!=0)
        return status;
    deleteGameShader();
    glError=glGetError();  
    //setting uniforms
    gameShader::camera_uni_pos =  glGetUniformLocation(gameShader::program,"camera");
    gameShader::translate_uni_pos =  glGetUniformLocation(gameShader::program,"translate");
    gameShader::look_uni_pos =  glGetUniformLocation(gameShader::program,"look");
    gameShader::image_uni_pos = glGetUniformLocation(gameShader::program,"diffuse");
    gameShader::ambient_c_pos = glGetUniformLocation(gameShader::program,"ambient_color");
    gameShader::ambient_i_pos = glGetUniformLocation(gameShader::program,"ambient_intensity");
    gameShader::sun_intensity_pos = glGetUniformLocation(gameShader::program,"sun_intensity");
    gameShader::sun_pos_pos = glGetUniformLocation(gameShader::program,"sun_pos");
    gameShader::sun_c_pos = glGetUniformLocation(gameShader::program,"sun_color");

    glError=glGetError();
    printf("camera_uni_pos = %i\n",gameShader::camera_uni_pos);
    printf("translate_uni_pos = %i\n",gameShader::translate_uni_pos);
    printf("look_uni_pos = %i\n",gameShader::look_uni_pos);
    printf("program:%i\n",gameShader::shaders[0]);
}
int initBufferShader(){
    std::string filename = "./shaders/buffer_shader";
    bufferShader::program=glCreateProgram();
    glError = glGetError();
    std::string file = loadFile(filename + ".vs");
    bufferShader::shaders[0] = createShader(file,GL_VERTEX_SHADER);
    file = loadFile(filename + ".fs");
    bufferShader::shaders[1] = createShader(file,GL_FRAGMENT_SHADER);
    for(unsigned int i=0;i<bufferShader::NUM_SHADERS;i++){
        glAttachShader(bufferShader::program,bufferShader::shaders[i]);
    }
    glBindAttribLocation(bufferShader::program,0,"position");
    glBindAttribLocation(bufferShader::program,1,"texcoord");
    glLinkProgram(bufferShader::program);
    int status;
    status = checkShaderError(bufferShader::program,GL_LINK_STATUS,true,"Error: Program failed to link");
    if(status!=0)
        return status;

    glValidateProgram(bufferShader::program);
    status = checkShaderError(bufferShader::program,GL_VALIDATE_STATUS,true,"program failed to validate");
    if(status!=0)
        return status;
    deleteBufferShader();
    glError=glGetError();  
    //setting uniforms
    bufferShader::cameraMat_pos=glGetUniformLocation(bufferShader::program,"camera");

    glError=glGetError();
    printf("program:%i\n",gameShader::shaders[0]);
}
void useGameShader(){
    glUseProgram(gameShader::program);
}
void useBufferShader(){
    glUseProgram(bufferShader::program);
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
    glUniformMatrix4fv(gameShader::camera_uni_pos,1,GL_FALSE,glm::value_ptr(cam));
}
void sendTranslate(glm::mat4 trans){
    //finding uniform in shaderinit()
    glUniformMatrix4fv(gameShader::translate_uni_pos,1,GL_FALSE,glm::value_ptr(trans));
}

void sendLook(glm::mat4 look){
    //finding uniform in shaderinit()
    glUniformMatrix4fv(gameShader::look_uni_pos,1,GL_FALSE,glm::value_ptr(look));
}
void sendAmbient(glm::vec3 color,GLfloat intensity,glm::vec3 sun_pos,GLfloat sun_intensity,glm::vec3 sun_color){
    glUniform3f(gameShader::ambient_c_pos,color.x,color.y,color.z);
    glUniform1f(gameShader::ambient_i_pos,intensity);

    glUniform1f(gameShader::sun_intensity_pos,sun_intensity);
    glUniform3f(gameShader::sun_pos_pos,sun_pos.x,sun_pos.y,sun_pos.z);
    glUniform3f(gameShader::sun_c_pos,sun_color.x,sun_color.y,sun_color.z);
}
void sendCamMatBuffer(glm::mat4 in){
    glUniformMatrix4fv(bufferShader::cameraMat_pos,1,GL_FALSE,glm::value_ptr(in));
}
void setTexture(int unit){
    //printf("unit = %i\n",unit);
    //glUniform1i(gameShader::image_uni_pos,unit);
    glError = glGetError();
    if(glError!=0){
        printf("error %i\n",glError);
    }
}
void deleteBufferShader(){
    for(unsigned int i=0;i<bufferShader::NUM_SHADERS;i++){
        glDetachShader(bufferShader::program,bufferShader::shaders[i]);
        glDeleteShader(bufferShader::shaders[i]);
    }
     glUseProgram(bufferShader::program);
}
void deleteGameShader(){
    for(unsigned int i=0;i<gameShader::NUM_SHADERS;i++){
        glDetachShader(gameShader::program,gameShader::shaders[i]);
        glDeleteShader(gameShader::shaders[i]);
    }
     glUseProgram(gameShader::program);
}