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

block::BlockPtr map::Chunk::getBlock(const Coord3D &position) {
	return blocks[position];
}

bool map::Chunk::setBlock(const Coord3D &position, block::BlockPtr &block) {
	if (block.get() == nullptr)
		throw zprException("map::Chunk::setBlock() setting empty block");

	auto self = this->shared_from_this();
	block->setPosition(self, position);
	blocks[position] = block;
	return false;
}

bool map::Chunk::setAir(const Coord3D &position) {
	blocks.erase(position);
	return false;
}

bool map::Chunk::isAir(const Coord3D &position) {
	return blocks.count(position) == 0;
}

const std::map<Coord3D, block::BlockPtr> &map::Chunk::getAllBlocks() const {
	return blocks;
}

const Coord2D &map::Chunk::getPosition() const {
	return position;
}

map::ChunkWPtr map::Chunk::getNeighbor(CoordDim dx, CoordDim dy) const {
	auto neighborPos = position;
	neighborPos.x += dx;
	neighborPos.y += dy;
	return worldMap->getChunk(neighborPos);
}

json map::Chunk::toJSON() const {
	json j;

	j["coord"] = getPosition().toJSON();

	auto jblocks = json::object();

	for (const auto &it : blocks)
		jblocks[it.first.toStringId()] = it.second->toJSON();
	j["blocks"] = jblocks;

	return j;
}

void map::Chunk::save() {
	auto &appSettings = AppSettings::get();
	auto fileName = (worldMap->getDirectory() / "surface1") / (position.toStringId() + ".chunk");
	appSettings.saveJSON(fileName, toJSON());
}


