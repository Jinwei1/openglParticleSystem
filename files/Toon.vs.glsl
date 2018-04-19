
#version 330 core
layout (location =0) in vec3 position;
layout (location =1) in vec3 normal;
out vec3 ONormal;
out vec3 fP;
layout (location =2) in vec2 text_p;
out vec2 text_pos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 project;
void main(){
gl_Position = project*view*model*vec4(position,1.0);
text_pos = text_p;
fP = vec3(model*vec4(position,1.0f));
ONormal = mat3(transpose(inverse(model)))* normal;
}
