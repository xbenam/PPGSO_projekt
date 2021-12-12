#include "ground.h"
#include "scene.h"

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Ground::mesh;
std::unique_ptr<ppgso::Texture> Ground::texture;
std::unique_ptr<ppgso::Shader> Ground::shader;

Ground::Ground() {
    position = {0, 0, 0};
    scale = {1000, 0.1, 1000};

    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("ground.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
}

bool Ground::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Ground::render(Scene &scene) {
    shader->use();

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);


    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    mesh->render();
}