/**
 * @file SelectedBlock.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "SelectedBlock.h"
#include "src/block/Wall.h"
#include "MainGame.h"
#include "Player.h"
#include "src/map/World.h"
#include "src/map/Chunk.h"

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
	auto camera = player->getCamera();
	auto headPosition = player->getFullPosition();

	static const CoordDim handRange = 4;

	float distance = handRange * 10, newDistance = handRange * 11;
	bool found = false;

	glm::vec2 baryPosition;//nie mam pojęcia do czego to jest ale glm tego chce

	for (CoordDim dx = -handRange; dx <= handRange; dx++)
		for (CoordDim dy = -handRange; dy <= handRange; dy++)
			for (CoordDim dz = -handRange; dz <= handRange; dz++) {

				auto blockPos = headPosition.getNeighbor(dx, dy, dz);
				if (!blockPos.isValid()) continue;
				if (auto chunk = map->getChunk(blockPos.getChunk()).lock()) {
					if (chunk->isAir(blockPos.getBlock())) continue;
				} else continue;

				// tu się inaczej nie da, musimy za każdym razem mieć dostęp do wielu zmiennych,
				// jak i operować na enumach i wartościach wektorów, można by zrobić wektor pomocniczy,
				// a potem iterować po nim, ale wiązało by się to z wprowadzenie wilu nowych struktur

				auto wall = block::getWall(blockPos, block::Direction::Z_PLUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointingPos = blockPos;
						newBlockPos = blockPos.getNeighbor(0, 0, +1);
					}

				wall = block::getWall(blockPos, block::Direction::Z_MINUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointingPos = blockPos;
						newBlockPos = blockPos.getNeighbor(0, 0, -1);
					}

				wall = block::getWall(blockPos, block::Direction::Y_PLUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointingPos = blockPos;
						newBlockPos = blockPos.getNeighbor(0, +1, 0);
					}

				wall = block::getWall(blockPos, block::Direction::Y_MINUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointingPos = blockPos;
						newBlockPos = blockPos.getNeighbor(0, -1, 0);
					}

				wall = block::getWall(blockPos, block::Direction::X_PLUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointingPos = blockPos;
						newBlockPos = blockPos.getNeighbor(+1, 0, 0);
					}

				wall = block::getWall(blockPos, block::Direction::X_MINUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointingPos = blockPos;
						newBlockPos = blockPos.getNeighbor(-1, 0, 0);
					}

			}

	selected = found;
}

const block::FullPosition &game::SelectedBlock::getPointingPos() const {
	return pointingPos;
}

const block::FullPosition &game::SelectedBlock::getNewBlockPos() const {
	return newBlockPos;
}

bool game::SelectedBlock::isSelected() const {
	return selected;
}
