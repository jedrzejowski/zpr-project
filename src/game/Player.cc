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

game::Player::Player(map::WorldPtr &world_map_ptr) :
		world_map_ptr(world_map_ptr) {
	logger(4).constructor(this);
}

game::Player::~Player() {
	logger(4).destructor(this);
}

void game::Player::initWithDefaultValues() {
	eye_angle_vertical = 0;
	eye_angle_horizontal = 0;
	mouse_precision = 20;
	keyboard_precision = 10;
	position = glm::vec3(4.0f);
}

game::PlayerPtr game::Player::create(map::WorldPtr &world_map_ptr) {
	struct Self : Player {
		Self(map::WorldPtr &world_map_ptr) : Player(world_map_ptr) {}
	};

	game::PlayerPtr self = std::make_shared<Self>(world_map_ptr);

	if (self->hasSavedFile())
		self->loadObjectFromFile([&] {
			self->initWithDefaultValues();
		});
	else
		self->initWithDefaultValues();

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
	setNeedSave(true);
}

void game::Player::moveBackward(float time) {
	moveForward(-time);
}

void game::Player::moveUp(float time) {
	auto vec = topVec();
	vec *= time * keyboard_precision;
	position += vec;
	setNeedSave(true);
}

void game::Player::moveDown(float time) {
	moveUp(-time);
}

void game::Player::moveLeft(float time) {
	auto vec = leftVec();
	vec *= time * keyboard_precision;
	position += vec;
	setNeedSave(true);
}

void game::Player::moveRight(float time) {
	moveLeft(-time);
}

void game::Player::rotateHeadUp(float dy) {
	eye_angle_vertical = std::clamp(eye_angle_vertical + dy / mouse_precision,
									-80.f, 80.f);
	setNeedSave(true);
}

void game::Player::rotateHeadDown(float dy) {
	rotateHeadUp(-dy);
}

void game::Player::rotateHeadRight(float dx) {
	eye_angle_horizontal = fmod(eye_angle_horizontal + dx / mouse_precision, 360);
	setNeedSave(true);
}

void game::Player::rotateHeadLeft(float dx) {
	rotateHeadRight(-dx);
}

engine::Camera game::Player::getCamera() const {
	auto camera = engine::Camera();
	camera.position = position;
	camera.up = topVec();
	camera.front = frontVec();
	return camera;
}

float game::Player::getChunkRenderDistance() const {
	static auto &app_setting = AppSettings::get();
	return app_setting.chunkRenderDistance.get();
}

float game::Player::getChunkUnloadDistance() const {
	return getChunkRenderDistance() + 2;
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

//region Block Pointing

void game::Player::resetBlockPointing() {
	need_block_point_calculate = true;
}

void game::Player::recalculateBlockPointing() const {
	if (!need_block_point_calculate) return;

	auto camera = getCamera();
	auto head_position = getFullPosition();

	static const CoordDim hand_range = 6;

	float distance = hand_range + 1, new_distance = hand_range + 2;
	bool found = false;

	glm::vec2 bary_position; //nie mam pojęcia do czego to jest ale glm tego chce

	for (CoordDim dx = -hand_range; dx <= hand_range; ++dx)
		for (CoordDim dy = -hand_range; dy <= hand_range; ++dy)
			for (CoordDim dz = -hand_range; dz <= hand_range; ++dz) {

				auto block_position = head_position.getNeighbor(dx, dy, dz);
				if (!block_position.isValid()) continue;
				if (auto chunk = world_map_ptr->getChunk(block_position.getChunkCoord()).lock()) {
					if (chunk->isAir(block_position.getBlockCoord())) continue;
				} else continue;

				// tu się inaczej nie da, musimy za każdym razem mieć dostęp do wielu zmiennych tymczasowych,
				// jak i operować na enumach i wartościach wektorów, można by zrobić wektor pomocniczy,
				// a potem iterować po nim, ale wiązało by się to z wprowadzenie wilu nowych struktur

				auto wall = block::getWall(block_position, block::Direction::Z_PLUS);
				if (wall.intersectCamera(camera, bary_position, new_distance))
					if (new_distance < distance) {

						found = true;
						distance = new_distance;
						pointing_block_position = block_position;
						new_block_position = block_position.getNeighbor(0, 0, +1);
					}

				wall = block::getWall(block_position, block::Direction::Z_MINUS);
				if (wall.intersectCamera(camera, bary_position, new_distance))
					if (new_distance < distance) {

						found = true;
						distance = new_distance;
						pointing_block_position = block_position;
						new_block_position = block_position.getNeighbor(0, 0, -1);
					}

				wall = block::getWall(block_position, block::Direction::Y_PLUS);
				if (wall.intersectCamera(camera, bary_position, new_distance))
					if (new_distance < distance) {

						found = true;
						distance = new_distance;
						pointing_block_position = block_position;
						new_block_position = block_position.getNeighbor(0, +1, 0);
					}

				wall = block::getWall(block_position, block::Direction::Y_MINUS);
				if (wall.intersectCamera(camera, bary_position, new_distance))
					if (new_distance < distance) {

						found = true;
						distance = new_distance;
						pointing_block_position = block_position;
						new_block_position = block_position.getNeighbor(0, -1, 0);
					}

				wall = block::getWall(block_position, block::Direction::X_PLUS);
				if (wall.intersectCamera(camera, bary_position, new_distance))
					if (new_distance < distance) {

						found = true;
						distance = new_distance;
						pointing_block_position = block_position;
						new_block_position = block_position.getNeighbor(+1, 0, 0);
					}

				wall = block::getWall(block_position, block::Direction::X_MINUS);
				if (wall.intersectCamera(camera, bary_position, new_distance))
					if (new_distance < distance) {

						found = true;
						distance = new_distance;
						pointing_block_position = block_position;
						new_block_position = block_position.getNeighbor(-1, 0, 0);
					}
			}

	is_pointing_block = hand_range >= distance && found;
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

//endregion

//region SavableObject

const char *JSON_ATTR_POSITION = "position";
const char *JSON_ATTR_EYE_ANGLE_VERTICAL = "eye_angle_vertical";
const char *JSON_ATTR_EYE_ANGLE_HORIZONTAL = "eye_angle_horizontal";
const char *JSON_ATTR_MOUSE_PRECISION = "mouse_precision";
const char *JSON_ATTR_KEYBOARD_PRECISION = "keyboard_precision";

std::filesystem::path game::Player::getSavePath() const {
	return world_map_ptr->getDirectory() / "player";
}

json game::Player::toJSON() const {
	json json_obj;

	json_obj[JSON_ATTR_POSITION] = json::array({position.x, position.y, position.z});
	json_obj[JSON_ATTR_EYE_ANGLE_VERTICAL] = eye_angle_vertical;
	json_obj[JSON_ATTR_EYE_ANGLE_HORIZONTAL] = eye_angle_horizontal;
	json_obj[JSON_ATTR_MOUSE_PRECISION] = mouse_precision;
	json_obj[JSON_ATTR_KEYBOARD_PRECISION] = keyboard_precision;

	return json_obj;
}

void game::Player::acceptState(json &json_obj) {

	position = assertGetVec3(json_obj[JSON_ATTR_POSITION]);
	eye_angle_vertical = assertGetNumber(json_obj[JSON_ATTR_EYE_ANGLE_VERTICAL]);
	eye_angle_horizontal = assertGetNumber(json_obj[JSON_ATTR_EYE_ANGLE_HORIZONTAL]);
	mouse_precision = assertGetNumber(json_obj[JSON_ATTR_MOUSE_PRECISION]);
	keyboard_precision = assertGetNumber(json_obj[JSON_ATTR_KEYBOARD_PRECISION]);

	setNeedSave(false);
}

//endregion

