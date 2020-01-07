/**
 * @file Texture.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <string>

#include "src/_classdef.h"
#include "src/OpenGL.h"
#include "src/lib/stb_image.h"

namespace engine {

	class Texture {
	private:
		GLuint texID;
		int width = 0, height = 0, nrChannels = 0;

		void loadTexture(const std::string &path);

	public:
		Texture();

		explicit Texture(const std::string &path);

		void use(const int &num = 0) const;

		GLuint getID() const {
			return texID;
		}

		int getWidth() const;
		int getHeight() const;
		int getNrChannels() const;

		Color getColor(int x, int y);
	};
}
