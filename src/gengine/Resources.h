#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


namespace gengine {
	class Resources {
	private:
		std::vector<std::string> roots;

		Resources() {

		}
	public:

		std::string absPath(std::string& path){
			return "/home/adam/Programowanie/studia/zpr-project/" + path;
		}

		void load(std::string path){

		}

		std::string loadTextFile(std::string path){
			std::ifstream file;
			file.exceptions(std::ifstream::badbit);
			file.open(this->absPath(path));
			std::stringstream shader_stream;
			shader_stream << file.rdbuf();
			file.close();
			return shader_stream.str();
		}

		static Resources &get() {
			static Resources resources;
			return resources;
		}
	};
}
