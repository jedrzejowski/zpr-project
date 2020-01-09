/**
 * @file Player.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include <cmath>
#include "Player.h"
#include "MainGame.h"
#include "src/lib/Coord.hpp"
#include "src/map/Chunk.h"
#include "src/map/World.h"

game::Player::Player(game::MainGamePtr &main_game) :
		main_game(main_game) {
	initWithDefaultValues();
}

void game::Player::initWithDefaultValues() {
	eye_angle_vertical = 0;
	eye_angle_horizontal = 0;
	mouse_precision = 20;
	keyboard_precision = 10;
	chunk_render_distance = 4;
	chunk_unload_distance = 6;
	position = glm::vec3(4.0f);
}

game::PlayerPtr game::Player::create(game::MainGamePtr &main_game) {
	struct Self : Player {
		Self(game::MainGamePtr &main_game) : Player(main_game) {}
	};

	game::PlayerPtr self = std::make_shared<Self>(main_game);


	return self;
}


glm::vec3 game::Player::topVec() const {
	return glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::vec3 game::Player::frontVec() const {
	glm::vec3 frontVec = glm::vec3(1.0f, 0.f, 0.f);
	frontVec = glm::rotateY(frontVec, glm::radians(eye_angle_vertical));
	frontVec = glm::rotateZ(frontVec, glm::radians(eye_angle_horizontal));
	return glm::normalize(frontVec);
}

glm::vec3 game::Player::leftVec() const {
	return glm::normalize(glm::cross(topVec(), frontVec()));
}


void game::Player::moveForward(float time) {
	glm::vec3 forward = glm::vec3(1.0f, 0.f, 0.f);
	forward = glm::rotateZ(forward, glm::radians(eye_angle_horizontal));
	forward *= time * keyboard_precision;
	position += forward;
}

void game::Player::moveBackward(float time) {
	moveForward(-time);
}

void game::Player::moveUp(float time) {
	auto vec = topVec();
	vec *= time * keyboard_precision;
	position += vec;
}

void game::Player::moveDown(float time) {
	moveUp(-time);
}

void game::Player::moveLeft(float time) {
	auto vec = leftVec();
	vec *= time * keyboard_precision;
	position += vec;
}

void game::Player::moveRight(float time) {
	moveLeft(-time);
}

void game::Player::rotateUp(float dy) {
	eye_angle_vertical = std::clamp(eye_angle_vertical + dy / mouse_precision,
									-80.f, 80.f);
}

void game::Player::rotateDown(float dy) {
	rotateUp(-dy);
}

void game::Player::rotateRight(float dx) {
	eye_angle_horizontal = fmod(eye_angle_horizontal + dx / mouse_precision, 360);
}

void game::Player::rotateLeft(float dx) {
	rotateRight(-dx);
}

engine::Camera game::Player::getCamera() const {
	auto camera = engine::Camera();
	camera.position = position;
	camera.up = topVec();
	camera.front = frontVec();
	return camera;
}

float game::Player::getChunkRenderDistance() const {
	return chunk_render_distance;
}

float game::Player::getChunkUnloadDistance() const {
	return chunk_unload_distance;
}

block::FullPosition game::Player::getFullPosition() const {

	auto chunk = Coord2D(position.x / map::Chunk::Size.x, position.y / map::Chunk::Size.y);

	return block::FullPosition(
			chunk,
			Coord3D(
					position.x - chunk.x * map::Chunk::Size.x,
					position.y - chunk.y * map::Chunk::Size.y,
					position.z
			)
	);
}

//#region Block Pointing

void game::Player::resetBlockPointing() {
	need_block_point_calculate = true;
}

void game::Player::recalculateBlockPointing() const {
	if (!need_block_point_calculate) return;

	auto &map = main_game.lock()->getWorldMap();
	auto camera = getCamera();
	auto headPosition = getFullPosition();

	static const CoordDim handRange = 4;

	float distance = handRange * 10, newDistance = handRange * 11;
	bool found = false;

	glm::vec2 baryPosition;//nie mam pojęcia do czego to jest ale glm tego chce

	for (CoordDim dx = -handRange; dx <= handRange; dx++)
		for (CoordDim dy = -handRange; dy <= handRange; dy++)
			for (CoordDim dz = -handRange; dz <= handRange; dz++) {

				auto blockPos = headPosition.getNeighbor(dx, dy, dz);
				if (!blockPos.isValid()) continue;
				if (auto chunk = map->getChunk(blockPos.getChunkCoord()).lock()) {
					if (chunk->isAir(blockPos.getBlockCoord())) continue;
				} else continue;

				// tu się inaczej nie da, musimy za każdym razem mieć dostęp do wielu zmiennych tymczasowych,
				// jak i operować na enumach i wartościach wektorów, można by zrobić wektor pomocniczy,
				// a potem iterować po nim, ale wiązało by się to z wprowadzenie wilu nowych struktur

				auto wall = block::getWall(blockPos, block::Direction::Z_PLUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointing_block_position = blockPos;
						new_block_position = blockPos.getNeighbor(0, 0, +1);
					}

				wall = block::getWall(blockPos, block::Direction::Z_MINUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointing_block_position = blockPos;
						new_block_position = blockPos.getNeighbor(0, 0, -1);
					}

				wall = block::getWall(blockPos, block::Direction::Y_PLUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointing_block_position = blockPos;
						new_block_position = blockPos.getNeighbor(0, +1, 0);
					}

				wall = block::getWall(blockPos, block::Direction::Y_MINUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointing_block_position = blockPos;
						new_block_position = blockPos.getNeighbor(0, -1, 0);
					}

				wall = block::getWall(blockPos, block::Direction::X_PLUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointing_block_position = blockPos;
						new_block_position = blockPos.getNeighbor(+1, 0, 0);
					}

				wall = block::getWall(blockPos, block::Direction::X_MINUS);
				if (wall.intersectCamera(camera, baryPosition, newDistance))
					if (newDistance < distance) {

						found = true;
						distance = newDistance;
						pointing_block_position = blockPos;
						new_block_position = blockPos.getNeighbor(-1, 0, 0);
					}
			}

	is_pointing_block = found;
}

const block::FullPosition &game::Player::getPointingBlockPosition() const {
	recalculateBlockPointing();
	return pointing_block_position;
}

const block::FullPosition &game::Player::getNewBlockPosition() const {
	recalculateBlockPointing();
	return new_block_position;
}

bool game::Player::isPointingBlock() const {
	recalculateBlockPointing();
	return is_pointing_block;
}

//#endregion
