#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

class Camera {
  private:
    float radius;
    float theta;
    float phi;
    glm::vec3 o;
    glm::vec3 eye;
    glm::vec3 up;
    
    void compute();
    
  public:
    Camera();
    void zoom(float factor);
    void turn(float phi, float theta);
    void pan(float x, float y);
};

#endif
