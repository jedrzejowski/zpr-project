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
		engine::TexturePtr block_texture;
	public:
		explicit WorldShader();

		void setCamera(const engine::Camera &camera);

		void setProjection(const glm::mat4 &mat);
		void updateProjection(const engine::WindowPtr &window_ptr);

		void setChunkPos(const glm::mat4 &mat);

		void bind() override;
	};
}
