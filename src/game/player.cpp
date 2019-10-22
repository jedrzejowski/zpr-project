#include "player.h"

game::Player::Player() {
	camera.position = glm::vec3(4.0f);
	camera.front = glm::vec3(-4.0f);
	camera.up = glm::vec3(0.0f, 0.0f, 1.0f);
}

void game::Player::moveForward(float distance) {
}

void game::Player::moveBackward(float distance) {
}

void game::Player::moveDown(float distance) {
}

void game::Player::moveUp(float distance) {
}

void game::Player::moveLeft(float distance) {
}

void game::Player::moveRight(float distance) {
}

const engine::camera& game::Player::getCamera() const {
	return camera;
}
