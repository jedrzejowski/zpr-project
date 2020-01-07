/**
 * @file TextureReference.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "TextureReference.h"
#include "src/engine/Point.hpp"


engine::TexCoord engine::SquareTextureReference::getTexCoord_xy() const {
	return engine::TexCoord(start.x, start.y, no);
}

engine::TexCoord engine::SquareTextureReference::getTexCoord_Xy() const {
	return engine::TexCoord(end.x, start.y, no);
}

engine::TexCoord engine::SquareTextureReference::getTexCoord_xY() const {
	return engine::TexCoord(start.x, end.y, no);
}

engine::TexCoord engine::SquareTextureReference::getTexCoord_XY() const {
	return engine::TexCoord(end.x, end.y, no);
}
