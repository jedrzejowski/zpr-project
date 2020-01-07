/**
 * @file Chunk.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Chunk.h"
#include "World.h"
#include "lib/AppSettings.h"

const Coord3D map::Chunk::Size = Coord3D(16, 16, 16);

map::Chunk::Chunk(const WorldPtr &worldMap, const Coord2D &position) :
		worldMapWPtr(worldMap),
		position(position) {
	logger.constructor(this);
}

map::Chunk::~Chunk() {
	logger.destructor(this);
}

map::ChunkPtr map::Chunk::create(const map::WorldPtr &worldMap, const Coord2D &position) {
	struct Self : Chunk {
		Self(const map::WorldPtr &worldMap, const Coord2D &position) : Chunk(worldMap, position) {}
	};

	map::ChunkPtr self = std::make_shared<Self>(worldMap, position);

	return self;
}

block::BlockPtr map::Chunk::getBlock(const Coord3D &position) {

	// tu jest ciekawa opcja, bo gdy weżmiemy sobie nie istaniejący blok to mapa utworzy go z konstruktorem domyślnym
	// https://stackoverflow.com/questions/6952486/recommended-way-to-insert-elements-into-map

	if (isAir(position)) throw zprException("getting air block");

	return blocks[position];
}

bool map::Chunk::setBlock(const Coord3D &position, block::BlockPtr &block) {
//	logger.log("map::Chunk::setBlock").log(block);
	if (block.get() == nullptr)
		throw zprException("map::Chunk::setBlock() setting empty block");

	auto self = this->shared_from_this();
	block->setPosition(self, position);
	blocks[position] = block;
	onBlockChange(position);
	return false;
}

bool map::Chunk::setAir(const Coord3D &position) {
	blocks.erase(position);
	onBlockChange(position);
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

	if (auto worldMapPtr = worldMapWPtr.lock())
		return worldMapPtr->getChunk(neighborPos);
	else return map::ChunkWPtr();
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
	if (auto worldMapPtr = worldMapWPtr.lock()) {

		auto fileName = (worldMapPtr->getDirectory() / "surface1") / (position.toStringId() + ".chunk");
		auto &appSettings = AppSettings::get();
		appSettings.saveJSON(fileName, toJSON());
	} else throw zprException("map::Chunk::save(): saving chunk when WorldMap object is gone");
}


