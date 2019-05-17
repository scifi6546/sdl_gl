#ifndef Texture_h
#define Texture_h
#include <string>
#include <GL/glew.h>
#include <vector>
#include "render_target.h"
void genTexture(std::vector<std::string> filename);
void bindTexture(unsigned int unit);//decrepitated do not use!
/*
    NOT TESTED
    binds the texture  to the buffer
*/
void bindTexture(const unsigned int texture_unit,
    const render_target buffer,
    const std::string image_sampler_name);
void delTexture();

#endif