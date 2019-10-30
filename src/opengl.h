#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/normal.hpp>


inline std::ostream &operator<<(std::ostream &out, const glm::vec2 &g) {
	return out << glm::to_string(g);
}

inline std::ostream &operator<<(std::ostream &out, const glm::vec3 &g) {
	return out << glm::to_string(g);
}

inline std::ostream &operator<<(std::ostream &out, const glm::vec4 &g) {
	return out << glm::to_string(g);
}

inline std::ostream &operator<<(std::ostream &out, const glm::mat4 &g) {
	return out << glm::to_string(g);
}