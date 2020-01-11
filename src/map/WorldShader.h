/**
 * @file WorldShader.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <src/engine/Engine.h>

namespace map {

	class WorldShader : public engine::Shader {
	private:
		const engine::Texture *block_texture = nullptr;
	public:
		explicit WorldShader();

		void setCamera(const engine::Camera &camera);

		void setProjection(const glm::mat4 &mat);

		void setChunkPos(const glm::mat4 &mat);

		void bind() override;
	};
}
