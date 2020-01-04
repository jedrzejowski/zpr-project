#pragma once

#include <map>
#include "src/_classdef.h"
#include "src/engine/Engine.h"
#include "src/lib/object.h"
#include "chunkGenerator.h"
#include "chunkLoader.h"

namespace map {
	class World : public Object, public virtual_enable_shared_from_this<World> {
		friend ChunkLoader;
		friend ChunkGenerator;
	protected:
		ChunkLoader chunkLoader;
		ChunkGenerator chunkGenerator;
		std::map<Coord2D, map::ChunkPtr> chunks;
		std::string codeName;
		std::string displayName;

		ChunkPtr ejectChunk(const Coord2D &position);
		void insertChunk(map::ChunkPtr chunk);
	public:
		World(std::string codeName);
		~World() override;

		bool hasChunk(const Coord2D &position);
		ChunkPtr getChunk(const Coord2D &position);
		void loadForPlayer(game::PlayerPtr &player);

		void requestChunk(Coord2D position);

		void syncChunkWithLoader();

		boost::filesystem::path getDirectory();

		const std::string &getDisplayName() const;
		void setDisplayName(const std::string &displayName);
		const std::string &getCodeName() const;

		const Signal<ChunkPtr> onChunkInserted;
		const Signal<ChunkPtr> onChunkEjected;
	};
}
