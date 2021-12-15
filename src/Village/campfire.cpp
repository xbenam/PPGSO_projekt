//
// Created by Marti on 12. 12. 2021.
//

#include "campfire.h"
#include "smoke.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Campfire::mesh;
std::unique_ptr<ppgso::Texture> Campfire::texture;
std::unique_ptr<ppgso::Shader> Campfire::shader;

Campfire::Campfire() {
    scale *= 0.25f;
    position.y += 0.5f;
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("campfire.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("campfire.obj");
}

bool Campfire::update(Scene &scene, float dt) {
    time += dt;
    if(time > 0.05f)
        generateSmoke(scene);
    generateModelMatrix();
    return true;
}

void Campfire::render(Scene &scene) {
    shader->use();

    // light
    shader->setUniform("viewPos",scene.camera->position);
    shader->setUniform("light.position",{position.x, position.y + 0.2f, position.z});
    shader->setUniform("light.color", {1.0f, 0.7f, 0.f});
    shader->setUniform("light.ambient",scene.LightAmb);
    shader->setUniform("light.diffuse",scene.LightDiff);
    shader->setUniform("light.specular",scene.LightSpec);

    shader->setUniform("light.linear",scene.lightLin);
    shader->setUniform("light.constant",scene.lightConst);
    shader->setUniform("light.quadratic",scene.lightQuad);

    shader->setUniform("directLight.direction",position);
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

void Campfire::generateSmoke(Scene &scene) {
    auto smokeParticle = std::make_unique<Smoke>();
    smokeParticle->position = position;
    smokeParticle->position.y = 0.8f;
    smokeParticle->position.x += glm::linearRand(-0.2f, 0.2f);
    smokeParticle->position.z += glm::linearRand(-0.2f, 0.2f);
    scene.objects.push_back(move(smokeParticle));
}

