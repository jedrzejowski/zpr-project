#pragma once

#include <utility>
#include <vector>
#include <tuple>

template<typename... Args>
class Signal;

class Object;

namespace engine {
	class exception;

	struct Point3DeX;
	struct Point3D;
	struct Normal;
	struct Color;
	struct TexCoord;
	struct SimpleTriangle;

	class Abs3DObj;

	class Camera;

	class Light;

	class Resources;

	class Scene;

	class Material;

	class Shader;

	class Texture;

	class Window;

	class InputDevice;

	class InputButton;

	class KeyboardBtn;

	class Keyboard;

	class MouseBtn;

	class Mouse;

	class InputInterface;

	class FpsCounter;
}

namespace gui {
	class Interface;

	class GuiObject;

	class RectangleObj;

	class Button;
}

namespace block {

	class Block;

	class SolidBlock;

	class Stone;
}

namespace map {
	class Chunk;

	class WorldMap;

	class Renderer;

	class ChunkRenderer;

	class ChunkGenerator;
}

namespace game {
	class Player;

	class MainWindow;

	class MainGame;

	class PlayerInterface;

	class InGameMenu;

	class GameScene;
}

struct coord3D {
	int64_t x, y, z;

	coord3D() : x(0), y(0), z(0) {}
	coord3D(int64_t x, int64_t y, int64_t z) : x(x), y(y), z(z) {}
	bool operator<(const coord3D &sec) const {
		if (x < sec.x) return true;
		if (x > sec.x) return false;

		if (y < sec.y) return true;
		if (y > sec.y) return false;

		return z < sec.z;
	}
};

struct coord2D {
	int64_t x, y;

	coord2D() : x(0), y(0) {}
	coord2D(int64_t x, int64_t y) : x(x), y(y) {}
	bool operator<(const coord2D &sec) const {
		if (x < sec.x) return true;
		if (x > sec.x) return false;
		return y < sec.y;
	}
};

#include "src/logger.h"
#include "src/exception.h"
