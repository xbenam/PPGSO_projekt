#ifndef PPGSO_CARTWHEELS_H
#define PPGSO_CARTWHEELS_H

#include <vector>
#include <ppgso/ppgso.h>
#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>
#include "object.h"


class CartWheels final : public Object {
private:
    float actualRotate;
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Texture> texture;
    static std::unique_ptr<ppgso::Shader> shader;

public:
    CartWheels();

    bool update(Scene &scene, float time) override;

    void render(Scene &scene) override;
};


#endif //PPGSO_CARTWHEELS_H