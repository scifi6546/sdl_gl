#ifndef RENDER_TARGET
#define RENDER_TARGET
#include <GL/glew.h>
#include <string>
#include <vector>
/*
    Struct that stores frame buffer object info
*/
struct FBO{
    unsigned int FBO_OJECT=0;
    unsigned int DEPTH_MAP=0;
    unsigned int COLOR_MAP=0;
};
struct uniform{
    std::string name="";//name of uniform
    GLuint location=0;//location of uniform
    GLenum type;//type of inuform (float vec3 etc)
};
struct attribute{
    std::string name="";//name of uniform
    GLuint location=0;//location of uniform
    GLenum type;//type of inuform (float vec3 etc)
};
struct Texture{
    GLuint color_texture;
    GLuint depth_texture;
};
//render target struct
struct render_target{
    FBO bufer_object;
    GLuint program;
    std::vector<uniform> Unis;
    std::vector<attribute> Attributes;


};


#endif