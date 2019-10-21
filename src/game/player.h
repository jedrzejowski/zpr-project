#include "src/engine/Engine.h"
#include "src/_classdef.h"

namespace game {
	class Player {
	protected:
		engine::Point3D position;
	public:
		Player();

		const engine::Point3D& getPosition();
	};
}