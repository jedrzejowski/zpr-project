/**
 * @file Resources.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Resources.h"
#include "Texture.h"

std::filesystem::path executablePath;

std::filesystem::path engine::Resources::absPath(const std::string &path) {
	return executablePath / "res" / path;
}

std::string engine::Resources::loadTextFile(std::string path) {
	path = absPath(path).string();

	std::ifstream file(path);

	if (!file.is_open())
		throw FileInputException(path);

	std::stringstream shader_stream;
	shader_stream << file.rdbuf();
	file.close();
	return shader_stream.str();
}

engine::Resources &engine::Resources::get() {
	static Resources resources;
	return resources;
}

engine::TexturePtr engine::Resources::getTexture(std::string path) {
	path = absPath(path).string();

	if (textures.count(path))
		return textures[path];

	return textures[path] = Texture::create(path);
}

void engine::Resources::setExecutablePath(char *path) {
	executablePath = std::filesystem::absolute(path).parent_path();
}
