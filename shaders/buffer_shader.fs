#version 130
uniform sampler2D diffuse;
in vec2 texcoord0;
in vec3 Normal;
in vec3 Pos;
in float z_depth;
out vec4 color;
uniform mat4 camera;
//out vec4 color;
void main(){
    color=texture(diffuse,texcoord0);
   // color=texture(diffuse,texcoord0);
}
