#include "game_engine.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "shader.h"
#include "display.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "event.h"
#include "block.h"
#include "error.h"
#include <unistd.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
glm::vec3 temp_trans;
float walk_speed = .1f;
SDL_Thread* input;
float mouse_move_speed = 0.005f;
std::vector<char> keys_pressed;
int display_height = 800;
int display_width = 1000;
int glError=0;
int init(){
    float dist = 10.0f;
    
    initDisplay(display_width,display_height,"temp_title");

    

    shaderInit();
    initCam(60.0,display_width,display_height,.01,500);\

    std::vector<std::string> textures;
    textures.push_back("./textures/grass.png");
    textures.push_back("./textures/rock.png");
    genTexture(textures);
    clearDisplay(0.0,.1,.6,1.0);
    temp_trans = glm::vec3(0.0f,0.0f,0.0f);
    //temp_mesh.push_back(Mesh_OBJ(0,glm::vec3(1.0f,0.0f,0.0f)));
    Chunk temp_chunk = Chunk();
    //drawMeshCopies(cube_pos);

    while(!isclosed()){
        event();
        translateCam(temp_trans);
        clearDisplay(0.0,.1,.6,1.0);
        bindTexture(0);
        temp_chunk.draw();
        updateDisplay();
        resetMouse(display_width,display_height);
        //temp_trans = glm::vec3(0.0f,0.0f,0.0f);
    }
    delDisplay();
    return 0;
}
void engineKeyboardEvent(char key,bool is_down){
    if(key==27){
        stopGame();
    }
    if(is_down){
        if(key=='w'){
            temp_trans.z=walk_speed;
            printf("w pressed\n");
        }
        if(key=='a')
            temp_trans.x=-walk_speed;
        if(key=='s')
            temp_trans.z=-walk_speed;
        if(key=='d')
            temp_trans.x=walk_speed;
        if(key==32){
            temp_trans.y=walk_speed;
        }
        
    }else{
        if(key=='w'){
            temp_trans.z=0;
            printf("w relesed");
        }if(key=='a')
            temp_trans.x = 0;
        if(key=='s')
            temp_trans.z=0;
        if(key=='d')
            temp_trans.x=0;
        if(key==32){
            temp_trans.y=0;
        }
        
    }
    temp_trans.x*SDL_GetTicks()/1000;
}
void engineMouseEvent(int x_rel, int y_rel){
    rotate_cam(y_rel*mouse_move_speed,x_rel*mouse_move_speed);
}
