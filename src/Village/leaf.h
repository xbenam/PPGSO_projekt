#pragma once

#include <iostream>
#include <ppgso/ppgso.h>

#include "object.h"

class Leaf : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    glm::vec3 speed;

public:
    Leaf();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
    float age = 0;
};

