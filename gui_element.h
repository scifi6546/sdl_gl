#ifndef GUI_ELEMENT
#define GUI_ELEMENT
#include "render_public.h"
#include "event.h"
#include <glm/glm.hpp>
enum GUI_ACTION{GUI_NONE,GUI_CLICKED};
/*
An object that will be drawn on the screen
pos_on_screen is the screen choordinates of the model (center of item)
z_depth is the depth of the object
Y-size and x_size is the size of the gui element on screen
a size of 1.0 takes up 1/2 of the screen
*/
class GuiElement{
    public:
        GuiElement(Text textureIn,glm::vec2 pos_on_screen,float z_depth,
            float size);
        GUI_ACTION tick(eventPacket e);
        void draw();
        ~GuiElement();
    private:
        //vector contains width and height of box
        glm::vec2 _box;
        void _boxToMesh(float z_depth);
        bool _mouseInBox(eventPacket e);
        glm::vec2 _boxCenter;
        Text texture_to_use;
        Mesh render_model;

};
#endif