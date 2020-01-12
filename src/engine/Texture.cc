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


TexturePtr Texture::create(const std::string &path) {
	struct Self : Texture {
	};

	TexturePtr self = std::make_shared<Self>();

	self->loadTexture(path);

	return self;
}


void Texture::loadTexture(const std::string &path) {

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// To jest aby tektury wygladały jak kwadratowe, czyli jak w minecrafcie
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

		if (number_of_channels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		if (number_of_channels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		logger(0).err("Failed to load texture from file:").enter().log(path);

		// w sumie gra nie powinna się wywalić jak nie wczyta textury
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