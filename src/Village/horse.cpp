
#include "scene.h"
#include "horse.h"
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Horse::mesh;
std::unique_ptr<ppgso::Texture> Horse::texture;
std::unique_ptr<ppgso::Shader> Horse::shader;

Horse::Horse() {
    scale = {.5, .5, .5};
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("HorseShape_texture1.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("horse.obj");
}

bool Horse::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Horse::render(Scene &scene) {
    shader->use();

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);


    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    mesh->render();
}
