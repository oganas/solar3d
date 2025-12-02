#include "Skybox.h"
#include "Texture.h"

Skybox::Skybox() {}

Skybox::Skybox(const std::vector<std::string> &faces) {
	cubemapTexture = new Texture("skybox", faces);
	mesh = MeshPrimitives::cube();
}

void Skybox::draw() const {
	mesh.draw();
}
