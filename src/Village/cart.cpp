#include "scene.h"
#include "cart.h"
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Cart::mesh;
std::unique_ptr<ppgso::Texture> Cart::texture;
std::unique_ptr<ppgso::Shader> Cart::shader;

Cart::Cart() {
    scale = {.035, .035, .035};
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("cart.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cart.obj");
    if (!cartWheels) cartWheels = std::make_unique<CartWheels>();
}

bool Cart::update(Scene &scene, float time) {
    cartWheels->position = position;
    cartWheels->scale = scale;
    cartWheels->rotation = rotation;
    generateModelMatrix();
    cartWheels->update(scene, time);
    return true;
}

void Cart::render(Scene &scene) {
    shader->use();

    // light
    shader->setUniform("viewPos",scene.camera->position);
    shader->setUniform("light.position",scene.LightPosition);
    shader->setUniform("light.color", scene.lightColor);
    shader->setUniform("light.ambient",scene.LightAmb);
    shader->setUniform("light.diffuse",scene.LightDiff);
    shader->setUniform("light.specular",scene.LightSpec);

    shader->setUniform("light.linear",scene.lightLin);
    shader->setUniform("light.constant",scene.lightConst);
    shader->setUniform("light.quadratic",scene.lightQuad);

    shader->setUniform("directLight.direction",scene.dirLightDirection);
    shader->setUniform("directLight.color",scene.lightColor);
    shader->setUniform("directLight.ambient",scene.dirLightAmb);
    shader->setUniform("directLight.diffuse",scene.dirLightDiff);
    shader->setUniform("directLight.specular",scene.dirLightSpec);

    shader->setUniform("material.shininess",scene.Mat3Shiny);
    shader->setUniform("material.ambient",scene.Mat3Amb);
    shader->setUniform("material.diffuse",scene.Mat3Diff);
    shader->setUniform("material.specular",scene.Mat3Spec);
    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);


    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    mesh->render();

    mesh->render();
    cartWheels->render(scene);
}