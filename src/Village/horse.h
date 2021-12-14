#ifndef PPGSO_HORSE_H
#define PPGSO_HORSE_H

#include <vector>
#include <ppgso/ppgso.h>
#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>
#include "object.h"
#include "cart.h"


class Horse final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Texture> texture;
    static std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<Cart> cart;
    float time = 0;

public:
    Horse();

    bool update(Scene &scene, float time) override;

    void render(Scene &scene) override;
};


#endif //PPGSO_HORSE_H
