#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"

namespace game {
	class Player : public Object {
	protected:
		engine::camera camera;
	public:
		Player();

		void moveForward(float distance);
		void moveBackward(float distance);
		void moveLeft(float distance);
		void moveRight(float distance);
		void moveUp(float distance);
		void moveDown(float distance);

		const engine::camera& getCamera() const;
	};
}