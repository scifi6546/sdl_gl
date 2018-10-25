#include <string>
#include <SDL2/SDL.h>
#ifndef Display_H
#define Display_H
class Display{
    public:
        Display(int width, int height,std::string title);
        ~Display();
        void update();
        bool isClosed();
        void clear(float r, float g, float b,float a);
        char getKey();
    private:
        SDL_Window *win;
        SDL_GLContext context;
        bool closed;
        char key_down;
        bool is_key_down;

};
#endif