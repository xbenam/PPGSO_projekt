#include <glm/glm.hpp>
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "camera.h"


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI/180.0f) * fow;
    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

glm::vec3 Camera::bezierPoint(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3, const glm::vec3 &p4, const glm::vec3 &p5, float time) {
    glm::vec3 p01 = lerp(p0, p1, time);
    glm::vec3 p12 = lerp(p1, p2, time);
    glm::vec3 p23 = lerp(p2, p3, time);
    glm::vec3 p34 = lerp(p3, p4, time);
    glm::vec3 p45 = lerp(p4, p5, time);

    glm::vec3 p0112 = lerp(p01, p12, time);
    glm::vec3 p1223 = lerp(p12, p23, time);
    glm::vec3 p2334 = lerp(p23, p34, time);
    glm::vec3 p3445 = lerp(p34, p45, time);

    glm::vec3 p01121223 = lerp(p0112, p1223, time);
    glm::vec3 p12232334 = lerp(p1223, p2334, time);
    glm::vec3 p23343445 = lerp(p2334, p3445, time);

    glm::vec3 p0112122312232334 = lerp(p01121223, p12232334, time);
    glm::vec3 p1223233423343445 = lerp(p12232334, p23343445, time);

    glm::vec3 p01121223122323341223233423343445 = lerp(p0112122312232334, p1223233423343445, time);
    return p01121223122323341223233423343445;
}

glm::vec3 Camera::cameraInterpolation(float time, std::vector<glm::vec3> vertecies) {
    glm::vec3 actualPosition = bezierPoint(vertecies[0], vertecies[1], vertecies[2], vertecies[3],
                                           vertecies[4], vertecies[5], time);
    return actualPosition;
}

void Camera::update(float dt) {
    time += dt;

    if(time/30 <= 1.0f)
        position = cameraInterpolation((time/30), verticesOfMovement);
    else
        cameraAroundVillage = false;

    if(cameraAroundMill) {
        wasSet = false;
        cameraAroundVillage = true; // musí byť, aby sa nesplnila podmienka vo village pri generovaní koňa
        timeMillCamera += dt;
        if(timeMillCamera <= 30)
            position = cameraInterpolation((timeMillCamera/30), verticesOfMillCamera);
        else {
            wasSet = true;
            cameraAroundVillage = false;
            cameraAroundMill = false;
        }

    }

    viewMatrix = lookAt(position, orientation, up);
}
