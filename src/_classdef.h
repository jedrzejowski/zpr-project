#pragma once

#include <utility>
#include <vector>
#include <tuple>

template<typename... Args>
class Signal;

class SignalObj;

class TreeObj;

class Object;

namespace engine {
	class exception;

	struct Point3DeX;
	struct Point3D;
	struct Normal;
	struct Color;
	struct TexCoord;
	struct SimpleTriangle;

	class abs3DObj;

	class camera;

	class Light;

	class Resources;

	class Scene;

	class Material;

	class Shader;

	class Texture;

	class Window;

	class Key;

	class Keyboard;
}

namespace block {
	struct cord3D {
		uint16_t x, y, z;

		cord3D() : x(0), y(0), z(0) {}
		cord3D(uint16_t x, uint16_t y, uint16_t z) : x(x), y(y), z(z) {}
		bool operator<(const cord3D &sec) const {
			return toInt64() < sec.toInt64();
		}
		int64_t toInt64() const {
			int64_t out = x;
			out = out << 16;
			out = out | y;
			out = out << 16;
			out = out | z;
			return out;
		}
	};

	struct cord2D {
		uint16_t x, y;

		cord2D() : x(0), y(0) {}
		cord2D(uint16_t x, uint16_t y) : x(x), y(y) {}
		bool operator<(const cord2D &sec) const {
			return (x < sec.x) && (y < sec.y);
		}
	};

	class Block;

	class SolidBlock;

	class Stone;
}

namespace map {
	typedef std::pair<int, int> ChunkPos;

	class Chunk;

	class Map;

	class Renderer;

	class ChunkRenderer;
}

namespace game {
	class Player;

	class MainWindow;

	class GameScene;
}

#include "src/logger.h"
