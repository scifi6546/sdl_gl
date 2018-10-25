#ifndef Texture_h
#define Texture_h
#include <string>
#include <GL/glew.h>
#include <vector>
void genTexture(std::vector<std::string> filename);
void bindTexture(unsigned int unit);
void delTexture();

#endif