//
// Created by Marti on 13. 12. 2021.
//
#include "scene.h"
#include "leaf_fall.h"

bool Leaf_fall::update(Scene &scene, float dt) {
    // Add object to scene when time reaches certain level
    time += dt;
    if (time > 500){
        auto obj = std::make_unique<Leaf>();
        obj->position = position;
        obj->position.x += glm::linearRand(-1.0f, 1.0f);
        obj->position.z += glm::linearRand(-1.0f, 1.0f);
        scene.objects.push_back(move(obj));
        time = 0;
    }
    return true;
}

void Leaf_fall::render(Scene &scene) {

}

