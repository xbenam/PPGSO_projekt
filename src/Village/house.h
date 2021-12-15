#ifndef PPGSO_HOUSE_H
#define PPGSO_HOUSE_H

#include <vector>
#include <ppgso/ppgso.h>
#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>
#include "object.h"


class House final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Texture> texture;
    static std::unique_ptr<ppgso::Shader> shader;
    float time = 0;

public:
    House();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;

    void generateSmoke(Scene &scene);
};


#endif //PPGSO_HOUSE_H
