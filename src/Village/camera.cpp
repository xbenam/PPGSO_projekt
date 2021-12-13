#include <glm/glm.hpp>
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "camera.h"


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI/180.0f) * fow;

    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

void Camera::update() {
    viewMatrix = lookAt(position, position - orientation, up);
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

    float rotX = 20.0f * (float) (curY - 512) / 512;
    float rotY = 20.0f * (float) (curX - 512) / 512;

    glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

    if(!(glm::angle(newOrientation, up) <= glm::radians(5.0f) or glm::angle(newOrientation, -up) > glm::radians(5.0f))){
        orientation = newOrientation;
    }

    orientation = glm::rotate(orientation, glm::radians(-rotY), up);
}