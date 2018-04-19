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
    int blinn=1;

    float ambientStrenth = 0.2f;
    vec3 ambient = ambientStrenth*lightColor;

    vec3 normal = normalize(ONormal);
    vec3 lightDir = normalize(lightPosition - fP);
    float k_diff = max(dot(normal,lightDir),0.0); // N dot L,  K diffuse
    vec3 diffuse = k_diff * lightColor;

    float k_spec =0.0f; // K_specular
    vec3 viewDir = normalize(viewPosition - fP);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    // Schlick's approximation for Fresnel factor
    float n1 = 1.0f; // indices of refraction of air
    float n2 = 0.8f; // indices of refraction of second media, n2
    float r0 = pow((n1-n2)/(n1+n2),2);
    float fresnel = r0 + (1.0-r0)*pow(1.0-max(dot(halfwayDir,viewDir),0.0),5);
    // Beckmann distribution
    float N_H = max(dot(normal,halfwayDir),0.0); // N dot H
    float roughness = 0.01f; // roughness for material, eg plastic=0.01, stainless steel = 0.03
    float mBYm = roughness * roughness;
    // Beckmann distribution
    float beckmannD =exp((N_H*N_H-1.0)/(mBYm*N_H*N_H))/(3.14159*mBYm*pow(N_H,4));
    
    // Geometric attenuation term, shadowing due to microfacets
    float V_H = max(dot(viewDir,halfwayDir),0.0); // V dot H
    float V_N = max(dot(viewDir,normal),0.0); // V dot N
    float L_N = k_diff;
    float g1 = 2.0*N_H*V_N/V_H;
    float g2 = 2.0*N_H*L_N/V_H;
    float geometric = min(1.0,min(g1,g2));
    // K specular
    k_spec = beckmannD*fresnel*geometric/max(4.0* V_N*L_N,0.00001);
  
    vec3 specular =  k_spec * lightColor;   //
    
    vec3 textureColor = (ambient+diffuse + specular) * vec3(texture(material.diffuse,text_pos));
    fcolor = vec4(textureColor , 1.0f);
}

