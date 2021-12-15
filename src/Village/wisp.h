#pragma once

#include <iostream>
#include <ppgso/ppgso.h>

#include "object.h"


class Wisp : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Texture> texture;
    static std::unique_ptr<ppgso::Shader> shader;
    glm::vec3 speed;
    float time;
    std::vector<glm::vec3> path = {{17, 2, -2},
                                   {12, 1, -2},
                                   {12, 3, 3},
                                   {17, 1, 3},
                                   {17, 1, 3},
                                   {17, 2, -2}};
public:

    Wisp();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;

    glm::vec3 bezierPoint(float t);
};
