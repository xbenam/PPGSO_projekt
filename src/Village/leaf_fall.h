#pragma once

#include <iostream>
#include <ppgso/ppgso.h>

#include "object.h"
#include "leaf.h"

class Leaf_fall :public Object {
public:
    bool update(Scene &scene, float dt);

    void render(Scene &scene) override;

    float time = 0.0f;
};