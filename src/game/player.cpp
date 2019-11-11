#include <cmath>
#include "player.h"
#include "src/lib/coord.h"
#include "src/map/world.h"
#include "src/map/chunk.h"

game::Player::Player(map::World *world) :
		world(world) {
	position = glm::vec3(4.0f);
	angleH = 0;
	angleV = 0;
}


glm::vec3 game::Player::topVec() const {
	return glm::vec3(0.0f, 0.0f, 1.0f);
}

glm::vec3 game::Player::frontVec() const {
	glm::vec3 frontVec = glm::vec3(1.0f, 0.f, 0.f);
	frontVec = glm::rotateY(frontVec, glm::radians(angleV));
	frontVec = glm::rotateZ(frontVec, glm::radians(angleH));
	return glm::normalize(frontVec);
}

glm::vec3 game::Player::leftVec() const {
	return glm::normalize(glm::cross(topVec(), frontVec()));
}


void game::Player::moveForward(float time) {
	glm::vec3 forward = glm::vec3(1.0f, 0.f, 0.f);
	forward = glm::rotateZ(forward, glm::radians(angleH));
	forward *= time * keyboardPrecision;
	position += forward;
}

void game::Player::moveBackward(float time) {
	moveForward(-time);
}

void game::Player::moveUp(float time) {
	auto vec = topVec();
	vec *= time * keyboardPrecision;
	position += vec;
}

void game::Player::moveDown(float time) {
	moveUp(-time);
}

void game::Player::moveLeft(float time) {
	auto vec = leftVec();
	vec *= time * keyboardPrecision;
	position += vec;
}

void game::Player::moveRight(float time) {
	moveLeft(-time);
}

void game::Player::rotateUp(float dy) {
	angleV = std::clamp(angleV + dy / mousePrecision,
						-80.f, 80.f);
}

void game::Player::rotateDown(float dy) {
	rotateUp(-dy);
}

void game::Player::rotateRight(float dx) {
	angleH = fmod(angleH + dx / mousePrecision, 360);
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
	return chunkRenderDistance;
}

float game::Player::getChunkLoadDistance() const {
	return chunkLoadDistance;
}

void game::Player::requestChunks() {
	auto currentChunk = getCurrentChunk();

	for (CoordDim x = currentChunk.x - chunkLoadDistance; x < currentChunk.x + chunkLoadDistance; x++) {
		for (CoordDim y = currentChunk.y - chunkLoadDistance; y < currentChunk.y + chunkLoadDistance; y++) {
			world->requestChunk(Coord2D(x, y));
		}
	}
}

Coord2D game::Player::getCurrentChunk() const {
	auto playerCoord = Coord2D(position);
	return Coord2D(playerCoord.x / map::Chunk::Size.x, playerCoord.y / map::Chunk::Size.y);
}
