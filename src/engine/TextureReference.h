/**
 * @file TextureReference.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "_classdef.h"
#include "src/lib/Coord.hpp"
#include "src/OpenGL.h"

namespace engine {
	struct SquareTextureReference {
		glm::vec2 start;
		glm::vec2 end;
		uint32_t no;

		SquareTextureReference() = default;

		SquareTextureReference(const glm::vec2 &start, const glm::vec2 &end, uint32_t no) :
				start(start), end(end), no(no) {}

		[[nodiscard]] engine::TexCoord getTexCoord_xy() const;
		[[nodiscard]] engine::TexCoord getTexCoord_Xy() const;
		[[nodiscard]] engine::TexCoord getTexCoord_xY() const;
		[[nodiscard]] engine::TexCoord getTexCoord_XY() const;
	};
}


