//
// Created by Marti on 10. 12. 2021.
//

#pragma once

#include <ppgso/ppgso.h>

#include "object.h"


class Sky final : public Object {
private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
public:
    /*!
     * Create new Sky background
     */
    Sky();

    /*!
     * Update sky background
     * @param scene Scene to update
     * @return true to delete the object
     */
    bool update(Scene &scene, float time) override;

    /*!
     * Render space background
     * @param scene Scene to render in
     */
    void render(Scene &scene) override;
};

