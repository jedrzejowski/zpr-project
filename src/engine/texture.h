#pragma once

#include <string>

#include "src/_classdef.h"
#include "src/opengl.h"
#include "src/lib/stb_image.h"

namespace engine {

	class Texture {
	private:
		GLuint texID;
		int width, height, nrChannels;

		void loadTexture(const std::string &path);

	public:
		Texture();

		explicit Texture(const std::string &path);

		void use(const int &num = 0) const;

		GLuint getID() const {
			return texID;
		}
	};

}

