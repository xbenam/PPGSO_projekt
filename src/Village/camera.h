#pragma once
#include <memory>

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>

class Camera {
public:
    glm::vec3 up{0,1,0};
    glm::vec3 position{0,0,0};
    glm::vec3 back{0,0,-1};

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    Camera(float fow = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 10.0f);

    void update();

    glm::vec3 cast(double u, double v);
};
