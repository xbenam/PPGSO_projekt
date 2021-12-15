//
// Created by Marti on 14. 12. 2021.
//
#include "scene.h"
#include "axe.h"
#include "wisp.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include <cmath>

std::unique_ptr<ppgso::Mesh> Axe::mesh;
std::unique_ptr<ppgso::Texture> Axe::texture;
std::unique_ptr<ppgso::Shader> Axe::shader;

Axe::Axe() {
    scale *= 1.5;
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("axe.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("axe.obj");
}

bool Axe::update(Scene &scene, float dt) {
    time += dt;
    rotation.z = -ppgso::PI/4 + ppgso::PI/4 * std::cos(time*2);
    position.z = 1 * std::cos(time*2);
    generateModelMatrix();
    return true;
}


void Axe::render(Scene &scene) {

    shader->use();
    glm::vec3 fireplace;
    for (auto &obj : scene.objects) {

        if (obj.get() == this) continue;

        auto wisp = dynamic_cast<Wisp *>(obj.get());
        if (!wisp) continue;
        scene.Light2pos = {wisp->position.x, wisp->position.y, wisp->position.z};
    }
    // light
    shader->setUniform("viewPos",scene.camera->position);
    shader->setUniform("light[0].position",scene.Light1pos);
    shader->setUniform("light[0].color", scene.light1Color);
    shader->setUniform("light[0].ambient",scene.LightAmb);
    shader->setUniform("light[0].diffuse",scene.LightDiff);
    shader->setUniform("light[0].specular",scene.LightSpec);

    shader->setUniform("light[0].linear",scene.lightLin);
    shader->setUniform("light[0].constant",scene.lightConst);
    shader->setUniform("light[0].quadratic",scene.lightQuad);

    shader->setUniform("light[1].position",scene.Light2pos);
    shader->setUniform("light[1].color", scene.light2Color);
    shader->setUniform("light[1].ambient",scene.LightAmb);
    shader->setUniform("light[1].diffuse",scene.LightDiff);
    shader->setUniform("light[1].specular",scene.LightSpec);

    shader->setUniform("light[1].linear",scene.lightLin);
    shader->setUniform("light[1].constant",scene.lightConst);
    shader->setUniform("light[1].quadratic",scene.lightQuad);

    shader->setUniform("directLight.direction",scene.dirLightDirection);
    shader->setUniform("directLight.color",scene.lightColor);
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