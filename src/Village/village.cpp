//
// Created by Mário Kolenič on 13/11/2021.
//
#include <iostream>
#include <ppgso.h>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

#include "ground.h"
#include "scene.h"
#include "camera.h"
#include "horse.h"
#include "walls.h"

using namespace std;
using namespace glm;
using namespace ppgso;

class SceneWindow : public Window {
private:
    Scene beginScene;
    ppgso::Shader program = {texture_vert_glsl, texture_frag_glsl};

    void initScene() {
        beginScene.objects.clear();

        // Create a camera
        auto camera = std::make_unique<Camera>(100.0f, 1.0f, 0.1f, 1000.0f);
        camera->position.y = 10.0f;
        camera->position.z = -20.0f;
        beginScene.camera = move(camera);

        auto ground = std::make_unique<Ground>();
        beginScene.objects.push_back(move(ground));

        auto horse = std::make_unique<Horse>();
        beginScene.objects.push_back(move(horse));

        auto castleWalls = std::make_unique<Walls>();
        beginScene.objects.push_back(move(castleWalls));
    }
public:
    SceneWindow() : Window{"Village", 1000, 1000} {

        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable polygon culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        initScene();
    }
    void onIdle() override {

        // Set gray background
        glClearColor(.5f, .5f, .5f, 0);

        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float dt = glfwGetTime();
        // Update and render all objects
        beginScene.update(dt);
        beginScene.render();

    }
};

int main() {
    // Initialize our window
    SceneWindow window;

    // Main execution loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}