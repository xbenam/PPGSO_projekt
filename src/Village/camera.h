#pragma once
#include <memory>

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>

class Camera {
public:

    glm::vec3 position = glm::vec3{0.0f,0.0f,0.0f};
    glm::vec3 orientation = glm::vec3{0.0f,0.0f,-1.0f};
    glm::vec3 up = glm::vec3{0.0f,1.0f,0.0f};

    float speed = 0.25f;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    Camera(float fow = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 100.0f);

    void update();

    void Inputs(int key);

    void MouseRotation(double curX, double curY);

    glm::vec3 cast(double u, double v);
};
