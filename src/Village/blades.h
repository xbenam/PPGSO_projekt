#pragma once

#include <iostream>
#include <vector>
#include <ppgso/ppgso.h>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

#include "object.h"

class Blades : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> meshMillBlades;
    static std::unique_ptr<ppgso::Texture> textureBlades;
    static std::unique_ptr<ppgso::Shader> shader;
public:
    Blades(glm::vec3 base_position);

    bool update(Scene &scene) override;

    void render(Scene &scene) override;
};

