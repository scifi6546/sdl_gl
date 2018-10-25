#ifndef Texture_h
#define Texture_h
#include <string>
#include <GL/glew.h>
class Texture{
    public:
        Texture(std::string filename);
        void bind(unsigned int unit);
        ~Texture();
    private:
        GLuint texture;
};
#endif