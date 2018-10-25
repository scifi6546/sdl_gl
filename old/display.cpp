#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "display.h"
Display::Display(int width, int height,std::string title){
    printf("displayed");
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

    win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL);
    context=SDL_GL_CreateContext(win);
    //SDL_INIT(SDL_INIT_EVERYTHING);

    GLenum status = glewInit();
    if(status != GLEW_OK){
        printf("glew did not init");
    }
    closed=false;
}
void Display::update(){
    SDL_GL_SwapWindow(win);
    SDL_Event e;
    while(SDL_PollEvent(&e)!=0){
        if(e.type==SDL_KEYDOWN){
            key_down=e.key.keysym.sym;
            is_key_down=true;
        }else{
            key_down=' ';
            is_key_down=false;
        }
        if(e.type==SDL_QUIT){
            closed=true;
        }
    }

}
Display::~Display(){
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
bool Display::isClosed(){
    return closed;
}
void Display::clear(float r, float g, float b,float a){
    glClearColor(r,g,b,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
char Display::getKey(){
    if(is_key_down==true)
        return key_down;
    return NULL;
}