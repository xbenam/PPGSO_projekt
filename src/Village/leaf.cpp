//
// Created by Marti on 13. 12. 2021.
//
#include "scene.h"
#include "leaf.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Leaf::mesh;
std::unique_ptr<ppgso::Shader> Leaf::shader;

Leaf::Leaf() {
    speed = {glm::linearRand(-0.001f, 0.001f), 0,glm::linearRand(0.0f, 0.001f)};
    scale *= 0.1;
    color = {glm::linearRand(0.2f,0.3f), glm::linearRand(0.6f,0.8f), 0.1f};
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool Leaf::update(Scene &scene, float dt) {
    age += dt;
    if (position.y > 0.0f){
        position -= speed;
        position.y -= dt;
    }
    if(age > 5.0f)
        return false;
    generateModelMatrix();
    return true;
}

void Leaf::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("OverallColor", color);
    mesh->render();
}
