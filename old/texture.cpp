#include "texture.h"
#include <string>
#include <GL/glew.h>
#include <png.h>
#include "stb_image.h"
#include <assert.h>
Texture::Texture(std::string filename){
    int width,height,numcomponents;
    unsigned char* imagedata= stbi_load(filename.c_str(),&width,
        &height,&numcomponents,4);
    if(imagedata==NULL){
        printf("can not find texture %s",filename.c_str());
    }
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

     glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,
        GL_UNSIGNED_BYTE,imagedata);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    stbi_image_free(imagedata);
}
Texture::~Texture(){
    glDeleteTextures(1,&texture);
}
void Texture::bind(unsigned int unit){
    assert(unit>=0 && unit<=31);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D,texture);
}