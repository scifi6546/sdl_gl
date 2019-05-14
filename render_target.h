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
    std::string name;
    GLuint location;
};
//render target struct
struct render_target{
    FBO bufer_object;
    GLuint program;
    std::vector<uniform> Unis;

};


#endif