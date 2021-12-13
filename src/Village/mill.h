#pragma once

#include <iostream>
#include <vector>
#include <ppgso/ppgso.h>

#include "object.h"
#include "blades.h"


class Mill : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> meshMillBase;
    static std::unique_ptr<ppgso::Texture> textureBase;
    static std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<Blades> blades;

public:
    Mill();

    bool update(Scene &scene, float time) override;

    void render(Scene &scene) override;
};

