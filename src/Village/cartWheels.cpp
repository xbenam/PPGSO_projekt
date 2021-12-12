#include "cartWheels.h"
#include "scene.h"
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> CartWheels::mesh;
std::unique_ptr<ppgso::Texture> CartWheels::texture;
std::unique_ptr<ppgso::Shader> CartWheels::shader;

CartWheels::CartWheels() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("cart.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cartWheel.obj");
}

bool CartWheels::update(Scene &scene) {
    position = {0, 10, 0};
    generateModelMatrix();
    return true;
}

void CartWheels::render(Scene &scene) {
    shader->use();

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);


    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    mesh->render();
}
