#ifndef shader_H
#define shader_H
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>


int shaderInit(); 
int checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string errorMessage);
GLuint createShader(std::string &text,GLenum shaderType);
void bind();
void sendCamera(glm::mat4 cam);
void sendTranslate(glm::mat4 trans);
void sendLook(glm::mat4 look);
void setTexture(int unit);
#endif