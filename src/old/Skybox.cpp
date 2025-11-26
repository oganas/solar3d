#include "../include/Skybox.h"
#include "../include/GLFW/WrapperGLFW.h"
#include "../include/MeshFactory.h"
#include "../include/TextureManager.h"

Skybox::Skybox(GLWrapper *glw, const std::vector<std::string> &faces) {

  program = glw->loadShader("shaders/skybox.vert", "shaders/skybox.frag");

  viewId = glGetUniformLocation(program, "view");
  projectionId = glGetUniformLocation(program, "projection");
  samplerId = glGetUniformLocation(program, "skybox");

  cubeMesh = createCube();
  cubemapTexture = gTextureManager.loadCubemap(faces);
}

void Skybox::render(const glm::mat4 &view, const glm::mat4 &projection) {
  glDepthFunc(GL_LEQUAL);

  glUseProgram(program);

  glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));
  glUniformMatrix4fv(viewId, 1, GL_FALSE, &viewNoTranslation[0][0]);
  glUniformMatrix4fv(projectionId, 1, GL_FALSE, &projection[0][0]);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
  glUniform1i(samplerId, 0);

  cubeMesh.draw();

  glDepthFunc(GL_LESS);
}
