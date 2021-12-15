#include "mill.h"
#include "scene.h"
#include "campfire.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Mill::meshMillBase;
std::unique_ptr<ppgso::Texture> Mill::textureBase;
std::unique_ptr<ppgso::Shader> Mill::shader;


Mill::Mill() {
    scale *= 0.02;
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!meshMillBase) meshMillBase = std::make_unique<ppgso::Mesh>("mill_base.obj");
    if (!textureBase) textureBase = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("mill_base.bmp"));
    if (!blades) blades = std::make_unique<Blades>(position);

}

bool Mill::update(Scene &scene, float time) {
    blades->position = position;
    blades->position.y = 3.0f;
    blades->position.x = position.x - sin(rotation.z) * 0.1f - 0.5;
    blades->position.z = position.z - cos(rotation.z) * 0.1f - 0.1;
    blades->rotation.z = rotation.z;
    blades->scale = scale;
    generateModelMatrix();
    blades->update(scene, time);
    return true;
}

void Mill::render(Scene &scene) {
    shader->use();
    glm::vec3 fireplace;
    for (auto &obj : scene.objects) {

        // Ignore self in scene
        if (obj.get() == this) continue;

        // We only need to collide with asteroids and projectiles, ignore other objects
        auto fire = dynamic_cast<Campfire *>(obj.get()); // dynamic_pointer_cast<Asteroid>(obj);
        if (!fire) continue;
        scene.LightPosition = {fire->position.x, fire->position.y + 0.2f, fire->position.z};
    }
    // light
//    shader->setUniform("LightDirection", scene.dirLightDirection);
    shader->setUniform("viewPos",scene.camera->position);
    shader->setUniform("light.position",scene.LightPosition);
    shader->setUniform("light.color", {1.0f, 0.7f, 0.f});
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



