#include "Engine.h"
#include "Input.h"
#include "Mesh.h"
#include "Object.h"
#include "Shader.h"
#include "Window.h"

#include <chrono>
#include <iostream>

using namespace glm;

/*
class App : public Engine {
public:
  void start() override {
                loadShader("shader", "shaders/vs.vert", "shaders/fs.frag");
    setWindowBackgroundColour(0.2f, 0.3f, 0.4f, 1.0f);


  }

  void update(float dt) override {
    if (isKeyDown(Key::SPACE)) {
      std::cout << "Jump!\n";
                        setWindowBackgroundColour(0.0f, 0.0f, 0.0f, 1.0f);
    }
  }
};

int main() {
  App simulation;
  simulation.run(1280, 720, "solar system");
}
*/

Window w(1280, 720, "solar system");
Input i(w);

GLuint modelId = 0, viewId = 0, projectionId = 0;

Shader s("shaders/vs.vert", "shaders/fs.frag");
Object cube;

// render logic
void render(Window *window) {
  s.bind();

  float aspect = (float)w.getWidth() / (float)w.getHeight();
  glm::mat4 projection =
      glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

  s.setUniform("projection", projection);

  glm::mat4 view =
      glm::lookAt(glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f));

  s.setUniform("view", view);

  cube.draw(s);

  s.unbind();
}

// init logic
void start() {
  w.setRenderCallback(render);

  modelId = glGetUniformLocation(s.getId(), "model");
  viewId = glGetUniformLocation(s.getId(), "view");
  projectionId = glGetUniformLocation(s.getId(), "projection");

  Mesh cubeMesh = MeshPrimitives::cube();

  cube = Object("cube", cubeMesh);
  cube.transform.position = vec3(0.0f, 0.0f, 0.0f);
}

// program logic
void update(float dt) {
  if (i.isKeyPressed(Key::SPACE)) {
    std::cout << "Jump!\n";
    w.setBackgroundColour(1.0f, 0.0f, 0.0f, 1.0f);
  }
}

int main() {
  start();

  auto last = std::chrono::high_resolution_clock::now();

  while (w.update()) {
    i.update();

    auto now = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(now - last).count();
    last = now;

    update(dt);

    i.endFrame();
  }
}
