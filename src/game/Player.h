/**
 * @file Player.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "src/_classdef.h"
#include "src/lib/Coord.hpp"
#include "src/lib/Object.h"
#include "src/lib/SavableObject.h"
#include "src/engine/Engine.h"
#include "src/block/FullPosition.h"

namespace game {

	/**
	 * @brief Obiekt gracza
	 *
	 * Implementuje ruchy gracza oraz znajduje bloki na które trzeba ustawić nowy block
	 */
	class Player : public Object, public SavableObject {
	protected:
		map::WorldPtr world_map_ptr;
		glm::vec3 position;

		float eye_angle_vertical, eye_angle_horizontal;
		float mouse_precision, keyboard_precision;

		[[nodiscard]] glm::vec3 topVec() const;
		[[nodiscard]] glm::vec3 frontVec() const;
		[[nodiscard]] glm::vec3 leftVec() const;

		explicit Player(map::WorldPtr &world_map_ptr);

		void initWithDefaultValues();
	public:
		static PlayerPtr create(map::WorldPtr &world_map_ptr);
		~Player();

		void moveForward(float time);
		void moveBackward(float time);
		void moveLeft(float time);
		void moveRight(float time);
		void moveUp(float time);
		void moveDown(float time);

		void rotateHeadUp(float dy);
		void rotateHeadDown(float dy);
		void rotateHeadLeft(float dx);
		void rotateHeadRight(float dx);

		[[nodiscard]] float getChunkRenderDistance() const;
		[[nodiscard]] float getChunkUnloadDistance() const;
		[[nodiscard]] block::FullPosition getFullPosition() const;

		[[nodiscard]] engine::Camera getCamera() const;


		//region SavableObject
	public:
		std::filesystem::path getSavePath() const override;
		json toJSON() const override;
	protected:
		void acceptState(json &json_obj) override;
		//endregion

		//region Block Pointing
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
		//endregion
	};
}