#include "event.h"
#include "game_engine.h"
bool INT_closed;
SDL_Event e;
void event(){
    char key_down;
    INT_closed = false;
    
    int x_rel;
    int y_rel;
    while(SDL_PollEvent(&e)){
        if(e.type==SDL_KEYDOWN){
            printf("key down: %i\n",e.key.keysym.sym);
            //key_down=e.key.keysym.;
            key_down=e.key.keysym.sym;
            engineKeyboardEvent(key_down,true);
        }
        if(e.type==SDL_KEYUP){
            printf("key down: %i\n",e.key.keysym.sym);
            //key_down=e.key.keysym.;
            key_down=e.key.keysym.sym;
            engineKeyboardEvent(key_down,false);
        }
        if(e.type==SDL_QUIT){
            INT_closed=true;
            printf("closed\n");
            break;
        }
        if(e.type==SDL_MOUSEMOTION){
            x_rel = e.motion.xrel;
            y_rel=e.motion.yrel;
            printf("mouse_moved x_rel = %i y_rel = %i",x_rel,y_rel);
            engineMouseEvent(x_rel,y_rel);
        }
    }
}
bool isclosed(){
    return INT_closed;
}
void stopGame(){
    for(int i =0; i<10; i++){
        printf("********game stop***********\n");
    }
    INT_closed=true;
}
void resetMouse(int x, int y){
    SDL_WarpMouseInWindow(NULL,x/2,y/2);
    SDL_PeepEvents(&e,1,SDL_PEEKEVENT,SDL_FIRSTEVENT,SDL_LASTEVENT);
    if(e.type==SDL_MOUSEMOTION)
    SDL_PollEvent(&e);
}