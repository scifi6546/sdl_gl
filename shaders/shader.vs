#version 460

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec3 aNormal;
out vec2 texcoord0;
out vec3 Normal;
out vec3 Pos;
uniform mat4 translate;
uniform mat4 camera;
uniform mat4 move;
uniform mat4 look;

void main(){
    gl_Position=camera*look*translate*vec4(position,1.0);
    //gl_Position= camera * vec4(position,1.0);
    //gl_Position=vec4(position,1.0);
    texcoord0=texcoord;
    Normal=aNormal;

}