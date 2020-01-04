#pragma once

#include <utility>
#include <vector>
#include <tuple>
#include <memory>

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

	typedef std::shared_ptr<Abs3DObj> Abs3DObjPtr;
	typedef std::weak_ptr<Abs3DObj> Abs3DObjWPtr;

	class Sub3DObj;

	typedef std::shared_ptr<Sub3DObj> Sub3DObjPtr;
	typedef std::weak_ptr<Sub3DObj> Sub3DObjWPtr;

	class Camera;

	class Light;

	class Resources;

	class Scene;

	typedef std::shared_ptr<Scene> ScenePtr;
	typedef std::weak_ptr<Scene> SceneWPtr;

	class Material;

	class ShaderProgram;

	class Texture;

	class Window;

	typedef std::shared_ptr<Window> WindowPtr;
	typedef std::weak_ptr<Window> WindowWPtr;

	class InputDevice;

	class InputButton;

	class KeyboardBtn;

	class Keyboard;

	typedef std::shared_ptr<Keyboard> KeyboardPtr;

	class MouseBtn;

	class Mouse;

	typedef std::shared_ptr<Mouse> MousePtr;

	class InputInterface;

	typedef std::shared_ptr<InputInterface> InputInterfacePtr;

	class FpsCounter;
}

namespace gui {
	class Interface;

	typedef std::shared_ptr<Interface> InterfacePtr;
	typedef std::weak_ptr<Interface> InterfaceWPtr;

	class InterfaceShader;

	class GuiObject;

	typedef std::shared_ptr<GuiObject> GuiObjectPtr;
	typedef std::weak_ptr<GuiObject> GuiObjectWPtr;

	class RectangleObj;

	typedef std::shared_ptr<RectangleObj> RectangleObjPtr;
	typedef std::weak_ptr<RectangleObj> RectangleObjWPtr;

	class Button;

	typedef std::shared_ptr<Button> ButtonPtr;

	class Text;

	typedef std::shared_ptr<Text> TextPtr;
	typedef std::weak_ptr<Text> TextWPtr;
}

namespace block {

	class Block;

	class SolidBlock;

	class Stone;

	class Dirt;
}

namespace map {
	class World;

	typedef std::shared_ptr<World> WorldPtr;
	typedef std::weak_ptr<World> WorldWPtr;

	class WorldRenderer;

	typedef std::shared_ptr<WorldRenderer> WorldRendererPtr;

	class Chunk;

	typedef std::shared_ptr<Chunk> ChunkPtr;

	class ChunkRenderer;

	typedef std::shared_ptr<ChunkRenderer> ChunkRendererPtr;
	typedef std::weak_ptr<ChunkRenderer> ChunkRendererWPtr;

	class ChunkGenerator;

	class ChunkLoader;

	typedef std::shared_ptr<ChunkLoader> ChunkLoaderPtr;
}

namespace game {
	class Player;

	typedef std::shared_ptr<Player> PlayerPtr;

	class MainWindow;

	class MainGame;
	typedef std::shared_ptr<MainGame> MainGamePtr;
	typedef std::weak_ptr<MainGame> MainGameWPtr;

	class PlayerInterface;

	class InGameMenu;
	typedef std::shared_ptr<InGameMenu> InGameMenuPtr;
	typedef std::weak_ptr<InGameMenu> InGameMenuWPtr;

	class GameScene;
	typedef std::shared_ptr<GameScene> GameScenePtr;
	typedef std::weak_ptr<GameScene> GameSceneWPtr;
}

namespace menu {
	class WelcomeScene;
	typedef std::shared_ptr<WelcomeScene> WelcomeScenePtr;
	typedef std::weak_ptr<WelcomeScene> WelcomeSceneWPtr;

	class SettingsScene;
	typedef std::shared_ptr<SettingsScene> SettingsScenePtr;
	typedef std::weak_ptr<SettingsScene> CSettingsSceneWPtr;

	class WorldScene;
	typedef std::shared_ptr<WorldScene> WorldScenePtr;
	typedef std::weak_ptr<WorldScene> WorldSceneWPtr;
}

#include "src/vars.h"
#include "src/logger.h"
#include "src/exception.h"
#include "src/lib/virtual_enable_shared_from_this.h"
