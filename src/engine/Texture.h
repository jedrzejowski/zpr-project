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
		GLuint texture_id;
		int width = 0, height = 0, number_of_channels = 0;

		void loadTexture(const std::string &path);

		Texture();
	public:
		static TexturePtr create(const std::string &path);

		void use(const int &num = 0) const;

		[[nodiscard]] GLuint getID() const {
			return texture_id;
		}

		[[nodiscard]] int getWidth() const;
		[[nodiscard]] int getHeight() const;
		[[nodiscard]] int getNrChannels() const;

		Color getColor(int x, int y);
	};
}

