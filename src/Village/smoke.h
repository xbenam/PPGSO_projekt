#pragma once

#include <iostream>
#include <ppgso/ppgso.h>

#include "object.h"


class Smoke : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Texture> texture;
    static std::unique_ptr<ppgso::Shader> shader;
    glm::vec3 speed;

public:
    Smoke();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
    float age = 0;
};
