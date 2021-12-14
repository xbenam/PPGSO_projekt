#include "scene.h"
#include "horse.h"
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Horse::mesh;
std::unique_ptr<ppgso::Texture> Horse::texture;
std::unique_ptr<ppgso::Shader> Horse::shader;

Horse::Horse() {
    position = {0, 0, -20};
    scale = {.011, .011, .011};
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("horse.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("horse.obj");
    if (!cart) cart = std::make_unique<Cart>();
}

bool Horse::update(Scene &scene, float dt) {
    time += dt;
    float angle = -ppgso::PI/6;
    rotation = {0, 0, angle};
    position = {position.x, position.y, position.z + dt};
    cart->position = {position.x, position.y + 0.2, position.z - 1.3};
    cart->position.x = (cos(angle) * cart->position.x) + (-(sin(angle)) * cart->position.z);
    cart->position.z = (sin(angle) * cart->position.x) + (cos(angle) * cart->position.z);
    cart->rotation = rotation;
    cart->scale = scale;
    cart->update(scene, time);

    std::cout << time <<std::endl;
    if(scene.camera->wasSet) {
        if(time <= 8) {
            scene.camera->orientation = position;
            scene.camera->position = {position.x, position.y + 1, position.z - 4};
        }
        else if(8 < time && time < 20) {
            scene.camera->orientation = {0, 0, -1};
            scene.camera->position = {(position.x + 0.5), (position.y + 0.2f), (position.z - 2)};
            scene.camera->viewMatrix = lookAt(scene.camera->position,
                                              (scene.camera->position - scene.camera->orientation),
                                              scene.camera->up);
        }
        else {
            rotation = {0, 0, -ppgso::PI/6};
            scene.camera->orientation = position;
            scene.camera->position = {position.x, position.y + 0.7f, position.z - 3};
        }
    }
    generateModelMatrix();
    return true;
}

void Horse::render(Scene &scene) {
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
    cart->render(scene);
}
