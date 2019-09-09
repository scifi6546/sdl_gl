#include <glm/glm.hpp>
#ifndef Event_H
#define Event_H
enum MOUSE_CICK{NONE,LEFT,MIDDLE,RIGHT};
struct eventPacket{
    glm::vec3 player_move;
    int mouseMx;//how much the mouse moved along the x axis
    int mouseMy;//how much the mouse moved along the y axis
    float thetaY;//the current player rotation
    float thetaX;//the current player rotation
    //pos from 0 to 1 on screen:
    //  (0,1)
    // /\ 
    // |
    // |
    // |
    // *------>(1,0)
    glm::vec2 mousePosScreen;
    MOUSE_CICK mouse;
};
eventPacket event();
//bool INT_closed;
void stopGame();
bool isclosed();
void resetMouse(int x,int y);
#endif