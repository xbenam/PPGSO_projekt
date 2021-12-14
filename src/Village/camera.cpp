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

glm::vec3 Camera::cameraInterpolation(float time) {
    glm::vec3 actualPosition = bezierPoint(verteciesOfMovement[0], verteciesOfMovement[1], verteciesOfMovement[2], verteciesOfMovement[3],
                verteciesOfMovement[4], verteciesOfMovement[5], time);
    return actualPosition;
}

void Camera::update(float dt) {
    time += dt;
    if(time/30 <= 1.0f ) {
        position = cameraInterpolation((time/30));
        viewMatrix = lookAt(position, orientation, up);
    }
    else {
        viewMatrix = lookAt(position, position - orientation, up);
    }

}

glm::vec3 Camera::cast(double u, double v) {
    // Create point in Screen coordinates
    glm::vec4 screenPosition{u,v,0.0f,1.0f};

    // Use inverse matrices to get the point in world coordinates
    auto invProjection = glm::inverse(projectionMatrix);
    auto invView = glm::inverse(viewMatrix);

    // Compute position on the camera plane
    auto planePosition = invView * invProjection * screenPosition;
    planePosition /= planePosition.w;

    // Create direction vector
    auto direction = glm::normalize(planePosition - glm::vec4{position,1.0f});
    return glm::vec3{direction};
}

void Camera::Inputs(int key){
    if(key == GLFW_KEY_S){
        position += speed * orientation;
    }
    if(key == GLFW_KEY_W){
        position += speed * -orientation;
    }
    if(key == GLFW_KEY_A){
        position += speed * glm::normalize(glm::cross(orientation, up));
    }
    if(key == GLFW_KEY_D){
        position += speed * -glm::normalize(glm::cross(orientation, up));
    }
    if(key == GLFW_KEY_SPACE){
        position += speed * up;
    }
    if(key == GLFW_KEY_LEFT_CONTROL){
        position += speed * -up;
    }
    if(key == GLFW_KEY_E){
//        orientation = glm::rotate(orientation, glm::radians(-rotY), up);
        orientation.x += speed * 0.5;
    }
    if(key == GLFW_KEY_Q){
        orientation.x += speed * -0.5;
    }
}

void Camera::MouseRotation(double curX, double curY){

    float rotX = 15.0f * (float) (curY - 512) / 512;
    float rotY = 15.0f * (float) (curX - 512) / 512;

    glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

    if(!(glm::angle(newOrientation, up) <= glm::radians(5.0f) or glm::angle(newOrientation, -up) > glm::radians(5.0f))){
        orientation = newOrientation;
    }

    orientation = glm::rotate(orientation, glm::radians(-rotY), up);
}