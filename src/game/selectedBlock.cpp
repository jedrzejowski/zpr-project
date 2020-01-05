#include "selectedBlock.h"
#include "src/block/wall.h"
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

	static const CoordDim handRange = 4;

	float distance = handRange * 10, newDistance = handRange * 11;
	bool found = false;

	glm::vec2 baryPosition;//nie mam pojęcia do czego to jest ale glm tego chce'
	CoordDim dx, dy, dz;


	for (dx = -handRange; dx <= handRange; dx++)
		for (dy = -handRange; dy <= handRange; dy++)
			for (dz = -handRange; dz <= handRange; dz++) {
				auto blockPos = headPosition.getNeighbor(dx, dy, dz);
				if (!blockPos.isValid()) continue;

				auto vec = blockPos.toVec();

				auto wall = block::getWall(blockPos, block::Direction::Z_PLUS);
				if (wall.intersectRay(player->getCamera().position,
									  player->getCamera().front,
									  baryPosition,
									  newDistance) &&
					newDistance < distance) {
					found = true;
					distance = newDistance;
					pointingPos = blockPos;
					newPos = blockPos.getNeighbor(0, 0, +1);
				}


				wall = block::getWall(blockPos, block::Direction::Z_MINUS);
				if (wall.intersectRay(player->getCamera().position,
									  player->getCamera().front,
									  baryPosition,
									  newDistance) &&
					newDistance < distance) {
					found = true;
					distance = newDistance;
					pointingPos = blockPos;
					newPos = blockPos.getNeighbor(0, 0, -1);
				}


				wall = block::getWall(blockPos, block::Direction::X_PLUS);
				if (wall.intersectRay(player->getCamera().position,
									  player->getCamera().front,
									  baryPosition,
									  newDistance) &&
					newDistance < distance) {
					found = true;
					distance = newDistance;
					pointingPos = blockPos;
					newPos = blockPos.getNeighbor(1, 0, 0);
				}

				wall = block::getWall(blockPos, block::Direction::X_MINUS);
				if (wall.intersectRay(player->getCamera().position,
									  player->getCamera().front,
									  baryPosition,
									  newDistance) &&
					newDistance < distance) {
					found = true;
					distance = newDistance;
					pointingPos = blockPos;
					newPos = blockPos.getNeighbor(-1, 0, 0);
				}

				wall = block::getWall(blockPos, block::Direction::Y_PLUS);
				if (wall.intersectRay(player->getCamera().position,
									  player->getCamera().front,
									  baryPosition,
									  newDistance) &&
					newDistance < distance) {
					found = true;
					distance = newDistance;
					pointingPos = blockPos;
					newPos = blockPos.getNeighbor(0, 1, 0);
				}

				wall = block::getWall(blockPos, block::Direction::Y_MINUS);
				if (wall.intersectRay(player->getCamera().position,
									  player->getCamera().front,
									  baryPosition,
									  newDistance) &&
					newDistance < distance) {
					found = true;
					distance = newDistance;
					pointingPos = blockPos;
					newPos = blockPos.getNeighbor(0, -1, 0);
				}
			}

	isSelected = found;

	if (isSelected) {
		logger.log("player is looking at").log(pointingPos);
	}
}

const block::FullPosition &game::SelectedBlock::getPointingPos() const {
	return pointingPos;
}

const block::FullPosition &game::SelectedBlock::getNewPos() const {
	return newPos;
}

bool game::SelectedBlock::isSelected1() const {
	return isSelected;
}
