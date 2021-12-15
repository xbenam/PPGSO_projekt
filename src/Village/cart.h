#ifndef PPGSO_CART_H
#define PPGSO_CART_H

#include <vector>
#include <ppgso/ppgso.h>
#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>
#include "object.h"
#include "cartWheels.h"


class Cart final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Texture> texture;
    static std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<CartWheels> cartWheels;

public:
    Cart();

    bool update(Scene &scene, float time) override;

    void render(Scene &scene) override;
};


#endif //PPGSO_CART_H