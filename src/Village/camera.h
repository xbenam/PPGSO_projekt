#pragma once
#include <memory>

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>

class Camera {
public:
    std::vector<glm::vec3> verteciesOfMovement = {{0, 1, -48},
                                                  {0, 1, -25},
                                                  {-100, 20, 50},
                                                  {50, 15, 70},
                                                  {50, 10, 10},
                                                  {0, 1, -50}};
    glm::vec3 position = glm::vec3{0.0f,0.0f,0.0f};
    glm::vec3 orientation = glm::vec3{0.0f,0.0f,5.0f};
    glm::vec3 up = glm::vec3{0.0f,1.0f,0.0f};

    bool firstClick = true;
    float speed = 0.5f;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    float time = 0;
    bool cameraAroundVillage = true;
    bool wasSet = false;

    Camera(float fow = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 100.0f);

    glm::vec3 bezierPoint(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec3 &p4, const glm::vec3 &p5, float time);

    glm::vec3 cameraInterpolation(float time);

    void update(float time);

    void Inputs(int key);

    void MouseRotation(double curX, double curY);

    glm::vec3 cast(double u, double v);
};
