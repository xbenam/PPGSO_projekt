#pragma once

#include <iostream>
#include <vector>
#include <ppgso/ppgso.h>

#include "object.h"

class Tree : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Texture> texture;
    static std::unique_ptr<ppgso::Shader> shader;
    float time = 0;
public:
    Tree();

    bool update(Scene &scene, float time) override;

    void render(Scene &scene) override;

    void generateLeafs(Scene &scene, float count);
};


