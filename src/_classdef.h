#pragma once

#include <utility>
#include <vector>
#include <tuple>

template<typename... Args>
class Signal;

class Object;

class BackWorkerQueue;

class JsonFile;

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

	class ShaderProgram;

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

	class InterfaceShader;

	class GuiObject;

	class RectangleObj;

	class Button;

	class Text;
}

namespace block {

	class Block;

	class SolidBlock;

	class Stone;

	class Dirt;
}

namespace map {
	class World;

	class WorldRenderer;

	class Chunk;

	class ChunkRenderer;

	class ChunkGenerator;

	class ChunkLoader;
}

namespace game {
	class Player;

	class MainWindow;

	class MainGame;

	class PlayerInterface;

	class InGameMenu;

	class GameScene;
}

namespace menu {
	class WelcomeScene;

	class SettingsScene;

	class WorldssScene;
}


#include "src/logger.h"
#include "src/exception.h"
