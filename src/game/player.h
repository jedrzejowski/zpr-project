#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"

namespace game {
	class Player : public Object {
	protected:
		engine::Camera camera;
	public:
		Player();

		void moveForward(double time);
		void moveBackward(double time);
		void moveLeft(double time);
		void moveRight(double time);
		void moveUp(double time);
		void moveDown(double time);

		void rotateUp(double dy);
		void rotateDown(double dy);
		void rotateLeft(double dx);
		void rotateRight(double dx);

		const engine::Camera& getCamera() const;
	};
}