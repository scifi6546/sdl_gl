#include "mesh.h"
#include <vector>
Vertex::Vertex(glm::vec3 pos_in,glm::vec2 incorrd){
    this->pos=pos_in;
    this->texcoord=incorrd;
}

Mesh::Mesh(Vertex* verticies, unsigned int numverticies, 
        unsigned int * indices, int numincdicies){
    drawcount=numincdicies;
    glGenVertexArrays(1,&vertexarrayObject);
    glBindVertexArray(vertexarrayObject);
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> tex_coord;

    positions.reserve(numverticies);
    tex_coord.reserve(numverticies);

    for(unsigned int i =0; i<numverticies;i++){
        positions.push_back(verticies[i].pos);
        tex_coord.push_back(verticies[i].texcoord);
    }

    glGenBuffers(NUM_BUFFERS,vertexarraybuffers);
    glBindBuffer(GL_ARRAY_BUFFER,vertexarraybuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER,numverticies*sizeof(positions[0]),
            &positions[0],GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

    glBindBuffer(GL_ARRAY_BUFFER,vertexarraybuffers[TEXTCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER,numverticies*sizeof(tex_coord[0]),
            &tex_coord[0],GL_STATIC_DRAW);


    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vertexarraybuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,numincdicies*sizeof(indices[0]),
            &indices[0],GL_STATIC_DRAW);


    glBindVertexArray(0);
}
void Mesh::draw(){
    glBindVertexArray(vertexarrayObject);
    glDrawArrays(GL_TRIANGLES,0,drawcount);
    //glDrawElements();
    glDrawElements(GL_TRIANGLES,drawcount,GL_UNSIGNED_INT,0);
}
Mesh::~Mesh(){
    glDeleteVertexArrays(1,&vertexarrayObject);
}