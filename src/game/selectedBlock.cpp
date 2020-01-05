#include "selectedBlock.h"
#include "mainGame.h"
#include "player.h"

game::SelectedBlock::SelectedBlock(MainGamePtr &mainGame) :
		mainGame(mainGame) {
	logger.constructor(this);
}

game::SelectedBlock::~SelectedBlock() {
	logger.destructor(this);
}

void game::SelectedBlock::update() {
	auto &player = mainGame.lock()->getPlayer();
	auto &map = mainGame.lock()->getWorldMap();
	auto headPosition = player->getFullPosition();

	logger.log("updateing block").log(headPosition);

	static const CoordDim handRange = 4;

	for (CoordDim dx = -handRange; dx <= handRange; dx++)
		for (CoordDim dy = -handRange; dy <= handRange; dy++)
			for (CoordDim dz = -handRange; dz <= handRange; dz++) {
				auto checkPos = headPosition.getNeighbor(dx, dy, dz);
				if (!checkPos.isValid()) continue;


			}
}
