//
//  Shader.h
//  rtRenderingA1
//
//  Created by J Yuan on 24/1/18.
//  Copyright © 2018 J Yuan. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{

public:
    GLuint shaderProgram;
    // Constructor creates shaderProgram
    Shader( const GLchar *vertexPath, const GLchar *fragmentPath )
    {
        // 1. Retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensures ifstream objects can throw exceptions:
        vShaderFile.exceptions ( std::ifstream::badbit );
        fShaderFile.exceptions ( std::ifstream::badbit );
        try
        {
          
            // Open files
            vShaderFile.open( vertexPath );
            fShaderFile.open( fragmentPath );
            if(vShaderFile.fail())
                std::cout<<"File failed to open"<<std::endl;
            std::stringstream vShaderStream, fShaderStream;
            // Read buffer into streams
            vShaderStream << vShaderFile.rdbuf( );
            fShaderStream << fShaderFile.rdbuf( );
            
            // close file
            vShaderFile.close( );
            fShaderFile.close( );
            // Convert stream into string
            vertexCode = vShaderStream.str( );
            fragmentCode = fShaderStream.str( );
            
           
        }
        catch ( std::ifstream::failure e )
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar *vShaderSource = vertexCode.c_str( );
        const GLchar *fShaderSource = fragmentCode.c_str( );
        // 2. Compile shaders
        GLint success;
        GLchar infoLog[512];
        // vertexShader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader,1,&vShaderSource,NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
        if(!success){
            glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
            std::cout<<"Error::SHADER::vertex::compliation_failed\n"<<infoLog<<std::endl;
        }
        // fragmentShader
        GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
        glShaderSource( fragmentShader, 1, &fShaderSource, NULL );
        glCompileShader( fragmentShader );
        glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
        if ( !success )
        {
            glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
            std::cout << "Error::SHADER::fragment::compliation_failed\n" << infoLog << std::endl;
        }
        // create Shader Program and attach v and f shaders to it
        this->shaderProgram = glCreateProgram( );
        glAttachShader( this->shaderProgram, vertexShader );
        glAttachShader( this->shaderProgram, fragmentShader );
        
        glLinkProgram( this->shaderProgram );
        
        glGetProgramiv( this->shaderProgram, GL_LINK_STATUS, &success );
        if (!success)
        {
            glGetProgramInfoLog( this->shaderProgram, 512, NULL, infoLog );
            std::cout << "Error::SHADER::shaderProgram::compliation_failed\n" << infoLog << std::endl;
        }
        // deleted the linked shaders
        glDeleteShader( vertexShader );
        glDeleteShader( fragmentShader );
        
    }
    // Uses the current shader program
    void UseProgram( )
    {
        glUseProgram( this->shaderProgram );
    }
};


#endif /* Shader_h */
