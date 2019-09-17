#include "gui_element.h"
GuiElement::GuiElement(Text textureIn,glm::vec2 pos_on_screen,float z_depth,float size){
    this->texture_to_use=textureIn;
    //setting size so that only one scale factor is needed
    //and aspect ratio is preserved
    float x_size = (float) textureIn.width;
    x_size/=textureIn.height;
    x_size*=size;
    float y_size=size;
    
    _box=glm::vec2(x_size,y_size);
    _boxCenter=pos_on_screen;
   _boxToMesh(z_depth);
}
void GuiElement::draw(){
    drawMeshGui(this->render_model);
}
GuiElement::~GuiElement(){
    deleteMeshP(this->render_model);

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
    render_model = genMesh(temp,texture_to_use,glm::vec3(_boxCenter.x,_boxCenter.y,0.0f));
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