// Playground
// - You can use this template project for quick C++ experiments

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

const unsigned int SIZE = 1024;
class MeshWindow : public ppgso::Window {
private:
    // Initialize resources

    ppgso::Shader program = {texture_vert_glsl, texture_frag_glsl};
    ppgso::Texture vrtula_texture = {ppgso::image::loadBMP("Material_baseColor.bmp")};
    ppgso::Texture base_texture = {ppgso::image::loadBMP("base.bmp")};
    ppgso::Texture ground_texture = {ppgso::image::loadBMP("ground.bmp")};

    ppgso::Mesh cube = {"cube.obj"};
    ppgso::Mesh vrtula = {"vrtula.obj"};
    ppgso::Mesh mill_base = {"mill_base.obj"};

    int speed = 1;

public:
    MeshWindow() : Window{"Village", SIZE, SIZE} {

        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable polygon culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
    }

    void onKey(int key, int scanCode, int action, int mods) override {

        if (key == GLFW_KEY_W)
        {
            speed += 1;
        }
        if (key == GLFW_KEY_S)
        {
            speed -= 1;
        }
    }
    void onIdle() override {

        // Set gray background
        glClearColor(.5f, .5f, .5f, 0);

        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        auto floor = glm::translate(glm::mat4{1.0f}, {0.0f, 1.25f, 0.0f}) * glm::scale(glm::mat4{1}, {1000,0.1,1000});

        program.setUniform("ModelMatrix", floor);
        program.setUniform("Texture", ground_texture);
        cube.render();

        auto mill = glm::scale(glm::mat4{1}, {.1,.1,.1});
        auto vrt = glm::translate(glm::mat4{1.0f}, {5.0f, 30.0f, 0.0f}) * glm::rotate(glm::mat4{1}, (float) glfwGetTime() * speed, {1.0f, 0.0f, 0.0f}) *
                   glm::scale(glm::mat4{1}, {.1,.1,.1});
        auto cameraMat = translate(glm::mat4{1.0f}, {0.0f, -15.0f, -50});



//        program.setUniform("ViewMatrix", glm::lookAt({cos((float) glfwGetTime())* 75,75.0f,sin((float) glfwGetTime())*-75.0f},{0.0f,1.0f,0.0f},glm::vec3{0.0f,1,0.0f}));
        program.setUniform("ViewMatrix", glm::lookAt({100 * sin ((float) glfwGetTime()/5),cos((float) glfwGetTime()*5)*0.2f + 5.0f,-75.0f},{0.0f,1.0f,0.0f},glm::vec3{0.0f,1,0.0f}));

//        program.setUniform("ViewMatrix", cameraMat);
        program.setUniform("ProjectionMatrix", glm::perspective((ppgso::PI / 180.f) * 60.0f, 1.0f, 0.1f, 250.0f));

        program.setUniform("ModelMatrix", mill);
        program.setUniform("Texture", base_texture);
        mill_base.render();

        program.setUniform("ModelMatrix", vrt);
        program.setUniform("Texture", vrtula_texture);
        vrtula.render();

    }


};

int main() {
    // Create instance of our mesh window
    MeshWindow window;

    // Poll events in loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}