/**
 * @file Player.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "src/_classdef.h"
#include "src/lib/Coord.hpp"
#include "src/engine/Engine.h"
#include "src/lib/Object.hpp"
#include "src/block/FullPosition.h"

namespace game {
	class Player : public Object {
	protected:
		game::MainGameWPtr main_game;
		glm::vec3 position;

		float eye_angle_vertical, eye_angle_horizontal;
		float mouse_precision, keyboard_precision;
		CoordDim chunk_render_distance, chunk_unload_distance;

		[[nodiscard]] glm::vec3 topVec() const;
		[[nodiscard]] glm::vec3 frontVec() const;
		[[nodiscard]] glm::vec3 leftVec() const;

		explicit Player(game::MainGamePtr &main_game);

		void initWithDefaultValues();
	public:

		static PlayerPtr create(MainGamePtr &main_game);

		void moveForward(float time);
		void moveBackward(float time);
		void moveLeft(float time);
		void moveRight(float time);
		void moveUp(float time);
		void moveDown(float time);

		void rotateUp(float dy);
		void rotateDown(float dy);
		void rotateLeft(float dx);
		void rotateRight(float dx);

		[[nodiscard]] float getChunkRenderDistance() const;
		[[nodiscard]] float getChunkUnloadDistance() const;
		[[nodiscard]] block::FullPosition getFullPosition() const;

		[[nodiscard]] engine::Camera getCamera() const;

		//#region Block Pointing
	private:
		mutable bool need_block_point_calculate = true;
		mutable block::FullPosition pointing_block_position;
		mutable block::FullPosition new_block_position;
		mutable bool is_pointing_block = false;

		void recalculateBlockPointing() const;

	public:
		void resetBlockPointing();
		const block::FullPosition &getPointingBlockPosition() const;
		const block::FullPosition &getNewBlockPosition() const;
		bool isPointingBlock() const;
		//#endregion
	};
}