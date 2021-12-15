#include "house.h"
#include "scene.h"
#include "smoke.h"
#include "wisp.h"
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> House::mesh;
std::unique_ptr<ppgso::Texture> House::texture;
std::unique_ptr<ppgso::Shader> House::shader;

House::House() {
    scale = {0.33, 0.33, 0.33};
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("house.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("house.obj");
}

bool House::update(Scene &scene, float dt) {
    time += dt;
    if(time > 1.0f)
        generateSmoke(scene);
    generateModelMatrix();
    return true;
}

void House::render(Scene &scene) {
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

void House::generateSmoke(Scene &scene) {
    auto smokeParticle = std::make_unique<Smoke>();
    smokeParticle->position = position;

    smokeParticle->position.y = 2.5f;
    smokeParticle->position.x = position.x - sin(rotation.z) * 0.5f;
    smokeParticle->position.z = position.z - cos(rotation.z) * 0.5f;

    smokeParticle->position.x += glm::linearRand(-0.1f, 0.1f);
    smokeParticle->position.z += glm::linearRand(-0.1f, 0.1f);
    scene.objects.push_back(move(smokeParticle));
}