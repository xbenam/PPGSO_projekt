#include "cube.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Cube::mesh;
std::unique_ptr<ppgso::Texture> Cube::texture;
std::unique_ptr<ppgso::Shader> Cube::shader;

Cube::Cube() {

    scale *= 0.5;
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("sphere.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
}

bool Cube::update(Scene &scene) {
    rotation.z += 0.0005;
//    position.z += 0.0001;
//    modelMatrix = glm::translate(glm::mat4{1.0f}, {0.0f, 1.25f, 0.0f}) * glm::scale(glm::mat4{1}, {1000,0.1,1000});
    generateModelMatrix();
    return true;
}

void Cube::render(Scene &scene) {
    shader->use();

//    shader->setUniform("LightDirection", scene.lightDirection);
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


    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    mesh->render();
}