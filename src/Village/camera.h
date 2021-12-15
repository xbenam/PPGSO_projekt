#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>

class Camera {
public:
    std::vector<glm::vec3> verticesOfMovement = {{0,    1,  -48},
                                                 {0,    1,  -25},
                                                 {-100, 20, 50},
                                                 {50,   15, 70},
                                                 {50,   10, 10},
                                                 {0,    1,  -50}};
    std::vector<glm::vec3> verticesOfMillCamera = {{10, 1,  8},
                                                   {40, 5,  30},
                                                   {23, 10, 1},
                                                   {5,  1,  -40},
                                                   {-2, 1,  15},
                                                   {28, 5,  15}};
    glm::vec3 position = glm::vec3{0.0f,0.0f,0.0f};
    glm::vec3 orientation = glm::vec3{0.0f,0.0f,5.0f};
    glm::vec3 up = glm::vec3{0.0f,1.0f,0.0f};

    float speed = 0.5f;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    float time = 0;
    bool cameraAroundVillage = true;
    bool wasSet = false;

    float timeMillCamera = 0;
    bool cameraAroundMill = false;

    Camera(float fow = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 100.0f);

    glm::vec3 bezierPoint(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec3 &p4, const glm::vec3 &p5, float time);

    glm::vec3 cameraInterpolation(float time, std::vector<glm::vec3> vertecies);

    void update(float time);

};