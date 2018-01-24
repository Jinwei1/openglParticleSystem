#version 330 core
in vec3 color;
out vec4 fcolor;
in vec3 fP;
in vec3 ONormal;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor;
void main(){
int blinn=1;

float ambientStrenth = 0.05f;
vec3 ambient = ambientStrenth*lightColor;

vec3 normal = normalize(ONormal);
vec3 lightDir = normalize(lightPosition - fP);
float diff = max(dot(normal,lightDir),0.0);
vec3 diffuse = diff * lightColor;

float spRatio = 0.6f;
float specular =0.0f;
vec3 viewDir = normalize(viewPosition - fP);
if(blinn==1){
vec3 halfwayDir = normalize(lightDir + viewDir);
specular = pow(max(dot(normal, halfwayDir), 0.0), 32);
}
else{
vec3 refDir = reflect(-lightDir, normal);
specular = pow(max(dot(viewDir, refDir),0.0),32);
}
vec3 sp = spRatio * specular * lightColor;

vec3 fcolor3 = (ambient+diffuse + sp) * color;
fcolor = vec4(fcolor3 , 1.0f);
}

