//
// Created by Mário Kolenič on 13/11/2021.
//
#include <iostream>
#include <ppgso.h>

using namespace std;
using namespace glm;
using namespace ppgso;

class SceneWindow : public Window {
public:
    SceneWindow() : Window{"Village", 1080, 1080} {
        //hideCursor();
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

        // Initialize OpenGL state
        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable polygon culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
    }
};

int main() {
    // Initialize our window
    SceneWindow window;

    // Main execution loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}