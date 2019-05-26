#include "game_engine.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "shader.h"
#include "display.h"
#include "mesh.h"
//#include "texture.h"
#include "camera.h"
#include "event.h"
#include "block.h"
#include "error.h"
#include "game_const.h"
#include "physics.h"
#include "entity.h"
#include "player.h"
#include "render_manager.h"
#include "camera_out.h"
#include <unistd.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
glm::vec3 temp_trans;
float walk_speed = 1.0f;
SDL_Thread* input;
float mouse_move_speed = 0.005f;
std::vector<char> keys_pressed;
glm::vec3 player_pos;
World *GameWorld;
int lastTime = 0;
Player player;
std::vector<Entity> entitys;

std::vector<Text> generated_textures;
Camera gameCam=Camera(glm::vec3(0.0,0.0,0.0),0.0,0.0);
int getHeight(){
    return display_height;
}
int getWidth(){
    return display_width;
}
int init(){
    initRender();
    float dist = 10.0f;
    player_pos=glm::vec3(0.1f,150.0f,0.1f);
    gameCam.setPos(player_pos);
    getError();
    std::vector<std::string> textures;
    generated_textures.push_back(genTextureP("./textures/total.png"));
    generated_textures.push_back(genTextureP("./textures/water.png"));
    genTextureP("./textures/water.png");
    //printf("hello world!\n");

    //genTexture(textures);
    getError();
    clearDisplay(0.0,.1,.6,1.0);
    temp_trans = glm::vec3(0.0f,0.0f,0.0f);
    //temp_mesh.push_back(Mesh_OBJ(0,glm::vec3(1.0f,0.0f,0.0f)));
    //Chunk temp_chunk = Chunk(glm::vec3(-10,-10,-10));
    GameWorld = new World(player_pos,generated_textures[0],generated_textures[1]);
    getError();
    //entitys.push_back(Entity(glm::vec3(2.1f,120.0f,0.1f),GameWorld,generated_textures[1]));
    //entitys.push_back(Entity(glm::vec3(3.1f,120.0f,0.1f),GameWorld,generated_textures[1]));
    //entitys.push_back(Entity(glm::vec3(6.1f,120.0f,0.1f),GameWorld,generated_textures[1]));
    //entitys.push_back(Entity(glm::vec3(-12.1f,120.0f,0.1f),GameWorld,generated_textures[1]));
    
    player = Player(player_pos,GameWorld);
    getError();
    printf("worked??\n");
    sendAmbientInfo(ambient_color,ambient_intensity,sun_pos,sun_intensity,
    sun_color);
    //error on this line
    //sendAmbient(ambient_color,ambient_intensity,sun_pos,sun_intensity,
    //sun_color);
    getError();
    //drawMeshCopies(cube_pos);

    // game loop
    lastTime=SDL_GetTicks();//glError right here ?? does not make any sense
    getError();
    while(!isclosed()){
        getError();
        eventPacket frameEvent=event();
        int current_time = SDL_GetTicks();
        float deltaT = current_time - lastTime;
        deltaT/=1000.0f;
        if(current_time%40==0){
            printf("frame rate: %f FPS\n",1.0f/deltaT);
        }
        lastTime=current_time;

        getError();
        player_pos=player.tick(deltaT,frameEvent);
        gameCam.setPos(player_pos);
        GameWorld->tick(frameEvent,deltaT,player_pos);
        for(int i =0;i<entitys.size();i++){
            entitys[i].tick(deltaT);
        }
        draw();
        drawRender();
        //GameWorld->setBlock(rand()/100,rand()/200,rand()/100,AIR);
        //drawFrame();
        getError();
    }
    delDisplay();
    return 0;
}
void draw(){
    gameCam.sendToRender();

    getError();
    
    for(int i =0;i<entitys.size();i++){
    entitys[i].draw();
    }
   
    GameWorld->draw();
    
    getError();
    
    //temp_chunk.draw();
       
}
void draw_temps(){
    for(int i =0;i<entitys.size();i++){
        entitys[i].draw();
    }
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
    gameCam.moveCam(x_rel*0.03f,y_rel*0.03f);
}
