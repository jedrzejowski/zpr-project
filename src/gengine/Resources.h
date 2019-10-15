#pragma once

#include <vector>
#include <string>

namespace gengine {
	class Resources {
	private:
		std::vector<std::string> roots;

		Resources() {

		}
	public:

		void load(std::string path){

		}

		static Resources &get() {
			static Resources resources;
			return resources;
		}
	};
}
