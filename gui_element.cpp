#include "gui_element.h"
GuiElement::GuiElement(Text textureIn,glm::vec2 pos_on_screen,float z_depth,float x_size,float y_size){
    this->texture_to_use=textureIn;
    Model temp = Model({glm::vec3(x_size,y_size,z_depth),glm::vec3(x_size,0.0f,z_depth),
     glm::vec3(0.0f,0.0f,z_depth),glm::vec3(0.0f,y_size,z_depth)},
    {glm::vec2(1.0f,1.0f),glm::vec2(1.0,0.0f),
        glm::vec2(0.0f,0.0f),glm::vec2(0.0f,1.0)},{0,1,3,1,2,3},
    {glm::vec3(1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,1.0f),
        glm::vec3(1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,1.0f)});
    this->render_model=genMesh(temp,this->texture_to_use,glm::vec3(pos_on_screen.x,pos_on_screen.y,z_depth));
}
void GuiElement::draw(){
    drawMeshGui(this->render_model);
}
GuiElement::~GuiElement(){
    deleteMeshP(this->render_model);

}