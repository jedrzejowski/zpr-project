//
// Created by adam on 08.04.18.
//

#define STB_IMAGE_IMPLEMENTATION

#include "exception.h"
#include "texture.h"
#include "resources.h"

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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	auto data = stbi_load(path.c_str(),
						  &width, &height, &nrChannels, 0);

	if (data) {

		if (nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		throw exception("Failed to load texture");

	stbi_image_free(data);
}

void Texture::use(const int &num) const {
	glActiveTexture(GL_TEXTURE0 + num);
	glBindTexture(GL_TEXTURE_2D, getID());
}
