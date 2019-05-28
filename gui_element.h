#ifndef GUI_ELEMENT
#define GUI_ELEMENT
#include "render_public.h"
#include <glm/glm.hpp>
/*
An object that will be drawn on the screen
pos_on_screen is the screen choordinates of the model
z_depth is the depth of the object
Y-size and x_size is the size of the gui element on screen
a size of 1.0 takes up 1/2 of the screen
*/
class GuiElement{
    public:
        GuiElement(Text textureIn,glm::vec2 pos_on_screen,float z_depth,float x_size,float y_size);
        void draw();
        ~GuiElement();
    private:
        Text texture_to_use;
        Mesh render_model;

};
#endif