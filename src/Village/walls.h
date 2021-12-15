#pragma once

#include <vector>
#include <ppgso/ppgso.h>
#include "object.h"


class Walls final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Texture> texture;
    static std::unique_ptr<ppgso::Shader> shader;
public:
    Walls();

    bool update(Scene &scene, float time) override;

    void render(Scene &scene) override;
};
