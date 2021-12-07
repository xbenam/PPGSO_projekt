#include "scene.h"

void Scene::update() {
    camera->update();
}

void Scene::render() {
    // Simply render all objects
    for ( auto& obj : objects )
        obj->render(*this);
}

std::vector<Object*> Scene::intersect(const glm::vec3 &position, const glm::vec3 &direction) {
    std::vector<Object*> intersected = {};
    for(auto& object : objects) {
        // Collision with sphere of size object->scale.x
        auto oc = position - object->position;
        auto radius = object->scale.x;
        auto a = glm::dot(direction, direction);
        auto b = glm::dot(oc, direction);
        auto c = glm::dot(oc, oc) - radius * radius;
        auto dis = b * b - a * c;

        if (dis > 0) {
            auto e = sqrt(dis);
            auto t = (-b - e) / a;

            if ( t > 0 ) {
                intersected.push_back(object.get());
                continue;
            }

            t = (-b + e) / a;

            if ( t > 0 ) {
                intersected.push_back(object.get());
                continue;
            }
        }
    }

    return intersected;
}