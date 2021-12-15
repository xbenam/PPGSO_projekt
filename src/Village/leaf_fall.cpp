//
// Created by Marti on 13. 12. 2021.
//
#include "scene.h"
#include "leaf_fall.h"

bool Leaf_fall::update(Scene &scene, float dt) {
    // Add object to scene when time reaches certain level
    time += dt;

//    auto axe = dynamic_cast<Axe*>(this);
//    auto tree = dynamic_cast<Tree*>(this);
//    for (auto &obj : scene.objects) {
//
//        // Ignore self in scene
//        if (obj.get() == this) continue;
//
//        // We only need to collide with asteroids and projectiles, ignore other objects
//        if (!axe)
//            axe = dynamic_cast<Axe*>(obj.get()); // dynamic_pointer_cast<Asteroid>(obj);
//        if(!tree)
//            tree = dynamic_cast<Tree*>(obj.get()); //dynamic_pointer_cast<Projectile>(obj);
//        if (!axe || !tree) continue;
//
//        // Compare distance to approximate size of the asteroid estimated from scale.
//        auto a = distance(axe->position, tree->position);
//        auto b = (axe->scale.z + tree->scale.z) * 1.8f;
//
//        std::cout << a << "\t" << tree->position.z << std::endl;
//        if (a < b && time > 0.5f) {
//            auto leaf = std::make_unique<Leaf>();
//            leaf->position = position;
//            leaf->position.x += glm::linearRand(-1.0f, 1.0f);
//            leaf->position.z += glm::linearRand(-1.0f, 1.0f);
//            scene.objects.push_back(move(leaf));
//            axe = NULL;
//            time = 0;
//        }
    std::cout << time << "\t" << dt << std::endl;
    if (time > 5.0f){
        auto obj = std::make_unique<Leaf>();
        obj->position = position;
        obj->position.x += glm::linearRand(-1.0f, 1.0f);
        obj->position.z += glm::linearRand(-1.0f, 1.0f);
        scene.objects.push_back(move(obj));
        time = 0;
    }
    return true;
}
//bool Leaf_fall::update(Scene &scene, float dt) {
//    time += dt;
//    if (time > 0.5f) {
//        auto obj = std::make_unique<Leaf>();
//        obj->position = position;
//        obj->position.x += glm::linearRand(-1.0f, 1.0f);
//        obj->position.z += glm::linearRand(-1.0f, 1.0f);
//        scene.objects.push_back(move(obj));
//        time = 0;
//    }
//    return true;
//}

void Leaf_fall::render(Scene &scene) {

}

