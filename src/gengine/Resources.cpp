
#include <src/logger.h>
#include "Resources.h"
#include "Texture.h"

std::string gengine::Resources::absPath(const std::string &path) {
	return "/home/adam/Programowanie/studia/zpr-project/res/" + path;
}

void gengine::Resources::load(std::string &path) {
}

std::string gengine::Resources::loadTextFile(const std::string &path) {\
	Logger::get().log("gengine::Resources::loadTextFile loading \"" + path +"\"");

	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	file.open(this->absPath(path));
	std::stringstream shader_stream;
	shader_stream << file.rdbuf();
	file.close();
	return shader_stream.str();
}

gengine::Resources &gengine::Resources::get() {
	static Resources resources;
	return resources;
}

const gengine::Texture *gengine::Resources::getTexture(std::string path) {
	path = absPath(path);

	if (textures.count(path))
		return textures[path];

	return textures[path] = new Texture(path);
}
