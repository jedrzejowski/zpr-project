//
// Created by adam on 08.04.18.
//

#ifndef GKOM_ANIMATION_TEXTURE_H
#define GKOM_ANIMATION_TEXTURE_H

#include <string>
#include <GL/glew.h>
#include "../lib/stb_image.h"

using namespace std;

namespace gengine {

	class Texture {
	private:
		GLuint texID;
		int width, height, nrChannels;

		void loadTexture(string path);

	public:
		Texture();

		explicit Texture(const string &path);

		void use();

		GLuint getID() {
			return texID;
		}
	};

}


#endif //GKOM_ANIMATION_TEXTURE_H
