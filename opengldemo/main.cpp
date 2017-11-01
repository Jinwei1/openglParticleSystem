// Jinwei Yuan 17306137
// yuanj@tcd.ie
// some codes are based on https://www.youtube.com/watch?v=aJRrgka4dpU&t=7s and openGL, GLFW & GLM official documents and tutorials
// modified and coded by Jinwei

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <iostream>
#include "maths_funcs.h"

void myKeyCallback( GLFWwindow *window);
const GLint WIDTH = 800, HEIGHT = 600;

const GLchar *vertexShaderSource = "#version 330 core   \n\
in vec3 position;                                           \n\
in vec4    vColor;                                                 \n\
out vec4 color;  \n\
uniform mat4 model; \n\
uniform mat4 view; \n\
uniform mat4 project; \n\
void main(){                                                \n\
gl_Position = project*view*model*vec4(position.x,position.y,position.z,1.0);   \n\
color = vColor;  \n\
}";

const GLchar *fragmentShaderSource = "#version 330 core\n\
in vec4 color; \n\
out vec4 fcolor; \n\
void main(){    \n\
fcolor =color;    \n\
}";

GLfloat translateX = 0.0f;
GLfloat translateY = 0.0f;
GLfloat translateZ = 0.0f;
GLfloat rotateX = 0.0f;
GLfloat rotateY = 0.0f;
GLfloat rotateZ = 0.0f;
GLfloat rotateAngle = 0.0f;
GLfloat scaleXYZ = 1.0f;
GLfloat scaleX = 0.0f;


GLfloat translateX2 = 0.0f;
GLfloat translateY2 = 0.0f;

void ortho();

int main(void){
    
    // Init glfw and use modern opengl in mac
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    
    
    GLFWwindow *window;
    
    window = glfwCreateWindow(WIDTH,HEIGHT,"Hello TRIANGLE", NULL,NULL);
    
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
    
    
    
    GLint success;
    GLchar infoLog[512];
    
    // vertexShader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
    std::cout<<"Error::SHADER::vertex::compliation_failed\n"<<infoLog<<std::endl;
    }

    // fragmentShader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    
    if(!success){
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
    std::cout<<"Error::SHADER::fragment::compliation_failed\n"<<infoLog<<std::endl;
    }
    
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        std::cout<<"Error::SHADER::program::compliation_failed\n"<<infoLog<<std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
   //
    GLfloat vertices[] = {
        -0.3f, -0.3f, -0.3f,
        0.3f, -0.3f, -0.3f,
        0.3f,  0.3f, -0.3f,
        0.3f,  0.3f, -0.3f,
        -0.3f,  0.3f, -0.3f,
        -0.3f, -0.3f, -0.3f,
        
        -0.3f, -0.3f,  0.3f,
        0.3f, -0.3f,  0.3f,
        0.3f,  0.3f,  0.3f,
        0.3f,  0.3f,  0.3f,
        -0.3f,  0.3f,  0.3f,
        -0.3f, -0.3f,  0.3f,
        
        -0.3f,  0.3f,  0.3f,
        -0.3f,  0.3f, -0.3f,
        -0.3f, -0.3f, -0.3f,
        -0.3f, -0.3f, -0.3f,
        -0.3f, -0.3f,  0.3f,
        -0.3f,  0.3f,  0.3f,
        
        0.3f,  0.3f,  0.3f,
        0.3f,  0.3f, -0.3f,
        0.3f, -0.3f, -0.3f,
        0.3f, -0.3f, -0.3f,
        0.3f, -0.3f,  0.3f,
        0.3f,  0.3f,  0.3f,
        
        -0.3f, -0.3f, -0.3f,
        0.3f, -0.3f, -0.3f,
        0.3f, -0.3f,  0.3f,
        0.3f, -0.3f,  0.3f,
        -0.3f, -0.3f,  0.3f,
        -0.3f, -0.3f, -0.3f,
        
        -0.3f,  0.3f, -0.3f,
        0.3f,  0.3f, -0.3f,
        0.3f,  0.3f,  0.3f,
        0.3f,  0.3f,  0.3f,
        -0.3f,  0.3f,  0.3f,
        -0.3f,  0.3f, -0.3f
    };
    GLfloat colors[] =
    {
        1.0f,0.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,1.0f,
        
        0.0f,1.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,1.0f,
        
        0.0f,0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f,
        
        0.0f,0.0f,0.0f,1.0f,
        0.0f,0.0f,0.0f,1.0f,
        0.0f,0.0f,0.0f,1.0f,
        0.0f,0.0f,0.0f,1.0f,
        0.0f,0.0f,0.0f,1.0f,
        0.0f,0.0f,0.0f,1.0f,
        
        1.0f,1.0f,0.0f,1.0f,
        1.0f,1.0f,0.0f,1.0f,
        1.0f,1.0f,0.0f,1.0f,
        1.0f,1.0f,0.0f,1.0f,
        1.0f,1.0f,0.0f,1.0f,
        1.0f,1.0f,0.0f,1.0f,
        
        1.0f,0.0f,1.0f,1.0f,
        1.0f,0.0f,1.0f,1.0f,
        1.0f,0.0f,1.0f,1.0f,
        1.0f,0.0f,1.0f,1.0f,
        1.0f,0.0f,1.0f,1.0f,
        1.0f,0.0f,1.0f,1.0f
    };
    
   
    
    GLuint VBO,VAO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices)+sizeof(colors),vertices,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
    glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertices),sizeof(colors),colors);
    
    GLint positionID = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(positionID,3,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
    glEnableVertexAttribArray(positionID);
    GLuint colorID = glGetAttribLocation(shaderProgram, "vColor");
    glVertexAttribPointer(colorID,4,GL_FLOAT,GL_FALSE,0,(GLvoid*)sizeof(vertices));
    glEnableVertexAttribArray(colorID);
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        myKeyCallback(window);
        
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
//        //Declare your uniform variables that will be used in your shader
        GLint matrix_location = glGetUniformLocation (shaderProgram, "model");
        GLint view_mat_location = glGetUniformLocation (shaderProgram, "view");
        GLint proj_mat_location = glGetUniformLocation (shaderProgram, "project");
//
//        //Here is where the code for the viewport lab will go, to get you started I have drawn a t-pot in the bottom left
//        //The model transform rotates the object by 45 degrees, the view transform sets the camera at -40 on the z-axis, and the perspective projection is setup using Antons method
//
        glm::mat4 transform;
        transform = glm::translate(transform , glm::vec3(translateX,translateY,translateZ));
        if(rotateX||rotateY||rotateZ){
            transform = glm::rotate(transform, rotateAngle, glm::vec3(rotateX,rotateY,rotateZ));
        }
        transform = glm::scale(transform, glm::vec3(scaleXYZ+scaleX,scaleXYZ,scaleXYZ));
        
        // bottom-left
        glViewport (0, 0, screenWidth/ 2, screenHeight/ 2);
        
        glm::mat4 view = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
        glm::mat4 persp_proj = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        glm::mat4 model = transform;
        
        glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, glm::value_ptr(persp_proj));
        glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // top-left
        glViewport (0, screenHeight/2, screenWidth/ 2, screenHeight/ 2);
        view = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0.5,0,0), glm::vec3(0,1,0));
        persp_proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 100.0f);
        model = glm::mat4();

        glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, glm::value_ptr(persp_proj));
        glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // bottom-right
        glViewport (screenWidth/2, 0, screenWidth/ 2, screenHeight/ 2);
        view = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0,2,0), glm::vec3(0,1,0));
        persp_proj = glm::perspective(glm::radians(70.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        model = transform;
        
        glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, glm::value_ptr(persp_proj));
        glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // top-right
        glViewport (screenWidth/2, screenHeight/2, screenWidth/ 2, screenHeight/ 2);
        
        view = glm::lookAt(glm::vec3(-3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
        persp_proj = glm::perspective(glm::radians(45.0f), (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        model = transform;
        
        glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, glm::value_ptr(persp_proj));
        glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv (matrix_location, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

//        glm::mat4 transform;
//        transform = glm::translate(transform , glm::vec3(translateX,translateY,translateZ));
//        if(rotateX||rotateY||rotateZ){
//            transform = glm::rotate(transform, rotateAngle, glm::vec3(rotateX,rotateY,rotateZ));
//        }
//        transform = glm::scale(transform, glm::vec3(scaleXYZ+scaleX,scaleXYZ,scaleXYZ));
//
//        GLint transformLocation = glGetUniformLocation(shaderProgram,"model");
//        glUniformMatrix4fv(transformLocation,1,GL_FALSE,glm::value_ptr(transform));
        
        
       
        

//        glm::mat4 transform2;
//        transform2 = glm::translate(transform2 , glm::vec3(translateX2,translateY2,0.0f));
//
//        glUniformMatrix4fv(transformLocation,1,GL_FALSE,glm::value_ptr(transform2));
//
//        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glfwTerminate();
    return 0;
}

void myKeyCallback( GLFWwindow *window)
{
    // translate , WSAD,QE
    if(glfwGetKey(window, GLFW_KEY_W)){
        translateY +=0.005f;
    }
    if(glfwGetKey(window, GLFW_KEY_S)){
        translateY -=0.005f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_D)){
        translateX +=0.005f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_A)){
        translateX -=0.005f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_Q)){
        translateZ +=0.005f;
    }
    if(glfwGetKey(window, GLFW_KEY_E)){
        translateZ -=0.005f;
    }
    
    // rotate, IKJL,UO
    if(glfwGetKey(window, GLFW_KEY_I)){
        rotateX = 1.0f;
        rotateAngle += 0.01f*glm::pi<GLfloat>();
    }
    if(glfwGetKey(window, GLFW_KEY_K)){
        rotateX = -1.0f;
        rotateAngle -= 0.01f*glm::pi<GLfloat>();
    }
    if(glfwGetKey(window, GLFW_KEY_J)){
        rotateY = -1.0f;
        rotateAngle -= 0.01f*glm::pi<GLfloat>();
    }
    if(glfwGetKey(window, GLFW_KEY_L)){
        rotateY = 1.0f;
        rotateAngle += 0.01f*glm::pi<GLfloat>();
    }
    if(glfwGetKey(window, GLFW_KEY_U)){
        rotateZ = -1.0f;
        rotateAngle -= 0.01f*glm::pi<GLfloat>();
    }
    if(glfwGetKey(window, GLFW_KEY_O)){
        rotateZ = 1.0f;
        rotateAngle += 0.01f*glm::pi<GLfloat>();
    }
    
    //  scale, TG in uniform, FH in X direction, non-uniform
    if(glfwGetKey(window, GLFW_KEY_T)){
        scaleXYZ += 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_G)){
        if(scaleXYZ>=0.02f)
            scaleXYZ -= 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_F)){
        if(scaleXYZ+scaleX>=0.02f)
            scaleX -= 0.01f;
    }
    if(glfwGetKey(window, GLFW_KEY_H)){
        scaleX += 0.01f;
    }
    
    // translate for second triangle on the right side, UP/DOWN/LEFT/RIGHT
    if(glfwGetKey(window, GLFW_KEY_UP)){
        translateY2 +=0.005f;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN)){
        translateY2 -=0.005f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_LEFT)){
        translateX2 -=0.005f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_RIGHT)){
        translateX2 +=0.005f;
    }
    
}
