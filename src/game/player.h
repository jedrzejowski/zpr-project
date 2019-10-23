#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"

namespace game {
	class Player : public Object {
	protected:
		glm::vec3 position;
		float angleV = 0, angleH = 0;
		float mousePrecision = 20;
		float keyboardPrecision = 20;

		glm::vec3 topVec() const;
		glm::vec3 frontVec() const;
		glm::vec3 leftVec() const;

	public:
		Player();

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

		engine::Camera getCamera() const;
	};
}