#include "ground.h"

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Ground::mesh;
std::unique_ptr<ppgso::Texture> Ground::texture;
std::unique_ptr<ppgso::Shader> Ground::shader;

Ground::Ground() {

    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("ground.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
}

void Ground::update() {
    modelMatrix = glm::translate(glm::mat4{1.0f}, {0.0f, 1.25f, 0.0f}) * glm::scale(glm::mat4{1}, {1000,0.1,1000});
}

void Ground::render() {
    shader->use();

    auto floor = glm::translate(glm::mat4{1.0f}, {0.0f, 1.25f, 0.0f}) * glm::scale(glm::mat4{1}, {1000,0.1,1000});

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    // Disable depth testing
    glDisable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    // Additive blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    mesh->render();

    // Disable blending
    glDisable(GL_BLEND);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
}