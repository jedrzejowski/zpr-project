
#include <src/logger.h>
#include "resources.h"
#include "texture.h"

std::string engine::Resources::absPath(const std::string &path) {
	return "/home/adam/Programowanie/studia/zpr-project/res/" + path;
}

void engine::Resources::load(std::string &path) {
}

std::string engine::Resources::loadTextFile(const std::string &path) {\
	logger.log("engine::Resources::loadTextFile loading \"" + path +"\"");

	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	file.open(this->absPath(path));
	std::stringstream shader_stream;
	shader_stream << file.rdbuf();
	file.close();
	return shader_stream.str();
}

engine::Resources &engine::Resources::get() {
	static Resources resources;
	return resources;
}

const engine::Texture *engine::Resources::getTexture(std::string path) {
	path = absPath(path);

	if (textures.count(path))
		return textures[path];

	return textures[path] = new Texture(path);
}
