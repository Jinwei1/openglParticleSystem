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

void myKeyCallback( GLFWwindow *window);
const GLint WIDTH = 800, HEIGHT = 600;

const GLchar *vertexShaderSource = "#version 330 core   \n\
in vec3 position;                                           \n\
in vec4    vColor;                                                 \n\
out vec4 color;  \n\
uniform mat4 transform; \n\
void main(){                                                \n\
gl_Position = transform*vec4(position.x,position.y,position.z,1.0);   \n\
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
    
    glViewport(0, 0, screenWidth, screenHeight);
    
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
    
    GLfloat vertices[] ={
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f
    };
    
    GLfloat colors[] =
    {
        1.0f,0.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f
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
    
   
    
    
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        myKeyCallback(window);
        
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 transform;
        transform = glm::translate(transform , glm::vec3(translateX,translateY,translateZ));
        if(rotateX||rotateY||rotateZ){
            transform = glm::rotate(transform, rotateAngle, glm::vec3(rotateX,rotateY,rotateZ));
        }
        transform = glm::scale(transform, glm::vec3(scaleXYZ+scaleX,scaleXYZ,scaleXYZ));
        
        GLint transformLocation = glGetUniformLocation(shaderProgram,"transform");
        glUniformMatrix4fv(transformLocation,1,GL_FALSE,glm::value_ptr(transform));
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glm::mat4 transform2;
        transform2 = glm::translate(transform2 , glm::vec3(translateX2,translateY2,0.0f));
        
        glUniformMatrix4fv(transformLocation,1,GL_FALSE,glm::value_ptr(transform2));
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
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
