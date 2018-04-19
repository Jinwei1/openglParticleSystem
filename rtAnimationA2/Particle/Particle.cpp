//
//  Particle.cpp
//  CinderProject
//
//  Created by J Yuan on 5/2/18.
//

#include "Particle.hpp"

Particle::Particle(){
//    this->position = position;
//    this->radius = radius;
//    this->mass  = mass;
//    this->drag  = drag;
//    this->vel = glm::vec2(0.0f);
//    // initialize forces
//    this->forces = glm::vec2(0.0f);
//    this->forces.y = 9.8f * mass;
//    this->prePosition = position;
//    this->time_old = 0.00f;
    
}
Particle::Particle(const glm::vec3&position, float radius,float mass, std::vector<glm::vec3> forces){
    this->position = position;
    this->radius = radius;
    this->mass  = mass;
    this->drag  = drag;
    this->vel = glm::vec3(0.0f);
    // initialize forces
    this->forces = forces;
    this->forces.push_back(glm::vec3(0.0f,-9.8f*mass,0.0f));  // add gravity to it
    
    this->prePosition = position;
    this->time_old = 0.00f;
    
}

glm::vec3 Particle::update(){
    glm::vec3 nForce = glm::vec3(0.0f);
    
    // particle velosity
    float currentGameTime = float(glfwGetTime());
    float time_delta =  float( currentGameTime- time_old);
    if(time_delta<0.00125f){
//        printf("(%f,%f)\n",position.x,position.y );
        return position;
    }
    

    // sum up forces get nForce
    std::for_each(forces.begin(), forces.end(), [&] (glm::vec3 f){
        nForce += f;
    });
//    printf("%f\n",nForce.y);
    if(planeDetect()==true){
        glm::vec3 normal = glm::vec3(0.0f,1.0f,0.0f);


        nForce+= -0.7f*glm::dot(nForce,normal) * normal;
        // vel = vel_tangential - k*vel_normal_direction
//        vel = glm::vec3(vel.x,0.0f,vel.z) - 0.80000f*glm::vec3(0.0f,vel.y,vel.z);
        vel = -0.0f*vel;

    }
//    if(collisionDetectRight()==true){
//        glm::vec3 normal = glm::vec3(-1.0f,0.0f,0.0f);
//
//
//        nForce+= -0.7f*glm::dot(nForce,normal) * normal;
//        // vel = vel_tangential - k*vel_normal_direction
//        vel = glm::vec3(0.0f,vel.y,vel.z) - 0.80000f*glm::vec3(vel.x,0.0f,vel.z);
////        vel = -0.7f*vel;
//
//    }
    vel += time_delta*(nForce /mass);
    
    //  update position Pos += vel + a
    
   
    
    position += time_delta*vel ;
//    printf("(%f,%f)\n",position.x,position.y );
//    printf("%f\n",currentGameTime);
    
    // update old position

   
    time_old = currentGameTime;
    //nForce = glm::vec3(0.0);
    return position;
}

void Particle::draw(){
    //ci::gl::drawSolidCircle(position, radius);
    
}

bool Particle::planeDetect(){
    // collision plane detect
    glm::vec3 pointCollisionPlane =  glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 normalCollisionPlane = glm::vec3(0.0f,1.0f,0.0f);
    float nf = glm::dot(position-pointCollisionPlane, normalCollisionPlane);
    //printf("%f\n",nf );
    if(nf<-0.000000f){
        
        return true;
    }
    return false;
}


bool Particle::collisionDetectLeft(){
    // collision plane detect
    glm::vec3 pointCollisionPlane =  glm::vec3(-108.0f,0.0f,0.0f);
    glm::vec3 normalCollisionPlane = glm::vec3(1.0f,0.0f,0.0f);
    float nf = glm::dot(position-pointCollisionPlane, normalCollisionPlane);
    
    if(nf<0.00000f){
        //printf("%f\n",nf );
        return true;
    }
    return false;
}

bool Particle::collisionDetectRight(){
    // collision plane detect
    glm::vec3 pointCollisionPlane =  glm::vec3(108.0f,0.0f,0.0f);
    glm::vec3 normalCollisionPlane = glm::vec3(-1.0f,0.0f,0.0f);
    float nf = glm::dot(position-pointCollisionPlane, normalCollisionPlane);
    
    if(nf<0.00000f){
        //printf("%f\n",nf );
        return true;
    }
    return false;
}
