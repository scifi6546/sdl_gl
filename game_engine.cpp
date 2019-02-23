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
#include "physics.h"
        
#include "render_manager.h"
#include <unistd.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
glm::vec3 temp_trans;
float walk_speed = 1.0f;
SDL_Thread* input;
float mouse_move_speed = 0.005f;
std::vector<char> keys_pressed;
int display_height = 800;
int display_width = 1000;
int glError=0;
glm::vec3 player_pos;
World *GameWorld;
int lastTime = 0;
int init(){
    float dist = 10.0f;
    player_pos=glm::vec3(0.1f,150.0f,0.1f);
    initDisplay(display_width,display_height,"temp_title");

    

    shaderInit();
    initCam(60.0,display_width,display_height,.01,500);

    std::vector<std::string> textures;
    textures.push_back("./textures/total.png");
    textures.push_back("./textures/water.png");
    genTexture(textures);
    clearDisplay(0.0,.1,.6,1.0);
    temp_trans = glm::vec3(0.0f,0.0f,0.0f);
    //temp_mesh.push_back(Mesh_OBJ(0,glm::vec3(1.0f,0.0f,0.0f)));
    //Chunk temp_chunk = Chunk(glm::vec3(-10,-10,-10));
    GameWorld = new World(player_pos);
    sendAmbient(ambient_color,ambient_intensity,sun_pos,sun_intensity,
    sun_color);
    glError = glGetError();
    //drawMeshCopies(cube_pos);

    // game loop
    lastTime=SDL_GetTicks();
    while(!isclosed()){
        glm::vec3 temp_move = event();
        int current_time = SDL_GetTicks();
        float deltaT = current_time - lastTime;
        deltaT/=1000.0f;
        if(current_time%40==0){
            printf("frame rate: %f FPS\n",1.0f/deltaT);
        }
        lastTime=current_time;

        player_pos = GameWorld->tick(temp_move,deltaT);

        GameWorld->setBlock(rand()/100,rand()/200,rand()/100,AIR);
        rManager::drawFrame();
    }
    delDisplay();
    return 0;
}
void draw(){
	
    translateCam(player_pos);
        glError = glGetError();
        clearDisplay(0.0,.1,.6,1.0);
         glError = glGetError();
        
        glError = glGetError();
       
        GameWorld->draw();
        updateDisplay();
        glError=glGetError();
        
        if(glError!=0){
            printf("Error %i\n",glError);
        }
        resetMouse(display_width,display_height);
        //temp_chunk.draw();
       
}
glm::vec3 engineKeyboardEvent(char key,bool is_down){
    glm::vec3 temp_trans=glm::vec3(0.0f,0.0f,0.0f);
    if(key==27){
        stopGame();
    }
    if(is_down){
        if(key=='w'){
            temp_trans.z=1.0f;
            //printf("w pressed\n");
        }
        if(key=='a')
            temp_trans.x=-1.0f;
        if(key=='s')
            temp_trans.z=-1.0f;
        if(key=='d')
            temp_trans.x=1.0f;
        if(key==32){
            temp_trans.y=1.0f;
        }
    }
    return temp_trans;
    //temp_trans.x*SDL_GetTicks()/1000;
}

void engineMouseEvent(int x_rel, int y_rel){
    rotate_cam(y_rel*mouse_move_speed,x_rel*mouse_move_speed);
}
