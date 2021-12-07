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

using namespace std;
using namespace glm;
using namespace ppgso;

class SceneWindow : public Window {
private:
    Scene beginScene;
    ppgso::Shader program = {texture_vert_glsl, texture_frag_glsl};
    ppgso::Texture horse_texture = {ppgso::image::loadBMP("HorseShape_texture1.bmp")};

    ppgso::Mesh horse = {"horse.obj"};

    void initScene() {
        beginScene.objects.clear();

        // Create a camera
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
        camera->position.z = -15.0f;
        beginScene.camera = move(camera);

        // Add space background
        beginScene.objects.push_back(std::make_unique<Ground>());
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
    }
    void onIdle() override {

        // Set gray background
        glClearColor(.5f, .5f, .5f, 0);

        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        auto horseMatrix = glm::translate(glm::mat4{1.0f}, {1.0f, 1.0f, 1.0f}) *
                   glm::scale(glm::mat4{1}, {1,1,1});
        auto cameraMat = translate(glm::mat4{1.0f}, {0.0f, -15.0f, -50});

//        program.setUniform("ViewMatrix", glm::lookAt({cos((float) glfwGetTime())* 75,75.0f,sin((float) glfwGetTime())*-75.0f},{0.0f,1.0f,0.0f},glm::vec3{0.0f,1,0.0f}));
        program.setUniform("ViewMatrix", glm::lookAt({1, 30, -50.0f},{0,0,0},glm::vec3{0.0f,1,0.0f}));

//        program.setUniform("ViewMatrix", cameraMat);
        program.setUniform("ProjectionMatrix", glm::perspective((ppgso::PI / 180.f) * 60.0f, 1.0f, 0.1f, 250.0f));

        program.setUniform("ModelMatrix", horseMatrix);
        program.setUniform("Texture", horse_texture);
        horse.render();

    }
};

int main() {
    // Initialize our window
    SceneWindow window;

    // Main execution loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}