#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <GL/glew.h>
class Vertex{
    public:
        Vertex(glm::vec3 pos_in, glm::vec2 incorrd);
        glm::vec3 pos;
        glm::vec2 texcoord;
    private:
        
};
class Mesh{
    public:
        Mesh(Vertex* verticies, unsigned int numverticies,unsigned int * indices, int numincdicies);
        ~Mesh();
        void draw();
        void set_camerapos();
    private:
        enum {
            POSITION_VB,
            TEXTCOORD_VB,
            INDEX_VB,
            NUM_BUFFERS
        };
        GLuint vertexarrayObject;
        GLuint vertexarraybuffers[NUM_BUFFERS];
        unsigned int drawcount;
        glm::vec3 camera_pos;
        GLint camera_pos_unoform_loc;
};
#endif