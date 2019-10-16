#pragma once

#include <string>
#include <GL/glew.h>

#include "_classdef.h"
#include "src/lib/stb_image.h"

namespace gengine {

	class Texture {
	private:
		GLuint texID;
		int width, height, nrChannels;

		void loadTexture(const std::string &path);

	public:
		Texture();

		explicit Texture(const std::string &path);

		void use() const;

		GLuint getID() const {
			return texID;
		}
	};

}

