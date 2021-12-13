#include <iostream>
#include <ppgso.h>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

#include "ground.h"
#include "scene.h"
#include "sky.h"
#include "cube.h"
#include "mill.h"
#include "camera.h"
#include "campfire.h"
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
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
        camera->position.z = -25.0f;
//        camera->orientation.y = ppgso::PI/4;
        camera->position.y = 1;
        beginScene.camera = move(camera);

        beginScene.objects.push_back(std::make_unique<Sky>());

        // Create a ground
        beginScene.objects.push_back(std::make_unique<Ground>());

        auto horse = std::make_unique<Horse>();
        beginScene.objects.push_back(move(horse));

        //auto walls = std::make_unique<Walls>();
        // beginScene.objects.push_back(move(walls));
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

        // Set gray background
        glClearColor(.5f, .5f, .5f, 0);

        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        auto cameraMat = translate(glm::mat4{1.0f}, {0.0f, -15.0f, -50});
//        program.setUniform("ViewMatrix", glm::lookAt({cos((float) glfwGetTime())* 75,75.0f,sin((float) glfwGetTime())*-75.0f},{0.0f,1.0f,0.0f},glm::vec3{0.0f,1,0.0f}));
//        program.setUniform("ProjectionMatrix",  beginScene.camera->projectionMatrix);
//        program.setUniform("ViewMatrix", beginScene.camera->viewMatrix);


        // Update and render all objects
        beginScene.update();
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