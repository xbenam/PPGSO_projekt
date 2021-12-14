#ifndef _PPGSO_SCENE_H
#define _PPGSO_SCENE_H

#include <memory>
#include <map>
#include <list>

#include "object.h"
#include "camera.h"

/*
 * Scene is an object that will aggregate all scene related data
 * Objects are stored in a list of objects
 * Keyboard and Mouse states are stored in a map and struct
 */
class Scene {
public:
    void update(float time);

    void render();

    std::vector<Object*> intersect(const glm::vec3 &position, const glm::vec3 &direction);

    // Camera object
    std::unique_ptr<Camera> camera;

    // All objects to be rendered in scene
    std::list< std::unique_ptr<Object> > objects;

    // Keyboard state
    std::map< int, int > keyboard;

    // Lights, in this case using only simple directional diffuse lighting
    glm::vec3 lightColor = {1,1,1};

    glm::vec3 dirLightDirection = {1,1,1};

    glm::vec3 dirLightDiff = {.7f,.7f,.7f};
    glm::vec3 dirLightAmb = {.45f,.45f,.45f};
    glm::vec3 dirLightSpec = {.2f,.2f,.2f};

    float lightConst = 3.0f;
    float lightLin = 0.01f;
    float lightQuad = 0.0032f;

    glm::vec3 LightPosition = {1,1,0};

    glm::vec3 LightDiff;
    glm::vec3 LightAmb;
    glm::vec3 LightSpec = {.5f,.5f,.5f};

    glm::vec3 Mat1Diff = {.75f,.37f,.6f};
    glm::vec3 Mat2Diff = {.85f,.5f,.7f};
    glm::vec3 Mat3Diff = {.9f,.8f,.9f};

    glm::vec3 Mat1Amb = {1,1,1};
    glm::vec3 Mat2Amb = {.75f,.75f,.75f};
    glm::vec3 Mat3Amb = {.6f,.6f,.6f};

    glm::vec3 Mat1Spec = {1,1,1};
    glm::vec3 Mat2Spec = {.8f,.8f,.8f};
    glm::vec3 Mat3Spec = {0,0,0};

    float Mat1Shiny = 32.f;
    float Mat2Shiny = 8.f;
    float Mat3Shiny = 1.f;

    static bool firstScene;

    static std::string usingTexture;

    // Store cursor state
    struct {
        double x, y;
        bool left, right;
    } cursor;
};

#endif // _PPGSO_SCENE_H
