
#version 330 core
in vec3 position;
in vec3 normal;
out vec3 ONormal;
out vec3 fP;
in vec3 vColor;
out vec3 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 project;
void main(){
gl_Position = project*view*model*vec4(position,1.0);
color = vColor;
fP = vec3(model*vec4(position,1.0f));
ONormal = mat3(transpose(inverse(model)))* normal;
}
