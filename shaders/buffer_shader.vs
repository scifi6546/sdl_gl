#version 130

in vec3 position;
in vec2 texcoord;
in vec3 aNormal;
out vec2 texcoord0;
out vec3 Normal;
out vec3 Pos;
uniform mat4 camera;

void main(){
    gl_Position=camera*translate*vec4(position,1.0);
    Pos = position;
    texcoord0=texcoord;
    Normal=aNormal;

}
