#include "player.h"

game::Player::Player() {
	camera.position = glm::vec3(4.0f);
	camera.front = glm::vec3(-4.0f);
	camera.up = glm::vec3(0.0f, 0.0f, 1.0f);
}

void game::Player::moveForward(double time) {
	auto forwardVec = glm::normalize(camera.front);
	forwardVec *= time;
	camera.position += forwardVec;
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

const engine::Camera &game::Player::getCamera() const {
	return camera;
}

void game::Player::rotateUp(double dy) {
	auto topVec = glm::vec3(0.0f, 0.0f, 1.0f);
	auto rotVec = glm::rotateY(camera.front, (float) dy / 200);
	camera.front = rotVec;
}

void game::Player::rotateDown(double dy) {
	rotateUp(-dy);
}

void game::Player::rotateLeft(double dx) {
	auto topVec = glm::vec3(0.0f, 0.0f, 1.0f);
	auto rotVec = glm::rotateZ(camera.front, (float) dx / 200);
	camera.front = rotVec;
}

void game::Player::rotateRight(double dx) {
	rotateLeft(-dx);
}
