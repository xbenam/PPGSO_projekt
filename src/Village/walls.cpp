#include "walls.h"
#include "scene.h"
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Walls::mesh;
std::unique_ptr<ppgso::Texture> Walls::texture;
std::unique_ptr<ppgso::Shader> Walls::shader;

Walls::Walls() {
    scale = {8, 8, 12};
    position = {-16, 0, 200};
    rotation = {0, 0, 1.61f};
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("castle.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("castle.obj");
}

bool Walls::update(Scene &scene) {
    generateModelMatrix();
    return true;
}

void Walls::render(Scene &scene) {
    shader->use();

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);


    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    mesh->render();
}