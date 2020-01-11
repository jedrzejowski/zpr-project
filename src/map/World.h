/**
 * @file World.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <map>
#include "boost/filesystem/path.hpp"
#include "src/_classdef.h"
#include "src/lib/Object.hpp"
#include "ChunkGenerator.h"
#include "ChunkLoader.h"
#include "src/lib/SavableObject.h"

namespace map {
	class World : public Object, public VirtualSharePtrObject<World>, public SavableObject {
		friend ChunkLoader;
		friend ChunkGenerator;
	protected:
		ChunkLoader chunk_loader;
		ChunkGenerator chunk_generator;
		std::map<Coord2D, map::ChunkPtr> chunks;
		std::string code_name;
		std::string display_name;

		ChunkPtr ejectChunk(const Coord2D &position);
		void insertChunk(map::ChunkPtr chunk);

		explicit World(const std::string &codeName);
	public:
		static WorldPtr create(const std::string &codeName);
		~World() override;

		bool hasChunk(const Coord2D &position);
		ChunkWPtr getChunk(const Coord2D &position);
		void loadForPlayer(game::PlayerPtr &player);
		void requestChunk(Coord2D position);

		void syncChunkWithLoader();

		const std::string &getDisplayName() const;
		void setDisplayName(const std::string &displayName);
		const std::string &getCodeName() const;

		const std::map<Coord2D, map::ChunkPtr> &getLoadedChunks() const;

		const Signal<ChunkPtr> onChunkInserted;
		const Signal<ChunkPtr> onChunkEjected;

		//region SavableObject
	public:
		boost::filesystem::path getDirectory() const;
		boost::filesystem::path getSavePath(AppSettings &app_settings) const override;
		json toJSON() const override;
	protected:
		void acceptState(json &json_obj) override;
		//endregion
	};
}
