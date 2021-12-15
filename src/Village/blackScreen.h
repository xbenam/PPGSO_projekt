#pragma once

class BlackScreen : public Object{
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    glm::vec3 speed;

public:
    BlackScreen();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

