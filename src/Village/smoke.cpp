#include "smoke.h"
#include "scene.h"
#include "wisp.h"

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
    if (position.y > 0.0f){
        speed = {glm::linearRand(-0.005f, 0.005f), 0,glm::linearRand(0.0f, 0.02f)};
        position -= speed;
        position.y += dt/2;
    }
    if(age > 5.0f)
        return false;
    for (auto &obj : scene.objects) {

        if (obj.get() == this) continue;

        auto anotherSmoke = dynamic_cast<Smoke*>(obj.get());
        if (!anotherSmoke ) continue;

        if (age < 0.2f) continue;
        auto a = distance(position, obj->position);
        auto b = (obj->scale.y + scale.y) * 1.2f;
        if (a < b) {
            if (scale.y < 0.00001f) continue;
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
