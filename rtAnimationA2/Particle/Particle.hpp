//
//  Particle.hpp
//  CinderProject
//
//  Created by J Yuan on 5/2/18.
//

#pragma once

#include<glm/glm.hpp>
#include <stdio.h>
#include <chrono>
#include <GLFW/glfw3.h>
#include<glm/gtc/random.hpp>
#include<vector>

using namespace std::chrono;


class Particle {
    
public:
    Particle();
    Particle(const glm::vec3& position,
             float radius, float mass, std::vector<glm::vec3> forces);
    
    glm::vec3 update();
    void draw();
    
private:
    glm::vec3 position;
    glm::vec3 prePosition; // previous pos
    std::vector<glm::vec3> forces;
    glm::vec3 vel;
    
    float radius;
    float mass;
    float drag;
    milliseconds ms;
    double time_old;
    
    bool planeDetect();
    bool collisionDetectLeft();
    bool collisionDetectRight();
    
    
    
    
};
