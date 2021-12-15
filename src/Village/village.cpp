//
// Created by Mário Kolenič on 13/11/2021.
//
#include <iostream>
#include <ppgso.h>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

#include "ground.h"
#include "scene.h"
#include "sky.h"
#include "cube.h"
#include "mill.h"
#include "tree.h"
#include "leaf_fall.h"
#include "axe.h"
#include "campfire.h"

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
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
        camera->position.z = -10.0f;
//        camera->orientation.y = ppgso::PI/4;
        camera->position.y = 1;
        camera->orientation.x = ppgso::PI/4;
        beginScene.camera = move(camera);

        beginScene.objects.push_back(std::make_unique<Sky>());

        // Create a ground
        beginScene.objects.push_back(std::make_unique<Ground>());

        auto cube1 = std::make_unique<Cube>();
        cube1->position.y += 0.75;
        cube1->rotation.x = ppgso::PI/4;
        beginScene.objects.push_back(move(cube1));

        auto tree = std::make_unique<Tree>();
        tree->position.x += 5.0f;
        beginScene.objects.push_back(move(tree));

//        auto leaf_fall_generator = std::make_unique<Leaf_fall>();
//        leaf_fall_generator->position.x += 5.0f;
//        leaf_fall_generator->position.y += 3.0f;
//        beginScene.objects.push_back(move(leaf_fall_generator));

        auto mill = std::make_unique<Mill>();
        mill->position.x -= 1.0f;
//        beginScene.objects.push_back(mill)
        beginScene.objects.push_back(move(mill));

        auto campfire = std::make_unique<Campfire>();
        campfire->position.x -= 10.0f;
        campfire->position.z -= 3.0f;
//        beginScene.objects.push_back(mill)
        beginScene.objects.push_back(move(campfire));

        auto axe = std::make_unique<Axe>();
        axe->position.x += 4.0f;
        axe->position.y += 1.0f;
        axe->position.z += 1.5f;
        beginScene.objects.push_back(move(axe));
    }
public:
    SceneWindow() : Window{"Village", 1024, 1024} {

        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable polygon culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_FOG);


        initScene();
    }

    void onKey(int key, int scanCode, int action, int mods) override {
        beginScene.keyboard[key] = action;

        // Reset
        beginScene.camera->Inputs(key);

    }

    void onCursorPos(double cursorX, double cursorY) override {
        beginScene.cursor.x = cursorX;
        beginScene.cursor.y = cursorY;

    }

    void onMouseButton(int button, int action, int mods) override{
        if(button == GLFW_MOUSE_BUTTON_LEFT) {
            beginScene.cursor.left = action;
            if (beginScene.cursor.left == GLFW_PRESS) {
//                if (beginScene.camera->firstClick){
//                    glfwSetCursorPos(window, 512, 512);
//                    beginScene.camera->firstClick = false;
//                }
                beginScene.camera->MouseRotation(beginScene.cursor.x, beginScene.cursor.y);
            }
            beginScene.cursor.left = action == GLFW_RELEASE;
//            if (beginScene.cursor.left == GLFW_RELEASE){
//                beginScene.camera->firstClick = true;
//            }
        }
    }

    void onIdle() override {
        static auto time = (float) glfwGetTime();

        // Compute time delta
        float dt =  (float) glfwGetTime() - time;
        time = (float) glfwGetTime();
        // Set gray background
        glClearColor(.5f, .5f, .5f, 0);


        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        GLfloat fogColor[] = {0.5, 0.5, 0.5, 1};
//        glFogfv(GL_FOG_COLOR, fogColor);
//        glFogi(GL_FOG_MODE, GL_LINEAR);
//        glFogf(GL_FOG_START, 10.0f);
//        glFogf(GL_FOG_END, 20.0f);

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