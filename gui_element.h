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
		GuiElement() {

		}
        GuiElement(Text textureIn,glm::vec2 pos_on_screen,float z_depth,
            float size);
		GuiElement(Text textureIn, glm::vec2 pos_on_screen, float z_depth,
			glm::vec2 size);
        GUI_ACTION tick(eventPacket e);
        void draw();
		void resize(glm::vec2 size);
        ~GuiElement();
		float getZDepth();
		void setZDepth(float z_depth);
    private:
        //vector contains width and height of box
		float _zDepth;
        glm::vec2 _box;
        void _boxToMesh(float z_depth);
        bool _mouseInBox(eventPacket e);
        glm::vec2 _boxCenter;
        Text _textureUsed;
        Mesh _renderModel;

};
//draws a bar on screen
//------------------
//| GREEN    |Grey |
//------------------
class Bar {
	public:
		Bar(Text green_bar, Text grey_bar,glm::vec2 pos_on_screen, float z_depth, float size);
		void setPercent(float percent);
		void draw();
	private:
		glm::vec2 _aspectRatio = glm::vec2(1.0f, 1.0f);
		float _greenOffset=0.1f;//how much grey is below green
		float _zDepth;
		GuiElement _greenBar;
		GuiElement _greyBar;

};
#endif