//
// Created by Marti on 15. 12. 2021.
//

#include "smoke.h"
#include "scene.h"

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>


std::unique_ptr<ppgso::Mesh> Smoke::mesh;
std::unique_ptr<ppgso::Texture> Smoke::texture;
std::unique_ptr<ppgso::Shader> Smoke::shader;

Smoke::Smoke() {
    speed = {glm::linearRand(-0.001f, 0.001f), 0,glm::linearRand(0.0f, 0.001f)};
    scale *= 0.025f;
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("smoke.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
}

bool Smoke::update(Scene &scene, float dt) {
    age += dt;
//    std::cout << dt << "\t" << age << std::endl;
    if (position.y > 0.0f){
        speed = {glm::linearRand(-0.005f, 0.005f), 0,glm::linearRand(0.0f, 0.002f)};
        position -= speed;
        position.y += dt/2;
    }
    if(age > 5.0f)
        return false;
    for (auto &obj : scene.objects) {
        // Ignore self in scene
        if (obj.get() == this) continue;

        // We only need to collide with asteroids and projectiles, ignore other objects
        auto anotherSmoke = dynamic_cast<Smoke*>(obj.get()); // dynamic_pointer_cast<Asteroid>(obj);
        if (!anotherSmoke ) continue;

        if (age < 0.2f) continue;
        auto a = distance(position, obj->position);
        auto b = (obj->scale.y + scale.y) * 1.2f;
//        std::cout << a << "\t" << b << std::endl;
        if (a < b) {
            if (scale.y < 0.00001f) continue;
            // Generate smaller asteroids
            auto smokeParticle = std::make_unique<Smoke>();
            smokeParticle->position = position;
            smokeParticle->scale = scale / 2.0f;
            scene.objects.push_back(move(smokeParticle));
            return false;
        }
    }
    generateModelMatrix();
    return true;
}

void Smoke::render(Scene &scene) {
    shader->use();

//    shader->setUniform("LightDirection", scene.lightDirection);
    shader->setUniform("Transparency",1.0f - age / 5.0f);
    shader->setUniform("viewPos",scene.camera->position);
    shader->setUniform("light.position", {position.x, position.y - 1.0f, position.z});
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
