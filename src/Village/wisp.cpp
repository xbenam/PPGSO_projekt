//
// Created by Marti on 15. 12. 2021.
//

#include "wisp.h"
#include "scene.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

#include <cmath>

std::unique_ptr<ppgso::Mesh> Wisp::mesh;
std::unique_ptr<ppgso::Shader> Wisp::shader;

Wisp::Wisp() {
    color = {0, 0, 1.0f};
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool Wisp::update(Scene &scene, float dt) {
    time += dt;
    scale = {0.2 + 0.1 * std::sin(time), 0.2 + 0.1 * std::sin(time), 0.2 + 0.1 * std::sin(time)};
    if(time <= 2)
    {
        position = bezierPoint(time / 2.0f);
    } else
        time = 0;
    generateModelMatrix();
    return true;
}

void Wisp::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("OverallColor", color);
    mesh->render();
}

glm::vec3 Wisp::bezierPoint(float t) {
    glm::vec3 p01 = lerp(path[0], path[1], t);
    glm::vec3 p12 = lerp(path[1], path[2], t);
    glm::vec3 p23 = lerp(path[2], path[3], t);
    glm::vec3 p34 = lerp(path[3], path[4], t);
    glm::vec3 p45 = lerp(path[4], path[5], t);

    glm::vec3 p0112 = lerp(p01, p12, t);
    glm::vec3 p1223 = lerp(p12, p23, t);
    glm::vec3 p2334 = lerp(p23, p34, t);
    glm::vec3 p3445 = lerp(p34, p45, t);

    glm::vec3 p01121223 = lerp(p0112, p1223, t);
    glm::vec3 p12232334 = lerp(p1223, p2334, t);
    glm::vec3 p23343445 = lerp(p2334, p3445, t);

    glm::vec3 p0112122312232334 = lerp(p01121223, p12232334, t);
    glm::vec3 p1223233423343445 = lerp(p12232334, p23343445, t);

    glm::vec3 p01121223122323341223233423343445 = lerp(p0112122312232334, p1223233423343445, t);
    return p01121223122323341223233423343445;
}
