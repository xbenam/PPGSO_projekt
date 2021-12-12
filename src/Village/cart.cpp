#include "scene.h"
#include "cart.h"
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Cart::mesh;
std::unique_ptr<ppgso::Texture> Cart::texture;
std::unique_ptr<ppgso::Shader> Cart::shader;

Cart::Cart() {
    rotation = {0, 0, -1.55f};
    scale = {.04, .04, .04};
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("cart.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cart.obj");
    if (!cartWheels) cartWheels = std::make_unique<CartWheels>();
}

bool Cart::update(Scene &scene) {
    position = {0, 1, -8};
    cartWheels->position = position;
    cartWheels->scale = scale;
    cartWheels->rotation = rotation;
    generateModelMatrix();
    cartWheels->update(scene);
    return true;
}

void Cart::render(Scene &scene) {
    shader->use();

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);


    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    mesh->render();
}