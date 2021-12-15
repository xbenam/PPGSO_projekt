#include "scene.h"
#include "cart.h"
#include "wisp.h"
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Cart::mesh;
std::unique_ptr<ppgso::Texture> Cart::texture;
std::unique_ptr<ppgso::Shader> Cart::shader;

Cart::Cart() {
    scale = {.035, .035, .035};
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("cart.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cart.obj");
    if (!cartWheels) cartWheels = std::make_unique<CartWheels>();
}

bool Cart::update(Scene &scene, float time) {
    cartWheels->position = position;
    cartWheels->scale = scale;
    cartWheels->rotation = rotation;
    generateModelMatrix();
    cartWheels->update(scene, time);
    return true;
}

void Cart::render(Scene &scene) {
    shader->use();
    glm::vec3 fireplace;
    for (auto &obj : scene.objects) {

        // Ignore self in scene
        if (obj.get() == this) continue;

        // We only need to collide with asteroids and projectiles, ignore other objects
        auto wisp = dynamic_cast<Wisp *>(obj.get()); // dynamic_pointer_cast<Asteroid>(obj);
        if (!wisp) continue;
        scene.Light2pos = {wisp->position.x, wisp->position.y, wisp->position.z};
    }
    // light
//    shader->setUniform("LightDirection", scene.dirLightDirection);
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

    mesh->render();
    cartWheels->render(scene);
}