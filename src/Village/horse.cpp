#include "scene.h"
#include "horse.h"
#include "wisp.h"
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Horse::mesh;
std::unique_ptr<ppgso::Texture> Horse::texture;
std::unique_ptr<ppgso::Shader> Horse::shader;

Horse::Horse() {
    position = {0, 0, -20};
    scale = {.011, .011, .011};
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("horse.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("horse.obj");
    if (!cart) cart = std::make_unique<Cart>();
}

bool Horse::update(Scene &scene, float dt) {
    time += dt;

    std::cout << time <<std::endl;
    if(scene.camera->wasSet) {
        direction = {sin(angle), 0, cos(angle)};
        rotation = {0, 0, angle};
        position += direction * dt;
        cart->position = {position.x - sin(angle) * 1.3, position.y + 0.2, position.z - cos(angle) * 1.3};
        cart->rotation = rotation;
        cart->scale = scale;
        cart->update(scene, time);

        if(8 < time && time < 20) {
            scene.camera->orientation = {0, 0, -1};
            scene.camera->position = {(position.x + 0.5), (position.y + 0.2f), (position.z - 2)};
            scene.camera->viewMatrix = lookAt(scene.camera->position,
                                              (scene.camera->position - scene.camera->orientation),
                                              scene.camera->up);
        }
        else {
            if(26 < time && time <= 30) {
                timeRotate += dt;
                angle = ppgso::PI/2 * (timeRotate / 4);
            }
            if(time > 42 && time < 72) {
                scene.camera->orientation = {20, 3, 9};
                scene.camera->cameraAroundMill = true;
                timeRotate = 0;
                angle = -ppgso::PI/2;
            }
            else {
                if((time > 83 && time < 86) || ((time > 92 && time < 94) && angle < 0)) {
                    timeRotate += dt;
                    angle = (-ppgso::PI / 2) + (ppgso::PI / 2 * (timeRotate / 4));
                }
                else if (time >= 104) {
                    scene.objects.clear();
                    exit(0);
                }
                scene.camera->orientation = position;
                scene.camera->position = {position.x - sin(angle) * 3, position.y + 1, position.z - cos(angle) * 3};
            }
        }
    }
    generateModelMatrix();
    return true;
}

void Horse::render(Scene &scene) {
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
    cart->render(scene);
}
