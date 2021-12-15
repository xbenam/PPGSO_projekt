#include "walls.h"
#include "scene.h"
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Walls::mesh;
std::unique_ptr<ppgso::Texture> Walls::texture;
std::unique_ptr<ppgso::Shader> Walls::shader;

Walls::Walls() {
    scale = {0.7, 0.5, 1};
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("walls.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("castleWalls.obj");
}

bool Walls::update(Scene &scene, float time) {
    generateModelMatrix();
    return true;
}

void Walls::render(Scene &scene) {
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
}