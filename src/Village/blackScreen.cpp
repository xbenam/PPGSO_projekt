
#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>
#include "scene.h"
#include "blackScreen.h"

std::unique_ptr<ppgso::Mesh> BlackScreen::mesh;
std::unique_ptr<ppgso::Shader> BlackScreen::shader;

BlackScreen::BlackScreen() {
    position = {0.0f, 1.0f, -47.5f};
    rotation.x = ppgso::PI;
    scale.x *= 50;
    scale.y *= 50;
    color = {0.0f, 0.0f, 0.0f};
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("quad.obj");
}

bool BlackScreen::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void BlackScreen::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("OverallColor", color);
    mesh->render();
}
