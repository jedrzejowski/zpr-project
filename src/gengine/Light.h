//
// Created by adam on 19.04.18.
//

#ifndef GKOM_ANIMATION_LIGHT_H
#define GKOM_ANIMATION_LIGHT_H

#include <glm/vec3.hpp>

namespace gengine {

	class Light {
	public:

		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}


#endif //GKOM_ANIMATION_LIGHT_H
