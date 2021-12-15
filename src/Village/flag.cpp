#include "flag.h"
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

std::unique_ptr<ppgso::Texture> Flag::texture;
std::unique_ptr<ppgso::Shader> Flag::shader;

Flag::Flag() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("lena.bmp"));
    // Generate Bezier patch points and incidences
    unsigned int PATCH_SIZE = 10;
    for (unsigned int i = 0; i < PATCH_SIZE; i++) {
        for (unsigned int j = 0; j < PATCH_SIZE; j++) {
            // HINT: Compute u, v coordinates
            glm::vec3 newBez[4];
            for (unsigned int k = 0; k < 4; k++)
                newBez[k] = bezierPoint(controlPoints[k], (float) i / (float) PATCH_SIZE);
            vertices.push_back(bezierPoint(newBez, (float) j / (float) PATCH_SIZE));

            texCoords.emplace_back((float) i / (float) PATCH_SIZE, 1.0f - (float) j / (float) PATCH_SIZE);
            // vertices.push_back(??);
            // texCoords.push_back(??);
        }
    }
    // Generate indices
    for(unsigned int i = 1; i < PATCH_SIZE; i++) {
        for (unsigned int j = 1; j < PATCH_SIZE; j++) {
            // indices.push_back(??);
            // indices.push_back(??);
            // indices.push_back(??);

            mesh.push_back({i + PATCH_SIZE * j ,i + PATCH_SIZE * (j-1), (i-1) + PATCH_SIZE * j});
            mesh.push_back({(i - 1) + PATCH_SIZE * j ,i + PATCH_SIZE * (j-1), (i-1) + PATCH_SIZE * (j-1)});
            // indices.push_back(??);
            // indices.push_back(??);
            // indices.push_back(??);
        }
    }

    // Copy data to OpenGL
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Copy positions to gpu
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Set vertex program inputs
    auto position_attrib = shader->getAttribLocation("Position");
    glEnableVertexAttribArray(position_attrib);
    glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Copy texture positions to gpu
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);

    // Set vertex program inputs
    auto texCoord_attrib = shader->getAttribLocation("TexCoord");
    glEnableVertexAttribArray(texCoord_attrib);
    glVertexAttribPointer(texCoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Copy indices to gpu
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.size() * sizeof(face), mesh.data(), GL_STATIC_DRAW);
}

Flag::~Flag() {
    // Delete data from OpenGL
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &tbo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

glm::vec3 Flag::bezierPoint(const glm::vec3 controlPoints[4], float t) {
    glm::vec3 p01 = glm::lerp(controlPoints[0], controlPoints[1], t);
    glm::vec3 p12 = glm::lerp(controlPoints[1], controlPoints[2], t);
    glm::vec3 p23 = glm::lerp(controlPoints[2], controlPoints[3], t);

    glm::vec3 p0112 = glm::lerp(p01, p12, t);
    glm::vec3 p1223 = glm::lerp(p12, p23, t);

    glm::vec3 p01121223 = glm::lerp(p0112, p1223, t);
    return p01121223;
}

// Set the object transformation matrix
bool Flag::update(Scene &scene, float dt) {
    time += dt;
    modelMatrix = translate(glm::mat4{1}, position) *
                  rotate(glm::mat4{1}, rotation.x, {1,0,0}) *
                  rotate(glm::mat4{1}, rotation.y, {0,1,0}) *
                  rotate(glm::mat4{1}, rotation.z, {0,0,1}) *
                  glm::scale(glm::mat4{1},scale);

    return true;
}

// Draw polygons
void Flag::render(Scene &scene){
    // Update transformation and color uniforms in the shader
    shader->use();

    // Initialize projection
    // Create projection matrix (field of view (radians), aspect ratio, near plane distance, far plane distance)
    // You can think of this as the camera objective settings
    auto projection = glm::perspective( (ppgso::PI/180.f) * 60.0f, 1.0f, 0.1f, 10.0f);
    shader->setUniform("ProjectionMatrix", projection);

    // Create view matrix (translate camera a bit backwards, so we can see the geometry)
    // This can be seen as the camera position/rotation in space
    auto view = glm::translate(glm::mat4{1}, {0.0f, 0.0f, -3.0f});
    shader->setUniform("ViewMatrix", view);

    // Set model position
    shader->setUniform("ModelMatrix", modelMatrix);

    // Bind texture
    shader->setUniform("Texture", *texture);

    glBindVertexArray(vao);
    //glDrawElements(??);
    glDrawElements(GL_TRIANGLES, (GLsizei) mesh.size() * 3, GL_UNSIGNED_INT, 0);

};