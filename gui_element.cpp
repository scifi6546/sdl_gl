#include "gui_element.h"
GuiElement::GuiElement(Text textureIn,glm::vec2 pos_on_screen,float z_depth,float size){
    _textureUsed=textureIn;
	_zDepth = z_depth;
    //setting size so that only one scale factor is needed
    //and aspect ratio is preserved
    float x_size = (float) textureIn.width;
    x_size/=textureIn.height;
    x_size*=size;
    float y_size=size;
   
    _box=glm::vec2(x_size,y_size);
    _boxCenter=pos_on_screen;
   _boxToMesh(z_depth);
   //this[0] = GuiElement(textureIn, pos_on_screen, z_depth, glm::vec2(x_size, y_size));
}
GuiElement::GuiElement(Text textureIn, glm::vec2 pos_on_screen, float z_depth, glm::vec2 size) {
	_zDepth = z_depth;
	_textureUsed = textureIn;
	_box = size;
	_boxCenter = pos_on_screen;
	_boxToMesh(z_depth);
}
void GuiElement::draw(){
    drawMeshGui(_renderModel);
	printf("gui rendermodel id: %i\n", _renderModel.id);
}
void GuiElement::resize(glm::vec2 size){
	_boxToMesh(_zDepth);
}
GuiElement::~GuiElement(){
    deleteMeshP(_renderModel);

}
void GuiElement::_boxToMesh(float z_depth){
    Model temp = Model(
        {
            glm::vec3(-_box.x/2.0f,_box.y/2.0f,z_depth),
            glm::vec3(_box.x/2.0f,_box.y/2.0f,z_depth),
            glm::vec3(_box.x/2.0f,-_box.y/2.0f,z_depth),
            glm::vec3(-_box.x/2.0f,-_box.y/2.0f,z_depth),
        },
        {
            glm::vec2(0.0f,0.0f),
            glm::vec2(1.0f,0.0f),
            glm::vec2(1.0f,1.0f),
            glm::vec2(0.0f,1.0f),
        },
        {
            0,1,2,0,3,2
        },
        {
            glm::vec3(0.0f,0.0f,1.0f),
            glm::vec3(0.0f,0.0f,1.0f),
            glm::vec3(0.0f,0.0f,1.0f),
            glm::vec3(0.0f,0.0f,1.0f),
        }
            
    );
    _renderModel = genMesh(temp,_textureUsed,glm::vec3(_boxCenter.x,_boxCenter.y,0.0f));
}
float GuiElement::getZDepth() {
	return _zDepth;
}
void GuiElement::setZDepth(float z_depth) {
	_zDepth = z_depth;
}
bool GuiElement::_mouseInBox(eventPacket e){
    printf("boxCenter x: %f y: %f\n",_boxCenter.x,_boxCenter.y);
    if(e.mousePosScreen.x< (_boxCenter.x+_box.x/4.0f) &&
        e.mousePosScreen.x>(_boxCenter.x-_box.x/4.0f)&&
        e.mousePosScreen.y<(_boxCenter.y+_box.y/4.0f)&&
        e.mousePosScreen.y>(_boxCenter.y-_box.y/4.0f)
    ){
        printf("mouse in box\n");
        return true;
    }
    return false;
}
GUI_ACTION GuiElement::tick(eventPacket e){
    printf("x_size: %f y_size: %f\n",_box.x,_box.y);
    if(_mouseInBox(e)&&e.mouse==LEFT){
		printf("box clicked\n");
        return GUI_CLICKED;
    }
    return GUI_NONE;
}

Bar::Bar(Text green_bar, Text grey_bar, glm::vec2 pos_on_screen, float z_depth, float size) {
	glm::vec2 green_bar_size = size * _aspectRatio;
	printf("bar_size.x: %f bar_size.x: %f\n", green_bar_size.x, green_bar_size.y);
	_zDepth = z_depth;
	printf("constructing gui object!\n");
	_greenBar = GuiElement(genTextureP("./textures/button.png"), glm::vec2(0.5f, 0.5f), 0.7f, 0.1f);
	//GuiElement(green_bar, pos_on_screen, _zDepth + _greenOffset, green_bar_size);
	_greyBar = GuiElement(grey_bar, pos_on_screen, _zDepth,green_bar_size);
	printf("end consttciting gui object!\n");
}
void Bar::draw() {
	printf("bar drawn!\n");
	//_greyBar.setZDepth(_greyBar.getZDepth() + 0.01f);
	_greenBar.draw();
	_greyBar.draw();
}