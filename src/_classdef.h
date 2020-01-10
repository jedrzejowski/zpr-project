/**
 * @file _classdef.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <utility>
#include <vector>
#include <tuple>
#include <memory>
#include "lib/json.hpp"

using json = nlohmann::json;

template<typename... Args>
class Signal;

class Object;

typedef std::shared_ptr<Object> ObjectPtr;
typedef std::weak_ptr<Object> ObjectWPtr;

class BackWorkerQueue;

class JsonFile;

class AppSettings;

class SavableObject;

namespace engine {
	class exception;

	struct Point3DeX;
	struct Point3D;
	struct Normal;
	struct Color;
	struct TexCoord;
	struct EboTriangle;

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

	typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
	typedef std::weak_ptr<ShaderProgram> ShaderProgramWPtr;

	class Shader;

	typedef std::shared_ptr<Shader> ShaderPtr;
	typedef std::weak_ptr<Shader> ShaderWPtr;

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
	typedef std::weak_ptr<InputInterface> InputInterfaceWPtr;

	class FpsCounter;

	struct SquareTextureReference;
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
	typedef std::weak_ptr<Button> ButtonWPtr;

	class Text;

	typedef std::shared_ptr<Text> TextPtr;
	typedef std::weak_ptr<Text> TextWPtr;
}

namespace block {

	typedef uint32_t BlockTypeId;

	class Block;

	typedef std::shared_ptr<Block> BlockPtr;
	typedef std::weak_ptr<Block> BlockWPtr;

	class Factory;

	class FullPosition;
	// NIE ROBIĆ SMART POINTERÓW

	class SolidBlock;

	typedef std::shared_ptr<SolidBlock> SolidBlockPtr;
	typedef std::weak_ptr<SolidBlock> SolidBlockWPtr;

	class Stone;

	class Dirt;

	class Water;

	class Sand;

	class Grass;

	class Brick;

	class Cobblestone;

	class TreeLog;

	class Wood;

	class Leaf;
}

namespace map {
	class World;

	typedef std::shared_ptr<World> WorldPtr;
	typedef std::weak_ptr<World> WorldWPtr;

	class WorldRenderer;

	typedef std::shared_ptr<WorldRenderer> WorldRendererPtr;
	typedef std::weak_ptr<WorldRenderer> WorldRendererWPtr;

	class WorldShader;

	typedef std::shared_ptr<WorldShader> WorldShaderPtr;
	typedef std::weak_ptr<WorldShader> WorldShaderWPtr;

	class Chunk;

	typedef std::shared_ptr<Chunk> ChunkPtr;
	typedef std::weak_ptr<Chunk> ChunkWPtr;

	class ChunkRenderer;

	typedef std::shared_ptr<ChunkRenderer> ChunkRendererPtr;
	typedef std::weak_ptr<ChunkRenderer> ChunkRendererWPtr;

	class ChunkGenerator;
	// NIE ROBIĆ SMART POINTERÓW

	class ChunkLoader;
	// NIE ROBIĆ SMART POINTERÓW
}

namespace game {
	class Player;

	typedef std::shared_ptr<Player> PlayerPtr;
	typedef std::weak_ptr<Player> PlayerWPtr;

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

	class PlayerInterface;

	typedef std::shared_ptr<PlayerInterface> PlayerInterfacePtr;
	typedef std::weak_ptr<PlayerInterface> PlayerInterfaceWPtr;

	class PlayerItem;

	typedef std::shared_ptr<PlayerItem> PlayerItemPtr;
	typedef std::weak_ptr<PlayerItem> PlayerItemWPtr;

	class PlayerSolidBlockItem;

	typedef std::shared_ptr<PlayerSolidBlockItem> PlayerBlockItemPtr;
	typedef std::weak_ptr<PlayerSolidBlockItem> PlayerBlockItemWPtr;
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

#include "src/Vars.h"
#include "src/Logger.h"
#include "src/Exception.hpp"
#include "src/lib/VirtualSharePtrObject.hpp"
