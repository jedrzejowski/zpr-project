/**
 * @file Player.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "src/_classdef.h"
#include "src/lib/Coord.hpp"
#include "src/engine/Engine.h"
#include "src/lib/Object.hpp"

namespace game {
	class Player : public Object {
	protected:
		map::WorldPtr world;
		glm::vec3 position;

		float angleV = 0, angleH = 0;
		float mousePrecision = 20;
		float keyboardPrecision = 10;
		CoordDim chunkRenderDistance = 4, chunkUnloadDistance = 6;

		[[nodiscard]] glm::vec3 topVec() const;
		[[nodiscard]] glm::vec3 frontVec() const;
		[[nodiscard]] glm::vec3 leftVec() const;

	public:
		explicit Player();

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
	};
}