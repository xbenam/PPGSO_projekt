#include "mill.h"
#include "scene.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Mill::meshMillBase;
std::unique_ptr<ppgso::Texture> Mill::textureBase;
std::unique_ptr<ppgso::Shader> Mill::shader;


Mill::Mill() {
    position = {-5.0f,-0.2f,-1.0f};
    scale *= 0.02;
    rotation.z += 0.2f;
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!meshMillBase) meshMillBase = std::make_unique<ppgso::Mesh>("mill_base.obj");
    if (!textureBase) textureBase = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("mill_base.bmp"));
    if (!blades) blades = std::make_unique<Blades>(position);

}

bool Mill::update(Scene &scene, float time) {
    blades->position = position;
    blades->rotation.z = rotation.z;
    blades->scale = scale;
    generateModelMatrix();
    blades->update(scene, time);
    return true;
}

void Mill::render(Scene &scene) {
    shader->use();

    // light
//    shader->setUniform("LightDirection", scene.dirLightDirection);
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
    shader->setUniform("Texture", *textureBase);

    meshMillBase->render();
    blades->render(scene);
}



