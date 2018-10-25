#include "shader.h"
std::string loadFile(std::string filedir){

    FILE *filep;
    filep=fopen(filedir.c_str(),"r");
    std::string file = std::string();
    char temp_char;
    while(0==0){
        temp_char=fgetc(filep);
        if(temp_char==EOF){
            break;
        }else{
            file.push_back(temp_char);
        }
    }
    fclose(filep);
    return file;
}
GLuint Shader::createShader(std::string &text,GLenum shaderType){
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
Shader::Shader(std::string filename,glm::vec3 cam_pos){
    program=glCreateProgram();
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
    checkShaderError(program,GL_LINK_STATUS,true,"Error: Program failed to link");

    glValidateProgram(program);
    checkShaderError(program,GL_VALIDATE_STATUS,true,"program failed to validate");
}

Shader::~Shader(){

    glDeleteProgram(program);
}
void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string errorMessage){
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
    }
}
 void Shader::bind(){
    for(unsigned int i=0;i<NUM_SHADERS;i++){
        glDetachShader(program,shaders[i]);
        glDeleteShader(shaders[i]);
    }
     glUseProgram(program);
 }
void Shader::update(glm::vec3 camera_pos){
    printf("not there yet");
}