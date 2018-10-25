#include "game_engine.h"
int main(){
    printf("hello world!\n");
    /*
    Display disp = Display(800,600,"game");
    
   
    Vertex verticies[] ={
        Vertex(glm::vec3(-.5f,-.5f,5.0f),glm::vec2(0,0)),
        Vertex(glm::vec3(0,.5,5.0f),glm::vec2(0.5,1.0)),
        Vertex(glm::vec3(.5,-.5,5.0f),glm::vec2(1.0,0))
    };
    unsigned int indices[] = {0,1,2};
    Mesh mesh(verticies,sizeof(verticies)/sizeof(verticies[0]),
            indices,3);
    glm::vec3 cam = glm::vec3(0.0,0.0,0.0);
    Shader shader("./shaders/shader",cam);
    

    
    std::string temp = "./textures/grass.png";
    Texture texture(temp);
    while(!disp.isClosed()){
        disp.clear(0.0f,0.1f,0.4f,1.0f);
        shader.bind();
        //texture.bind(0);
        mesh.draw();
        disp.update();
        
    }
    */
    init();
    return 0;
}
//
