#version 460

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;
out vec2 texcoord0;
uniform mat4 translate;
uniform mat4 camera;
uniform mat4 move;
uniform mat4 look;

void main(){
    gl_Position=camera*look*translate*vec4(position,1.0);
    //gl_Position= camera * vec4(position,1.0);
    //gl_Position=vec4(position,1.0);
    texcoord0=texcoord;

}