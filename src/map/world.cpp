#include "world.h"
#include "chunk.h"
#include "src/game/Game.h"
#include "lib/appSettings.h"

map::World::World(std::string codeName) :
		codeName(codeName),
		chunkLoader(this),
		chunkGenerator(this) {
	logger.constructor(this);
}

map::World::~World() {
	logger.destructor(this);
}


bool map::World::hasChunk(const Coord2D &position) {
	return chunks.count(position) == 1;
}

map::ChunkPtr map::World::getChunk(const Coord2D &position) {
	if (hasChunk(position))
		return chunks[position];

	return nullptr;
}

void map::World::requestChunk(Coord2D position) {
	chunkLoader.load(position);
}


void map::World::syncChunkWithLoader() {
	chunkLoader.syncWithWorld();
}

void map::World::insertChunk(map::ChunkPtr chunk) {
	if (hasChunk(chunk->getPosition()))
		throw zprException("inserting chunk which position already exist");

	chunks[chunk->getPosition()] = chunk;
	onChunkInserted(chunk);
}

map::ChunkPtr map::World::ejectChunk(const Coord2D &position) {
	if (!hasChunk(position))
		throw zprException("ejecting chunk not inserted chunk");

	auto chunk = chunks[position];
	chunks.erase(position);

	onChunkEjected(chunk);

	return chunk;
}

void map::World::loadForPlayer(game::PlayerPtr &player) {
	auto playerChunk = player->getFullPosition().getChunk();
	auto chunkLoadDistance = player->getChunkUnloadDistance();

	// ładowanie chunków
	for (CoordDim x = playerChunk.x - chunkLoadDistance; x < playerChunk.x + chunkLoadDistance; x++) {
		for (CoordDim y = playerChunk.y - chunkLoadDistance; y < playerChunk.y + chunkLoadDistance; y++) {
			requestChunk(Coord2D(x, y));
		}
	}

	// wyładowanie chunków
	for (const auto &it : chunks) {
		auto chunk = it.second;

		auto pos = chunk->getPosition();

		if (pos.x > playerChunk.x + chunkLoadDistance ||
			pos.x < playerChunk.x - chunkLoadDistance ||
			pos.y > playerChunk.y + chunkLoadDistance ||
			pos.y < playerChunk.y - chunkLoadDistance) {

			chunkLoader.unload(pos);
		}
	}
}

const std::string &map::World::getDisplayName() const {
	return displayName;
}

void map::World::setDisplayName(const std::string &displayName) {
	World::displayName = displayName;
}

const std::string &map::World::getCodeName() const {
	return codeName;
}

boost::filesystem::path map::World::getDirectory() {
	return AppSettings::get().getCfgDir() / "worlds" / getCodeName();
}
