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
#include "game_const.h"
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
glm::vec3 player_pos;
int init(){
    float dist = 10.0f;
    player_pos=glm::vec3(0,0,0);
    initDisplay(display_width,display_height,"temp_title");

    

    shaderInit();
    initCam(60.0,display_width,display_height,.01,500);

    std::vector<std::string> textures;
    textures.push_back("./textures/total.png");
    genTexture(textures);
    clearDisplay(0.0,.1,.6,1.0);
    temp_trans = glm::vec3(0.0f,0.0f,0.0f);
    //temp_mesh.push_back(Mesh_OBJ(0,glm::vec3(1.0f,0.0f,0.0f)));
    //Chunk temp_chunk = Chunk(glm::vec3(-10,-10,-10));
    World world = World();
    sendAmbient(ambient_color,ambient_intensity,sun_pos,sun_intensity,
    sun_color);
    glError = glGetError();
    //drawMeshCopies(cube_pos);

    // game loop
    while(!isclosed()){
        event();
        translateCam(player_pos);
        glError = glGetError();
        clearDisplay(0.0,.1,.6,1.0);
         glError = glGetError();
        bindTexture(0);
        glError = glGetError();
        world.tick(player_pos);
        glError = glGetError();
        world.draw();
        //temp_chunk.draw();
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
    temp_trans.x=0;
    temp_trans.y=0;
    temp_trans.z=0;
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
    }
    //temp_trans.x*SDL_GetTicks()/1000;
    player_pos+=temp_trans;
}
void engineMouseEvent(int x_rel, int y_rel){
    rotate_cam(y_rel*mouse_move_speed,x_rel*mouse_move_speed);
}
