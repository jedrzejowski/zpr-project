#include "chunk.h"
#include "world.h"
#include "lib/appSettings.h"

const Coord3D map::Chunk::Size = Coord3D(16, 16, 16);

map::Chunk::Chunk(World *worldMap, const Coord2D &position) :
		worldMap(worldMap),
		position(position) {
	logger.constructor(this);
}

map::Chunk::~Chunk() {
	logger.destructor(this);
}

block::Block *map::Chunk::getBlock(const Coord3D &position) {
	if (blocks.count(position) == 1)
		return blocks[position];
	return nullptr;
}

bool map::Chunk::setBlock(const Coord3D &position, block::Block *block) {
	block->setPosition(this, position);

	blocks[position] = block;
	return false;
}

std::map<Coord3D, block::Block *> &map::Chunk::getAllBlocks() {
	return blocks;
}

const Coord2D &map::Chunk::getPosition() const {
	return position;
}

map::ChunkPtr map::Chunk::getNeighbor(CoordDim dx, CoordDim dy) const {
	auto neighborPos = position;
	neighborPos.x += dx;
	neighborPos.y += dy;
	return worldMap->getChunk(neighborPos);
}

json map::Chunk::toJSON() const {
	json j;

	j["coord"] = getPosition().toJSON();

	auto jblocks = json::object();

	for (const auto &it : blocks) {
		logger.log(it.first.toStringId()).log(it.second->toJSON());

		jblocks[it.first.toStringId()] = it.second->toJSON();
	}

	j["blocks"] = jblocks;

	return j;
}

void map::Chunk::save() {
	auto &appSettings = AppSettings::get();
	auto fileName = (worldMap->getDirectory() / "surface1") / (position.toStringId() + ".chunk");
	appSettings.saveJSON(fileName, toJSON());
}


