#include "camera_out.h"
#include <glm/glm.hpp>
Camera::Camera(glm::vec3 pos,float thetax, float thetay){
    this->position=pos;
    this->thetax=thetax;
    this->thetay=thetay;
}
void Camera::setPos(glm::vec3 pos_in){
    this->position=pos_in;
}
glm::vec3 Camera::getPos(){
    return this->position;
}
void Camera::moveCam(float deltax,float deltay){
    this->thetax+=deltax;
    this->thetay+=deltay;
}
void Camera::sendToRender(){
    sendCameraPos(this->position);
    sendCameraLook(this->thetax,this->thetay);
}