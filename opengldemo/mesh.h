//
//  mesh.h
//  opengldemo
//
//  Created by J Yuan on 12/11/17.
//  Copyright © 2017 J Yuan. All rights reserved.
//


    GLfloat cube[] = {
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

    GLfloat colorCube[] =
    {
        1.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,
        1.0f,0.0f,0.0f,
        
        0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,1.0f,0.0f,
        
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,
        
        0.0f,1.0f,1.0f,
        0.0f,1.0f,1.0f,
        0.0f,1.0f,1.0f,
        0.0f,1.0f,1.0f,
        0.0f,1.0f,1.0f,
        0.0f,1.0f,1.0f,
        
        1.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        1.0f,1.0f,0.0f,
        
        1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f
    };
// random RGB  as normal for the cube :::  R ,G ,B, -R ,-G ,-B
GLfloat normalCube[] =
{
    1.0f,0.0f,0.0f,
    1.0f,0.0f,0.0f,
    1.0f,0.0f,0.0f,
    1.0f,0.0f,0.0f,
    1.0f,0.0f,0.0f,
    1.0f,0.0f,0.0f,
    
    0.0f,1.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,1.0f,0.0f,
    
    0.0f,0.0f,1.0f,
    0.0f,0.0f,1.0f,
    0.0f,0.0f,1.0f,
    0.0f,0.0f,1.0f,
    0.0f,0.0f,1.0f,
    0.0f,0.0f,1.0f,
    
    -1.0f,0.0f,0.0f,
    -1.0f,0.0f,0.0f,
    -1.0f,0.0f,0.0f,
    -1.0f,0.0f,0.0f,
    -1.0f,0.0f,0.0f,
    -1.0f,0.0f,0.0f,
    
    0.0f,-1.0f,0.0f,
    0.0f,-1.0f,0.0f,
    0.0f,-1.0f,0.0f,
    0.0f,-1.0f,0.0f,
    0.0f,-1.0f,0.0f,
    0.0f,-1.0f,0.0f,
    
    0.0f,0.0f,-1.0f,
    0.0f,0.0f,-1.0f,
    0.0f,0.0f,-1.0f,
    0.0f,0.0f,-1.0f,
    0.0f,0.0f,-1.0f,
    0.0f,0.0f,-1.0f,
};
int cube_count=sizeof(cube)/sizeof(float);