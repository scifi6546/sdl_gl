#include "gui_element.h"
GuiElement::GuiElement(Text textureIn,glm::vec2 pos_on_screen,float z_depth,float x_size,float y_size){
    this->texture_to_use=textureIn;
    _box={glm::vec2(pos_on_screen.x-x_size/2.0f,pos_on_screen.y+y_size/2.0f),
        glm::vec2(pos_on_screen.x+x_size/2.0f,pos_on_screen.y-y_size/2.0f)};

    /*
    Model temp = Model({glm::vec3(x_size,y_size,z_depth),glm::vec3(x_size,0.0f,z_depth),
     glm::vec3(0.0f,0.0f,z_depth),glm::vec3(0.0f,y_size,z_depth)},
    {glm::vec2(1.0f,1.0f),glm::vec2(1.0,0.0f),
        glm::vec2(0.0f,0.0f),glm::vec2(0.0f,1.0)},{0,1,3,1,2,3},
    {glm::vec3(1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,1.0f),
        glm::vec3(1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,1.0f)});
    this->render_model=genMesh(temp,this->texture_to_use,glm::vec3(pos_on_screen.x,pos_on_screen.y,z_depth));
    */
   _boxToMesh(z_depth);
}
void GuiElement::draw(){
    drawMeshGui(this->render_model);
}
GuiElement::~GuiElement(){
    deleteMeshP(this->render_model);

}
void GuiElement::_boxToMesh(float z_depth){
    assert(_box.size()==2);
    Model temp = Model(
        {
            glm::vec3(_box[0].x,_box[0].y,z_depth),
            glm::vec3(_box[1].x,_box[0].y,z_depth),
            glm::vec3(_box[1].x,_box[1].y,z_depth),
            glm::vec3(_box[0].x,_box[1].y,z_depth),
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
    render_model = genMesh(temp,texture_to_use,glm::vec3(0.0f,0.0f,0.0f));
}
GUI_ACTION GuiElement::tick(eventPacket e){

}