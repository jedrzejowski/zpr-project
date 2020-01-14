/**
 * @file World.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "World.h"
#include "Chunk.h"
#include "WorldManager.h"
#include "src/game/Game.h"
#include "lib/AppSettings.h"

map::World::World(const std::string &codeName) :
		code_name(codeName),
		chunk_loader(this),
		chunk_generator(this),
		display_name(codeName) {
	logger(4).constructor(this);
}

map::World::~World() {
	logger(4).destructor(this);
}

map::WorldPtr map::World::create(const std::string &codeName) {
	struct Self : World {
		Self(const std::string &codeName) : World(codeName) {}
	};

	map::WorldPtr self = std::make_shared<Self>(codeName);

	if (self->hasSavedFile())
		self->loadObjectFromFile();

	return self;
}


bool map::World::hasChunk(const Coord2D &position) {
	return chunks.count(position) == 1;
}

map::ChunkWPtr map::World::getChunk(const Coord2D &position) {
	if (hasChunk(position))
		return chunks[position];

	return map::ChunkWPtr();
}

void map::World::requestChunk(Coord2D position) {
	chunk_loader.load(position);
}


void map::World::syncChunkWithLoader() {
	chunk_loader.syncWithWorld();
}

void map::World::insertChunk(map::ChunkPtr chunk) {
	if (hasChunk(chunk->getPosition()))
		throw zprException("map::World::insertChunk", "inserting chunk which position already exist");

	if (isDeleted()) chunk->deleteThisObjectAsFile();

	chunks[chunk->getPosition()] = chunk;
	onChunkInserted(chunk);
}

map::ChunkPtr map::World::ejectChunk(const Coord2D &position) {
	if (!hasChunk(position))
		throw zprException("map::World::ejectChunk", "ejecting chunk not inserted chunk");

	auto chunk = chunks[position];
	chunks.erase(position);

	onChunkEjected(chunk);

	return chunk;
}

void map::World::loadForPlayer(game::PlayerPtr &player) {
	auto playerChunk = player->getFullPosition().getChunkCoord();
	auto chunkLoadDistance = player->getChunkUnloadDistance();

	// ładowanie chunków
	for (CoordDim x = playerChunk.x - chunkLoadDistance; x < playerChunk.x + chunkLoadDistance; ++x) {
		for (CoordDim y = playerChunk.y - chunkLoadDistance; y < playerChunk.y + chunkLoadDistance; ++y) {
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

			chunk_loader.unload(pos);
		}
	}
}

const std::string &map::World::getDisplayName() const {
	return display_name;
}

void map::World::setDisplayName(const std::string &displayName) {
	World::display_name = displayName;
	setNeedSave(true);
}

const std::string &map::World::getCodeName() const {
	return code_name;
}


const std::map<Coord2D, map::ChunkPtr> &map::World::getLoadedChunks() const {
	return chunks;
}

//region SavableObject

const char *JSON_ATTR_DISPLAY_NAME = "display_name";

std::filesystem::path map::World::getDirectory() const {
	return WorldManager::getWorldsDirectory() / getCodeName();
}

std::filesystem::path map::World::getSavePath() const {
	return getDirectory() / "worldinfo";
}

json map::World::toJSON() const {
	json json_obj;

	json_obj[JSON_ATTR_DISPLAY_NAME] = display_name;

	return json_obj;
}

void map::World::acceptState(json &json_obj) {

	display_name = assertGetString(json_obj[JSON_ATTR_DISPLAY_NAME]);

	setNeedSave(false);
}

void map::World::fullSave() {
	saveObjectToFile();

	chunk_generator.saveObjectToFile();

	for (const auto &it : chunks)
		it.second->saveObjectToFile();
}

//endregion