#version 460
uniform sampler2D diffuse;
uniform vec3 ambient_color;
uniform float ambient_intensity;
uniform vec3 sun_pos;
uniform float sun_intensity;
uniform vec3 sun_color;
in vec2 texcoord0;
in vec3 Normal;
in vec3 Pos;
out vec4 color;
uniform mat4 camera;
//out vec4 color;
void main(){
    vec3 lightDir = normalize(sun_pos-Pos);
    float diff = max(dot(Normal,lightDir),0.0);
    vec3 diffuse_light=diff*sun_color*sun_intensity;
    //gl_FragColor=vec3(1.0,1.0,1.0);
    
    vec3 color_light = ambient_color*ambient_intensity + diffuse_light;
    color=texture(diffuse,texcoord0)*vec4(color_light,1.0);
    vec3 temp = sun_color*Normal;
    //color=texture(diffuse,texcoord0)*vec4(temp,1.0);
    //gl_FragColor=texture2D(diffuse,vec2(.2,.3));
    //gl_FragColor=texture(diffuse,texcoord0);
}
