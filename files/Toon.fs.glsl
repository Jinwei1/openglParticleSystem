#version 330 core

struct Texture
{
    sampler2D diffuse;
};

in vec2 text_pos;
out vec4 fcolor;
in vec3 fP;
in vec3 ONormal;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor;
uniform Texture material;
void main(){


vec3 normal = normalize(ONormal);
vec3 lightDir = normalize(lightPosition - fP);
float diff = max(dot(normal,lightDir),0.0);
vec3 toonDiff;
if(diff>0.8)        toonDiff = vec3(1.0,1.0,1.0);
else if(diff>0.6)   toonDiff = vec3(0.8,0.8,0.8);
else if(diff>0.4)   toonDiff = vec3(0.6,0.6,0.6);
else if(diff>0.2)   toonDiff = vec3(0.4,0.4,0.4);
else                toonDiff = vec3(0.2,0.2,0.2);
//vec4 fcolor3 = vec4(toonDiff,1.0f)*texture(texture_diffuse,color);
vec3 textureColor = toonDiff * vec3(texture(material.diffuse,text_pos));
fcolor = vec4(textureColor,1.0f);
}

