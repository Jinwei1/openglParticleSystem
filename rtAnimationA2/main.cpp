// Jinwei Yuan 17306137
// yuanj@tcd.ie
// 9 colorful cube system, opengl, glew, glfw, lgm
// Jinwei

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include<glm/gtc/random.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <iostream>
#include "mesh.h"
#include<glm/gtx/transform.hpp>
#include"Shader.h"
#include "Particle/Particle.hpp"
#include"model.h"


void myKeyCallback( GLFWwindow *window);
const GLint WIDTH = 1024, HEIGHT = 768;


GLfloat PixelMeterRatio = 0.105f;  // pixel meter ratio

GLfloat translateX = 0.0f;
GLfloat translateY = 0.0f;
GLfloat translateZ = 0.0f;
GLfloat yaw = 0.0f;
GLfloat pitch = 0.0f;
GLfloat roll = 0.0f;
GLfloat rotateAngle = 0.0f;
GLfloat scaleXYZ = 1.0f;
GLfloat scaleX = 0.0f;
glm::mat4 rotationMat = glm::rotate(0.0f,glm::vec3(1.0f,0.0f,0.0f));

GLfloat translateXfps = 0.0f;
GLfloat translateYfps = 0.0f;
GLfloat translateZfps = 0.0f;
GLfloat translateXfpsl = 0.0f;
GLfloat translateYfpsl = 0.0f;
GLfloat translateZfpsl = 0.0f;



GLfloat transformCube[8][7] = {
    -0.9,0.9,0.9,0.0,-1.0,0.0,0.0,
    0.9,0.9,0.9,0.0,-1.0,0.0,0.0,
    -0.9,-0.9,0.9,0.0,-1.0,0.0,0.0,
    0.9,-0.9,0.9,0.0,-1.0,0.0,0.0,
    -0.9,0.9,-0.9,0.0,-1.0,0.0,0.0,
    0.9,0.9,-0.9,0.0,-1.0,0.0,0.0,
    -0.9,-0.9,-0.9,0.0,-1.0,0.0,0.0,
    0.9,-0.9,-0.9,0.0,-1.0,0.0,0.0
};
GLfloat PI = glm::pi<GLfloat>();
glm::vec3 lightPosition(3.0f,4.0f,2.0f);

int main(void){
    // Init glfw and use modern opengl in mac
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    
    
    GLFWwindow *window;
    
    window = glfwCreateWindow(WIDTH,HEIGHT,"Jin's Magic Cube", NULL,NULL);
    
    int screenWidth,screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if(!window){
        std::cout<<"Failed to create window"<<std::endl;
        
        glfwTerminate();
        return -1;
    }
    // make the windows contet current
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if(GLEW_OK != glewInit()){
        std::cout<<"Failed to initialize GLEW"<<std::endl;
        return -1;
    }
    
    
  
    Shader phongShader("/Users/jyuan/Projects/RT Animation/rtAnimationA2/files/Phong.vs.glsl","/Users/jyuan/Projects/RT Animation/rtAnimationA2/files/Phong.fs.glsl");
   
    Model myModel("/Users/jyuan/Projects/RT Animation/rtAnimationA2/files/Eis.obj");
//     Model myModel("/Users/jyuan/Projects/RT Rendering/rtRenderingA2/files/models/nanosuit.obj");
//    Model myModel("/Users/jyuan/Projects/RT Animation/rtAnimationA2/files/army helicopter obj/army helicopter_obj.obj");
    float x,y=0.0f;
    float mass = 0.001f;  // snow
    std::vector<glm::vec3> forces; // forces , No Gravity here, as it will be added by default
    forces.push_back(glm::vec3(0.0001f,0.0f,0.0f));  // add a force
    forces.push_back(glm::vec3(0.0f,0.008f,0.0f));  // add a force
    
    Particle p=Particle(glm::vec3(0.0f,100.0f,0.0),10.0f,mass,forces);
//    Particle p2=Particle(glm::vec3(10.0f,100.0f,0.0),10.0f,mass,forces);
    Particle p_array[1000];
    for(int i=0; i<1000;i++){
        x = glm::linearRand(-100.0f, 100.0f);
        y = glm::linearRand(100.0f, 150.0f);
//        y = 100.0f;
        printf("(%f,%f)\n",x,y );
        p_array[i] = Particle(glm::vec3(x,y,0.0f),10.0f,mass,forces);
    }
  
    glEnable(GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    while(!glfwWindowShouldClose(window)){
        static int rotationCount=0;
        glfwPollEvents();
        myKeyCallback(window);
        
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        phongShader.UseProgram();
        
        
        
        glm::quat firstQuaternion;
        
        glm::mat4 transform;
        glm::mat4 translateMat = glm::translate(glm::vec3(translateX,translateY,translateZ));
        glm::mat4 rotationMat;
        if(yaw||pitch||roll){
            // convert local rotate angles to quaternion
            firstQuaternion = glm::quat(glm::vec3(pitch,yaw,roll));
            // convert quaternion to 4x4 rotation matrix
            rotationMat *= glm::toMat4(firstQuaternion);
            
        }
        glm::mat4 scaleMat = glm::scale(glm::vec3(scaleXYZ+scaleX,scaleXYZ,scaleXYZ));
        glm::mat4 scaleMat_PointOne = glm::scale(glm::vec3(0.1f));
        transform = translateMat*rotationMat*scaleMat*scaleMat_PointOne;
        
        // 1 top left view
        
        // glViewport (0, screenHeight/2, screenWidth/ 2, screenHeight/ 2);
        
        //Declare uniform variables that will be used in 1st shader
        GLint matrix_location = glGetUniformLocation (phongShader.shaderProgram, "model");
        GLint view_mat_location = glGetUniformLocation (phongShader.shaderProgram, "view");
        GLint proj_mat_location = glGetUniformLocation (phongShader.shaderProgram, "project");
        
        GLint light_color_location = glGetUniformLocation(phongShader.shaderProgram,"lightColor");
        GLint light_position_location = glGetUniformLocation(phongShader.shaderProgram,"lightPosition");
        GLint view_position_location = glGetUniformLocation(phongShader.shaderProgram,"viewPosition");
        // light it
        glUniform3f(light_color_location,1.0f,1.0f,1.0f);
        glUniform3f(light_position_location,lightPosition.x,lightPosition.y,lightPosition.z);
        glUniform3f(view_position_location,translateXfps,translateYfps,translateZfps+20);
        
      
        // fps view using wsad zxcv
//        glm::mat4 view = glm::translate(glm::mat4(),glm::vec3(translateXfps,translateYfps,-20.0f+translateZfps));
        glm::mat4 view = glm::lookAt(glm::vec3(translateXfps,translateYfps-0.1,translateZfps+20),glm::vec3(translateXfps,translateYfps,translateZfps+20)+ glm::vec3(translateXfpsl,translateYfpsl,-1.0f), glm::vec3(0,1,0));
        glm::mat4 persp_proj = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        glm::mat4 local1 = glm::mat4();
        
        local1 = transform;
        
        // for the root, we orient it in global space
        glm::mat4 global1 = local1;
        // update uniform & draw
        glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, glm::value_ptr(persp_proj));
        glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(global1));
        myModel.Draw(phongShader);
    
//        printf("%f\n",glm::linearRand(0.0f, 5.0f));
        
        
//        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::vec3(1.0,0.0,0.0))*global1));
//        myModel.Draw(phongShader);
//
//        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::vec3(-1.0,0.0,0.0))*global1));
//        myModel.Draw(phongShader);
//
//        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::vec3(0.0,1.0,0.0))*global1));
//        myModel.Draw(phongShader);
//
//        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::vec3(0.0,-1.0,0.0))*global1));
//        myModel.Draw(phongShader);
        
        for(int i=0; i<1000; i++){
            glm::vec3 position = p_array[i].update();
            glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(glm::translate(PixelMeterRatio*position)*global1));
            myModel.Draw(phongShader);

        }
        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(glm::translate(PixelMeterRatio*glm::vec3(p.update()))*global1));
        myModel.Draw(phongShader);
        
//        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(glm::translate(PixelMeterRatio*glm::vec3(p2.update()))*global1));
//        myModel.Draw(phongShader);
        
//        // for 2 in top left view
//        glViewport (screenWidth/2,screenHeight/ 2 , screenWidth/ 2, screenHeight/ 2);
//        toonShader.UseProgram();
//
//        //Declare uniform variables that will be used in 2nd shader
//        GLint matrix_location2 = glGetUniformLocation (toonShader.shaderProgram, "model");
//        GLint view_mat_location2 = glGetUniformLocation (toonShader.shaderProgram, "view");
//        GLint proj_mat_location2 = glGetUniformLocation (toonShader.shaderProgram, "project");
//
//        GLint light_color_location2 = glGetUniformLocation(toonShader.shaderProgram,"lightColor");
//        GLint light_position_location2 = glGetUniformLocation(toonShader.shaderProgram,"lightPosition");
//        GLint view_position_location2 = glGetUniformLocation(toonShader.shaderProgram,"viewPosition");
//        // light it
//        glUniform3f(light_color_location2,1.0f,1.0f,1.0f);
//        glUniform3f(light_position_location2,lightPosition.x,lightPosition.y,lightPosition.z);
//        glUniform3f(view_position_location2,translateXfps,translateYfps,translateZfps+20);
//
//
//        glm::mat4 global2 = glm::mat4();
//        global2 = transform;
//        // update uniform & draw
//        glUniformMatrix4fv (proj_mat_location2, 1, GL_FALSE, glm::value_ptr(persp_proj));
//        glUniformMatrix4fv (view_mat_location2, 1, GL_FALSE, glm::value_ptr(view));
//        glUniformMatrix4fv (matrix_location2, 1, GL_FALSE, glm::value_ptr(global2));
//        myModel.Draw(toonShader);
//
//
//         // for 3
//        glViewport (0, 0, screenWidth/2, screenHeight/ 2);
//        ctShader.UseProgram();
//
//        //Declare uniform variables that will be used in 3rd shader
//        GLint matrix_location3 = glGetUniformLocation (ctShader.shaderProgram, "model");
//        GLint view_mat_location3 = glGetUniformLocation (ctShader.shaderProgram, "view");
//        GLint proj_mat_location3 = glGetUniformLocation (ctShader.shaderProgram, "project");
//
//        GLint light_color_location3 = glGetUniformLocation(ctShader.shaderProgram,"lightColor");
//        GLint light_position_location3 = glGetUniformLocation(ctShader.shaderProgram,"lightPosition");
//        GLint view_position_location3 = glGetUniformLocation(ctShader.shaderProgram,"viewPosition");
//        // light it
//        glUniform3f(light_color_location3,1.0f,1.0f,1.0f);
//        glUniform3f(light_position_location3,lightPosition.x,lightPosition.y,lightPosition.z);
//        glUniform3f(view_position_location3,translateXfps,translateYfps,translateZfps+20);
//
//
//        glm::mat4 global3 = glm::mat4();
//        global3 = transform;
//        // update uniform & draw
//        glUniformMatrix4fv (proj_mat_location3, 1, GL_FALSE, glm::value_ptr(persp_proj));
//        glUniformMatrix4fv (view_mat_location3, 1, GL_FALSE, glm::value_ptr(view));
//        glUniformMatrix4fv (matrix_location3, 1, GL_FALSE, glm::value_ptr(global3));
//        myModel.Draw(ctShader);
        
        rotationCount++;
        glfwSwapBuffers(window);
        
    }
    //glDeleteVertexArrays(1,&VAO);
    //glDeleteBuffers(1,&VBO);
    glfwTerminate();
    return 0;
}



void myKeyCallback( GLFWwindow *window)
{
    // translate FPS view, WSAD,QE
    if(glfwGetKey(window, GLFW_KEY_S)){
        translateYfps +=0.05f;
    }
    if(glfwGetKey(window, GLFW_KEY_W)){
        translateYfps -=0.05f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_A)){
        translateXfps +=0.05f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_D)){
        translateXfps -=0.05f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_Q)){
        translateZfps +=0.05f;
    }
    if(glfwGetKey(window, GLFW_KEY_E)){
        translateZfps -=0.05f;
    }
    
    // translate FPS view, ZXCV
    if(glfwGetKey(window, GLFW_KEY_Z)){
        translateYfpsl +=0.05f;
    }
    if(glfwGetKey(window, GLFW_KEY_X)){
        translateYfpsl -=0.05f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_C)){
        translateXfpsl +=0.05f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_V)){
        translateXfpsl -=0.05f;
    }
    
  
    
    // rotate, IKJLUO
    if(glfwGetKey(window, GLFW_KEY_I)){
        //        rotateX = 1.0f;
        pitch -= 0.01f*glm::pi<GLfloat>();
        rotationMat = glm::rotate(pitch,glm::vec3(1.0f,0.0f,0.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_K)){
        //        rotateX = 1.0f;
        pitch += 0.01f*glm::pi<GLfloat>();
        rotationMat = glm::rotate(pitch,glm::vec3(1.0f,0.0f,0.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_J)){
        //        rotateY = 1.0f;
        yaw -= 0.01f*glm::pi<GLfloat>();
        rotationMat = glm::rotate(yaw,glm::vec3(0.0f,1.0f,0.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_L)){
        //        rotateY = 1.0f;
        yaw += 0.01f*glm::pi<GLfloat>();
        rotationMat = glm::rotate(yaw,glm::vec3(0.0f,1.0f,0.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_U)){
        //        rotateZ = 1.0f;
        roll -= 0.01f*glm::pi<GLfloat>();
        rotationMat = glm::rotate(roll,glm::vec3(0.0f,0.0f,1.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_O)){
        //        rotateZ = 1.0f;
        roll += 0.01f*glm::pi<GLfloat>();
        rotationMat = glm::rotate(roll,glm::vec3(0.0f,0.0f,1.0f));
    }
    
    //  scale, M/ in uniform, <> in X direction, non-uniform
    if(glfwGetKey(window, GLFW_KEY_M)){
        scaleXYZ += 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_SLASH)){
        if(scaleXYZ>=0.02f)
            scaleXYZ -= 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_BRACKET)){
        if(scaleXYZ+scaleX>=0.02f)
            scaleX -= 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET)){
        scaleX += 0.01f;
    }
    
    // play with the cube, transform it
    if(glfwGetKey(window, GLFW_KEY_UP)){
       
        for(int i=0; i < 8; i++){
            if(transformCube[i][0] == -0.9f && transformCube[i][1] == 0.9f && transformCube[i][2] == 0.9f){
               
                transformCube[i][0] *= -1.0f;
              
                transformCube[i][6] -= 0.05f*PI;
            }
            else if(transformCube[i][0] == 0.9f && transformCube[i][1] == 0.9f && transformCube[i][2] == 0.9f){
                
                transformCube[i][2] *= -1.0f;
                
                transformCube[i][6] -= 0.05f*PI;
            }
            else if(transformCube[i][0] == -0.9f && transformCube[i][1] == 0.9f && transformCube[i][2] == -0.9f){
                
                transformCube[i][2] *= -1.0f;
              
                transformCube[i][6] -= 0.05f*PI;
            }
            else if(transformCube[i][0] == 0.9f && transformCube[i][1] == 0.9f && transformCube[i][2] == -0.9f){
                
                transformCube[i][0] *=-1.0f;
              
                transformCube[i][6] -= 0.05f*PI;
            }
        }
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN)){
        for(int i=0; i < 8; i++){
            if(transformCube[i][0] == -0.9f && transformCube[i][1] == -0.9f && transformCube[i][2] == 0.9f){
                
                transformCube[i][0] *= -1.0f;
           
                transformCube[i][6] -= 0.05f*PI;
            }
            else if(transformCube[i][0] == 0.9f && transformCube[i][1] == -0.9f && transformCube[i][2] == 0.9f){
                
                transformCube[i][2] *= -1.0f;
            
                transformCube[i][6] -= 0.05f*PI;
            }
            else if(transformCube[i][0] == -0.9f && transformCube[i][1] == -0.9f && transformCube[i][2] == -0.9f){
                
                transformCube[i][2] *= -1.0f;
               
                transformCube[i][6] -= 0.05f*PI;
            }
            else if(transformCube[i][0] == 0.9f && transformCube[i][1] == -0.9f && transformCube[i][2] == -0.9f){
                
                transformCube[i][0] *=-1.0f;
               
                transformCube[i][6] -= 0.05f*PI;
            }
        }
        
    }
    
   
    
    
    
  
    
}
