#version 130
uniform sampler2D diffuse;
in vec2 texcoord0;
out vec4 color;
uniform mat4 camera;
//out vec4 color;
void main(){
    //gl_FragColor=vec3(1.0,1.0,1.0);
    color=texture(diffuse,texcoord0);
    //gl_FragColor=texture2D(diffuse,vec2(.2,.3));
    //gl_FragColor=texture(diffuse,texcoord0);
}