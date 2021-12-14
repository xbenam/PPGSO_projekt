//
// Created by Marti on 10. 12. 2021.
//

#include "sky.h"
#include "scene.h"

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

// shared resources
std::unique_ptr<ppgso::Mesh> Sky::mesh;
std::unique_ptr<ppgso::Shader> Sky::shader;
std::unique_ptr<ppgso::Texture> Sky::texture;


Sky::Sky() {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("sky.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("quad.obj");
}

bool Sky::update(Scene &scene, float time) {
    // Offset for UV mapping, creates illusion of scrolling
    generateModelMatrix();
    return true;
}

void Sky::render(Scene &scene) {
    // Disable writing to the depth buffer so we render a "background"
    glDepthMask(GL_FALSE);

    // NOTE: this object does not use camera, just renders the entire quad as is
    shader->use();

    // Render mesh, not using any projections, we just render in 2D
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("ViewMatrix", glm::mat4{1.0f});
    shader->setUniform("ProjectionMatrix", glm::mat4{1.0f});
    shader->setUniform("Texture", *texture);
    mesh->render();

    glDepthMask(GL_TRUE);
}