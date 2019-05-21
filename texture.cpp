#include "texture.h"
#include <string>
#include "shader.h"
#include <GL/glew.h>
#include "stb_image.h"
#include <assert.h>
#include "error.h"
#include <vector>
#include "render_target.h"
GLuint *texture;
int num_textures;
void genTexture(std::vector<std::string> filename)
{
    glError = glGetError();
    num_textures = filename.size();
    printf("num_textures = %i\n", num_textures);
    int width, height, numcomponents;
    // /printf("texture_new: %i \n",temp_texture);
    texture = (GLuint *)calloc(filename.size(), sizeof(GLuint));
    glGenTextures(num_textures,&texture[0]);
    /*
    for (int i = 0; i < num_textures; i++)
    {
        glGenTextures(1, &texture[i]);
        printf("texture[%i] = %i\n", i, texture[i]);
    }*/
    for (int i = 0; i < num_textures; i++)
    {
        unsigned char *imagedata = stbi_load(filename[i].c_str(), &width,
                                             &height, &numcomponents, 4);
        if (imagedata == NULL)
        {
            printf("can not find texture %s", filename[i].c_str());
        }

        glBindTexture(GL_TEXTURE_2D, texture[i]);
        glError = glGetError();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, imagedata);
        glError = glGetError();
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        stbi_image_free(imagedata);
       glError= glGetError();
        if (glError != 0)
        {
            printf("glError %i\n", glError);
        }
    }
}
Texture genTexture(std::string filename){
    Texture out;
    glError = glGetError();
    printf("num_textures = %i\n", num_textures);
    int width, height, numcomponents;
    // /printf("texture_new: %i \n",temp_texture);
    texture = (GLuint *)calloc(1, sizeof(GLuint));
    glGenTextures(1,&out.color_texture);
    /*
    for (int i = 0; i < num_textures; i++)
    {
        glGenTextures(1, &texture[i]);
        printf("texture[%i] = %i\n", i, texture[i]);
    }*/
    
    unsigned char *imagedata = stbi_load(filename.c_str(), &width,
                                         &height, &numcomponents, 4);
    if (imagedata == NULL)
    {
        printf("can not find texture %s", filename.c_str());
    }
    glBindTexture(GL_TEXTURE_2D, out.color_texture);
    glError = glGetError();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, imagedata);
    glError = glGetError();
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    stbi_image_free(imagedata);
    glError= glGetError();
    if (glError != 0)
    {
        printf("glError %i\n", glError);
    }

    return out;
    
}
void delTexture()
{
    for (int i = 0; i < num_textures; i++)
    {
        glDeleteTextures(1, &texture[i]);
    }
}
void bindTexture(unsigned int unit)
{
    //printf("unit = %i",unit);
    //assert(unit >= 0 && unit <= 31);
    glActiveTexture(GL_TEXTURE0);
    glError= glGetError();
    glBindTexture(GL_TEXTURE_2D, unit);
    glError= glGetError();
    setTexture(unit);
    glError= glGetError();
    if (glError != 0)
    {
        printf("glError %i\n", glError);
    }
}
void bindTexture(const unsigned int texture,
    const render_target buffer,
    const std::string image_sampler_name){
        GLuint location = glGetUniformLocation(buffer.program,
            image_sampler_name.c_str());
        glActiveTexture(GL_TEXTURE0+location);

        //binds texture
        glBindTexture(GL_TEXTURE_2D,texture);
        glError = glGetError();
    }