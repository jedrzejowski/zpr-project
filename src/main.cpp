#include "MainWindow.h"

int main(int argc, char *argv[]) {
	try {
		engine::Resources::setExecutablePath(argv[0]);

//		glm::vec2 baryPosition;
//		float distance;
//		auto was = glm::intersectRayTriangle(
//				glm::vec3(1, 1, 10),
//				glm::vec3(0, 0, -1),
//
//				glm::vec3(0, 0, 0),
//				glm::vec3(1000, 0, 0),
//				glm::vec3(0, 1000, 0),
//				baryPosition,
//				distance
//		);
//
//		logger.log(true).log(false).log(was).log(distance).log(baryPosition);




		auto window = std::make_shared<MainWindow>();
		window->open();

		return 0;
	} catch (ZprException &e) {
		logger.err(e.what());
	}
}