
#include "oak.h"
#include "scene.h"
#include "axe.h"
#include "leaf.h"
#include "wisp.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Oak::mesh;
std::unique_ptr<ppgso::Texture> Oak::texture;
std::unique_ptr<ppgso::Shader> Oak::shader;

Oak::Oak() {
    scale *= 0.005f;
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("oak.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("oak.obj");
}

bool Oak::update(Scene &scene, float dt) {
    time += dt;
    int times = 0;
    for (auto &obj : scene.objects) {

        // Ignore self in scene
        if (obj.get() == this) continue;

        // We only need to collide with asteroids and projectiles, ignore other objects
        auto axe = dynamic_cast<Axe*>(obj.get()); // dynamic_pointer_cast<Asteroid>(obj);
        if (!axe) continue;

        // Compare distance to approximate size of the asteroid estimated from scale.
        auto a = distance(axe->position, this->position);
        auto b = (axe->scale.z + this->scale.z) * 1.0f;

        if (a < b && time > 2.0f) {
            generateLeafs(scene, glm::linearRand(7,12));
            time = 0;
        }
    }
    generateModelMatrix();
    return true;
}

void Oak::render(Scene &scene) {
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

void Oak::generateLeafs(Scene &scene, float count)
{
    for (float i = 0; i < count; i++) {
        auto leaf = std::make_unique<Leaf>();
        leaf->position = position;
        leaf->position.y = 1.5f;
        leaf->position.x += glm::linearRand(-0.75f, 0.75f);
        leaf->position.z += glm::linearRand(-0.75f, 0.75f);
        scene.objects.push_back(move(leaf));
    }
}