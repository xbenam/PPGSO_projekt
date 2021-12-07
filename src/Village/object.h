#pragma once
#include <memory>
#include <list>
#include <map>

#include <glm/glm.hpp>

// Forward declare a scene
class Scene;

class Object {
public:
    // Define default constructors as this is an abstract class
    Object() = default;
    Object(const Object&) = default;
    Object(Object&&) = default;
    virtual ~Object() {};

    virtual bool update(Scene &scene, float dt) = 0;

    virtual void render(Scene &scene) = 0;

    virtual void onClick(Scene &scene) {};

    // Object properties
    glm::vec3 position{0,0,0};
    glm::vec3 rotation{0,0,0};
    glm::vec3 scale{1,1,1};
    glm::mat4 modelMatrix{1};

protected:
    void generateModelMatrix();
};
