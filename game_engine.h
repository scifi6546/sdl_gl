#ifndef game_engine_H
#define game_engine_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
int init();
void draw();
glm::vec3 engineKeyboardEvent(char key,bool is_down);
void engineMouseEvent(int x_rel, int y_rel);

#endif
