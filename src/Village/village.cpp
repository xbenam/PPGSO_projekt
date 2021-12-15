#include <iostream>
#include <ppgso.h>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

#include "ground.h"
#include "scene.h"
#include "sky.h"
#include "mill.h"
#include "campfire.h"
#include "horse.h"
#include "walls.h"
#include "house.h"
#include "tree.h"
#include "oak.h"
#include "axe.h"
#include "blackScreen.h"

using namespace std;
using namespace glm;
using namespace ppgso;

class SceneWindow : public Window {
private:
    Scene beginScene;
    ppgso::Shader program = {texture_vert_glsl, texture_frag_glsl};

    std::vector<glm::vec3> generateTreePositions(int treeCount) {
        std::vector<glm::vec3> treePositions;
        bool founded;
        for(int i = 0; i < treeCount; i++) {
            founded = false;
            int randX = (rand() % 100) - 50;
            int randZ = (rand() % 100) - 50;
            if(randX < 30 && randX > -20 && randZ < 40) {
                i--;
                continue;
            }
            glm::vec3 newPoint = {(float)randX, 0, (float)randZ};
            for(size_t j = 0; j < treePositions.size(); j++) {
                if(newPoint.x < (treePositions[j].x + 5) && newPoint.x > (treePositions[j].x - 5) &&
                   newPoint.z < (treePositions[j].z + 5) && newPoint.z > (treePositions[j].z - 5)) {
                    i--;
                    founded = true;
                    break;
                }
            }
            if(!founded)
                treePositions.push_back(newPoint);
        }
        return treePositions;
    }

    void initScene() {
        beginScene.objects.clear();

        // Create a camera
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
        camera->position.z = -25.0f;
        camera->position.y = 1;
        beginScene.camera = move(camera);

        beginScene.objects.push_back(std::make_unique<Sky>());

        beginScene.objects.push_back(std::make_unique<BlackScreen>());

        // Create a ground
        beginScene.objects.push_back(std::make_unique<Ground>());

        auto walls = std::make_unique<Walls>();
        beginScene.objects.push_back(move(walls));

//        auto flag = std::make_unique<Flag>();
//        beginScene.objects.push_back(move(flag));

        glm::vec3 housePoistions[5] = {{4, 0, 5}, {4, 0, 11}, {3, 0, 17}, {-4, 0, 15}, {-4, 0, 7}};
        glm::vec3 houseRotations[5] = {{0, 0, 0}, {0, 0, 0}, {0, 0, -(ppgso::PI/4)}, {0, 0, -(ppgso::PI/2)}, {0, 0, ppgso::PI}};
        for(int i = 0; i < 5; i++) {
            auto house = std::make_unique<House>();
            house->position = housePoistions[i];
            house->rotation = houseRotations[i];
            beginScene.objects.push_back(move(house));
        }

        std::vector<glm::vec3> treePositions = generateTreePositions(70);
        for(size_t i = 0; i < treePositions.size(); i++) {
            auto tree = std::make_unique<Tree>();
            tree->position = treePositions[i];
            beginScene.objects.push_back(move(tree));
        }

        auto oak = std::make_unique<Oak>();
        oak->position.x += 15.5f;
        oak->position.z += 1.55f;
        oak->scale *= 0.5f;
        beginScene.objects.push_back(move(oak));

        auto mill = std::make_unique<Mill>();
        mill->position.x += 20.0f;
        mill->position.z += 9.0f;
        mill->rotation.z += ppgso::PI;
        mill->scale *= 0.5f;
        beginScene.objects.push_back(move(mill));

        auto campfire = std::make_unique<Campfire>();
        campfire->position.x += 17.0f;
        campfire->position.z += 9.0f;
        campfire->position.y += 0.2f;
        campfire->scale *= 0.5f;
        beginScene.objects.push_back(move(campfire));

        auto axe = std::make_unique<Axe>();
        axe->position.x += 16.0f;
        axe->position.y += 0.5f;
        axe->position.z += 28.0f;
        axe->rotation.y += ppgso::PI/2;
        beginScene.objects.push_back(move(axe));
    }
public:
    SceneWindow() : Window{"Village", 1024, 960} {

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
        static auto time = (float) glfwGetTime();

        // Compute time delta
        float dt = (float) glfwGetTime() - time;
        time = (float) glfwGetTime();

        // Set gray background
        glClearColor(.5f, .5f, .5f, 0);

        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//        auto cameraMat = translate(glm::mat4{1.0f}, {0.0f, -15.0f, -50});
//        program.setUniform("ViewMatrix", glm::lookAt({cos((float) glfwGetTime())* 75,75.0f,sin((float) glfwGetTime())*-75.0f},{0.0f,1.0f,0.0f},glm::vec3{0.0f,1,0.0f}));
//        program.setUniform("ProjectionMatrix",  beginScene.camera->projectionMatrix);
//        program.setUniform("ViewMatrix", beginScene.camera->viewMatrix);

        if(!beginScene.camera->cameraAroundVillage && !beginScene.camera->wasSet) {
            auto horse = std::make_unique<Horse>();
            beginScene.objects.push_back(move(horse));
            beginScene.camera->wasSet = true;
        }

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