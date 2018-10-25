#ifndef Shader_H
#define Shader_H
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
std::string loadFile(std::string filedir);

class Shader{
    public:
        Shader(std::string filename,glm::vec3 cam_pos);
        void bind();
        ~Shader();
        GLuint createShader(std::string &text,GLenum shaderType);
        void checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string errorMessage);
        void update(glm::vec3 camera_pos);
    private:
    static const unsigned int NUM_SHADERS=2;
        GLuint program;
        GLuint shaders[NUM_SHADERS];

        glm::vec3 camera_pos;
        GLint camera_uni_pos;        
};
#endif