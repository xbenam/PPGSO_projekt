#include "scene.h"

void Scene::update(float time) {
    camera->update(time);
    auto i = std::begin(objects);
    while (i != std::end(objects)) {
        auto obj = i->get();
        if (!obj->update(*this, time))
            i = objects.erase(i);
        else
            ++i;
    }
}

void Scene::render() {
    for ( auto& obj : objects )
        obj->render(*this);
}
/// Na koliziu som pouzil inu funkciu, konktretne tu kde sa prejde scena a hladaju sa konkretne typy a potom sa
/// porovnavaju ich vydalenosti.
//std::vector<Object*> Scene::intersect(const glm::vec3 &position, const glm::vec3 &direction) {
//    std::vector<Object*> intersected = {};
//    for(auto& object : objects) {
//        // Collision with sphere of size object->scale.x
//        auto oc = position - object->position;
//        auto radius = object->scale.x;
//        auto a = glm::dot(direction, direction);
//        auto b = glm::dot(oc, direction);
//        auto c = glm::dot(oc, oc) - radius * radius;
//        auto dis = b * b - a * c;
//
//        if (dis > 0) {
//            auto e = sqrt(dis);
//            auto t = (-b - e) / a;
//
//            if ( t > 0 ) {
//                intersected.push_back(object.get());
//                continue;
//            }
//
//            t = (-b + e) / a;
//
//            if ( t > 0 ) {
//                intersected.push_back(object.get());
//                continue;
//            }
//        }
//    }
//
//    return intersected;
//}