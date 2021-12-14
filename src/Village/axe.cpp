//
// Created by Marti on 14. 12. 2021.
//
#include "scene.h"
#include "axe.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include <cmath>

std::unique_ptr<ppgso::Mesh> Axe::mesh;
std::unique_ptr<ppgso::Texture> Axe::texture;
std::unique_ptr<ppgso::Shader> Axe::shader;

Axe::Axe() {
    scale *= 1.5;
//    rotation.z += ppgso::PI/2;
//    rotation.x += ppgso::PI/2;
//    rotation.y -= ppgso::PI/2;
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("axe.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("axe.obj");
}

bool Axe::update(Scene &scene, float dt) {
    time += dt;
//    std::cout << std::cos(time) << "\t" << std::cos(dt) << std::endl;
//    rotation.x = ppgso::PI/4+ ppgso::PI/4 * -std::cos(time*2);
    rotation.z =  ppgso::PI/4 * -std::cos(time*2);
//    position.z = 1 + std::cos(time*2);
//    rotation.x = -std::sin(time*2);
//    rotation.z = -std::cos(time*2);
//    rotation.y = -std::sin(time*2);
//    rotation +=  std::sin(time)/1000;
    generateModelMatrix();
    return true;
}


void Axe::render(Scene &scene) {
    auto t = (float) glfwGetTime();

    shader->use();

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

    shader->setUniform("material.shininess",scene.Mat1Shiny);
    shader->setUniform("material.ambient",scene.Mat1Amb);
    shader->setUniform("material.diffuse",scene.Mat1Diff);
    shader->setUniform("material.specular",scene.Mat1Spec);
    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

//    position.z += std::cos(t*3);
//    auto cuttingAnimation =
//            glm::translate(glm::mat4{1.0f}, {position.x , position.y,position.z + std::cos(t*3)})
//            * glm::rotate(glm::mat4{1.0f}, t*3, {rotation.x + std::sin(t*3),
//                                                                rotation.y + std::sin(t*3),
//                                                                0.0f})
//            * glm::scale(glm::mat4{1}, {1.5f,1.5f, 1.5f});
//
//    shader->setUniform("ModelMatrix", cuttingAnimation);
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    mesh->render();
}