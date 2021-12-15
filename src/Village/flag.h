#ifndef PPGSO_FLAG_H
#define PPGSO_FLAG_H

#include <vector>
#include <ppgso/ppgso.h>
#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>
#include "object.h"

class Flag final : public Object {
private:
    glm::vec3 controlPoints[4][4]{
            { {-.5,-.5,0}, {0,-.5,0},{.5,-.5,0},{1,-.5,0} },
            { {-.5,0,0}, {0.5,0,0}, {1,0,0}, {1.5,0.5,0} },
            { {-.5,.5,0}, {0.5,0.5,0}, {1,0.5,0}, {1.5,0.5,0}, },
            { {-.5,1,0}, {0.5,1,0}, {1,1,0}, {1.5,1,0} }};
    static std::unique_ptr<ppgso::Texture> texture;
    static std::unique_ptr<ppgso::Shader> shader;
    std::vector<glm::vec3> vertices;

    // Texture coordinates
    std::vector<glm::vec2> texCoords;

    // Define our face using indexes to 3 vertices
    struct face {
        GLuint v0, v1, v2;
    };

    // Define our mesh as collection of faces
    std::vector<face> mesh;

    // These will hold the data and object buffers
    GLuint vao, vbo, tbo, ibo;
    glm::mat4 modelMatrix{1.0f};
    float time = 0;

public:
    glm::vec3 position{0,0,0};
    glm::vec3 rotation{0,0,0};
    glm::vec3 scale{1,1,1};

    Flag();

    ~Flag();

    glm::vec3 bezierPoint(const glm::vec3 controlPoints[4], float t);

    bool update(Scene &scene, float time) override;

    void render(Scene &scene) override;

};


#endif //PPGSO_FLAG_H
