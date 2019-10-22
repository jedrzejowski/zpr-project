#include "player.h"

game::Player::Player() {
	camera.position = glm::vec3(4.0f);
	camera.front = glm::vec3(-4.0f);
	camera.up = glm::vec3(0.0f, 0.0f, 1.0f);
}

void game::Player::moveForward(double time) {
}

void game::Player::moveBackward(double time) {
	moveForward(-time);
}

void game::Player::moveUp(double time) {
	auto topVec = glm::vec3(0.0f, 0.0f, 1.0f);
	topVec *= time;
	camera.position += topVec;
}

void game::Player::moveDown(double time) {
	moveUp(-time);
}

void game::Player::moveLeft(double time) {
	auto leftVec = glm::cross(camera.up, camera.front);
	// TODO sprawdzić czy noramlizacja jest potrzebna
	leftVec = glm::normalize(leftVec);
	leftVec *= time;
	camera.position += leftVec;
}

void game::Player::moveRight(double time) {
	moveLeft(-time);
}

const engine::camera &game::Player::getCamera() const {
	return camera;
}
