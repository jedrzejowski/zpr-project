#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"

namespace game {
	class Player : public Object {
	protected:
		engine::camera camera;
	public:
		Player();

		void moveForward(double time);
		void moveBackward(double time);
		void moveLeft(double time);
		void moveRight(double time);
		void moveUp(double time);
		void moveDown(double time);

		const engine::camera& getCamera() const;
	};
}