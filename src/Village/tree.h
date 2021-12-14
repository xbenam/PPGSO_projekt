#ifndef PPGSO_TREE_H
#define PPGSO_TREE_H

#include <ppgso/ppgso.h>
#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>
#include "object.h"


class Tree final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Texture> texture;
    static std::unique_ptr<ppgso::Shader> shader;

public:
    Tree();

    bool update(Scene &scene, float time) override;

    void render(Scene &scene) override;
};


#endif //PPGSO_TREE_H
