/**
 * @file Texture.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#define STB_IMAGE_IMPLEMENTATION

#include "src/Exception.hpp"
#include "Texture.h"
#include "Resources.h"
#include "Point.hpp"
#include "ShaderProgram.h"

using namespace engine;

Texture::Texture() = default;

Texture::Texture(const std::string &path) {
	loadTexture(path);
}

void Texture::loadTexture(const std::string &path) {

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// To jest aby tektury wygladały jak kwadratowe, czyli jak w MC
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// To jest aby nie było lini pomiędzy dwoma tekturami
	// https://community.khronos.org/t/2d-texture-problem-lines-between-textures/57809
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	auto data = stbi_load(path.c_str(),
						  &width, &height, &number_of_channels, 0);

	if (data) {
		logger(1).log(path).log(number_of_channels);

		if (number_of_channels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		if (number_of_channels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		logger(1).warn("Texture::loadTexture()").log("failed to load texture from path").log(path);
//		throw zprException("Texture::loadTexture", "failed to load texture");
	}

	stbi_image_free(data);
}

void Texture::use(const int &num) const {
	glActiveTexture(GL_TEXTURE0 + num);
	glBindTexture(GL_TEXTURE_2D, getID());
}

int Texture::getWidth() const {
	return width;
}

int Texture::getHeight() const {
	return height;
}

int Texture::getNrChannels() const {
	return number_of_channels;
}

Color Texture::getColor(int x, int y) {
	return Color();
}
