#include "Resources.h"
#include "Texture.h"

boost::filesystem::path executablePath;

boost::filesystem::path engine::Resources::absPath(const std::string &path) {
	return executablePath / "res" / path;
}

void engine::Resources::load(std::string &path) {
}

std::string engine::Resources::loadTextFile(const std::string &path) {

	logger.log("engine::Resources::loadTextFile loading \"" + path + "\"");

	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	file.open(absPath(path).string());
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
	path = absPath(path).string();

	if (textures.count(path))
		return textures[path];

	return textures[path] = new Texture(path);
}

void engine::Resources::setExecutablePath(char *path) {
	executablePath = boost::filesystem::system_complete(path).parent_path();
}
