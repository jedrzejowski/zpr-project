#pragma once

#include <src/engine/Engine.h>

namespace map {

	class WorldShader : public engine::Shader {

	public:
		explicit WorldShader();
		glm::vec2 getPointInWindow(const glm::vec3 &vec) override;

		void setCamera(const engine::Camera& camera);

		void setProjection(const glm::mat4& mat);

		void setChunkPos(const glm::mat4& mat);
	};
}
