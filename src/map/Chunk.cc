/**
 * @file Chunk.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Chunk.h"
#include "World.h"
#include "lib/AppSettings.h"
#include "src/block/Factory.h"

const Coord3D map::Chunk::Size = Coord3D(16, 16, 16);

map::Chunk::Chunk(const WorldPtr &worldMap, const Coord2D &position) :
		worldMapWPtr(worldMap),
		position(position) {
	logger(5).constructor(this);
}

map::Chunk::~Chunk() {
	logger(5).destructor(this);
}

map::ChunkPtr map::Chunk::create(const map::WorldPtr &worldMap, const Coord2D &position) {
	struct Self : Chunk {
		Self(const map::WorldPtr &worldMap, const Coord2D &position) : Chunk(worldMap, position) {}
	};

	map::ChunkPtr self = std::make_shared<Self>(worldMap, position);

	return self;
}

block::BlockPtr map::Chunk::getBlock(const Coord3D &position) const {

	// tu jest ciekawa opcja, bo gdy weżmiemy sobie nie istaniejący blok to mapa utworzy go z konstruktorem domyślnym
	// https://stackoverflow.com/questions/6952486/recommended-way-to-insert-elements-into-map

	if (isAir(position)) throw zprException("map::Chunk::getBlock", "getting air solid_block");

	return blocks[position];
}

bool map::Chunk::setBlock(const Coord3D &position, block::BlockPtr &block) {
	if (block.get() == nullptr)
		throw zprException("map::Chunk::setBlock", "setting empty solid_block");

	auto self = this->shared_from_this();
	block->setPosition(self, position);
	blocks[position] = block;
	setNeedSave(true);
	onBlockChange(position);
	return false;
}

bool map::Chunk::setAir(const Coord3D &position) {
	setNeedSave(true);
	blocks.erase(position);
	onBlockChange(position);
	return false;
}

bool map::Chunk::isAir(const Coord3D &position) const {
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

//region SavableObject

const char *JSON_ATTR_BLOCKS = "blocks";
const char *JSON_ATTR_COORD = "blocks";

json map::Chunk::toJSON() const {
	json j;

	j[JSON_ATTR_COORD] = getPosition().toJSON();

	auto row_x = json::array();
	for (CoordDim x = 0; x < Chunk::Size.x; x++) {
		auto row_y = json::array();
		for (CoordDim y = 0; y < Chunk::Size.y; y++) {
			auto row_z = json::array();
			for (CoordDim z = 0; z < Chunk::Size.y; z++) {

				auto coord = Coord3D(x, y, z);

				if (isAir(coord))
					row_z.push_back(nullptr);
				else row_z.push_back(getBlock(coord)->toJSON());
			}

			row_y.push_back(row_z);
		}
		row_x.push_back(row_y);
	}

	j[JSON_ATTR_BLOCKS] = row_x;

	return j;
}

boost::filesystem::path map::Chunk::getSavePath(AppSettings &app_settings) const {
	if (auto worldMapPtr = worldMapWPtr.lock()) {
		return (worldMapPtr->getDirectory() / "surface1") / (position.toStringId() + ".chunk");
	} else throw zprException("map::Chunk::getSavePath", "saving chunk when WorldMap object is gone");
}

void map::Chunk::acceptState(json &data) {


	auto row_x = data[JSON_ATTR_BLOCKS];

	if (!row_x.is_array()) throw WrongJsonException();

	CoordDim x = 0, y = 0, z = 0;

	for (auto &row_y : row_x) {
		if (!row_x.is_array())
			throw std::exception();

		if (x >= Size.x) throw WrongJsonException();
		y = 0;

		for (auto &row_z : row_y) {
			if (y >= Size.y) throw WrongJsonException();
			z = 0;

			for (auto &jblock : row_z) {
				if (z >= Size.z) throw WrongJsonException();

				if (jblock != nullptr) {

					auto block = block::Factory::create(jblock);
					setBlock(Coord3D(x, y, z), block);
				}

				z++;
			}
			y++;
		}
		x++;
	}

	setNeedSave(false);
}

//endregion
