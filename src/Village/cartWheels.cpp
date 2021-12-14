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
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cartWheels.obj");
}

bool CartWheels::update(Scene &scene, float time) {
    actualRotate = 3 * position.z;
    rotation = {actualRotate, 0, 0};
    generateModelMatrix();
    return true;
}

void CartWheels::render(Scene &scene) {
    shader->use();

    // light
    shader->setUniform("LightDirection", scene.dirLightDirection);
    shader->setUniform("viewPos",scene.camera->position);
    shader->setUniform("light.position",scene.LightPosition);
    shader->setUniform("light.ambient",scene.LightAmb);
    shader->setUniform("light.diffuse",scene.LightDiff);
    shader->setUniform("light.specular",scene.LightSpec);

    shader->setUniform("light.linear",scene.lightLin);
    shader->setUniform("light.constant",scene.lightConst);
    shader->setUniform("light.quadratic",scene.lightQuad);

    shader->setUniform("directLight.direction",scene.dirLightDirection);
    shader->setUniform("directLight.ambient",scene.dirLightAmb);
    shader->setUniform("directLight.diffuse",scene.dirLightDiff);
    shader->setUniform("directLight.specular",scene.dirLightSpec);

    shader->setUniform("material.shininess",scene.Mat2Shiny);
    shader->setUniform("material.ambient",scene.Mat2Amb);
    shader->setUniform("material.diffuse",scene.Mat2Diff);
    shader->setUniform("material.specular",scene.Mat2Spec);
    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    mesh->render();
}