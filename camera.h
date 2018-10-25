#ifndef camera_H
#define camera_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
void initCam(GLfloat fov,GLfloat width, GLfloat height, GLfloat near, GLfloat far);
void rotate_cam(float x_rot, float y_rot);
void translateCam(glm::vec3 trans);
#endif