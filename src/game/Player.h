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
		float keyboardPrecision = 2;
		CoordDim chunkRenderDistance = 4, chunkUnloadDistance = 6;

		glm::vec3 topVec() const;
		glm::vec3 frontVec() const;
		glm::vec3 leftVec() const;

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

		float getChunkRenderDistance() const;
		float getChunkUnloadDistance() const;
		block::FullPosition getFullPosition() const;

		engine::Camera getCamera() const;
	};
}