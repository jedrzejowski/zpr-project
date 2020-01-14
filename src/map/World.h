/**
 * @file World.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <map>
#include "boost/filesystem/path.hpp"
#include "src/_classdef.h"
#include "src/lib/Object.h"
#include "src/lib/Signal.hpp"
#include "src/lib/SavableObject.h"
#include "ChunkGenerator.h"
#include "ChunkLoader.h"

namespace map {

	/**
	 * @brief Świat gry
	 *
	 * Cały świat gry jest w czterech klasach, na początku był jedna, ale tak się rozrosła, że postanowiliśmy podzielić
	 * ją na cztery:
	 *  - World - do trzymania danych
	 *  - ChunkLoader - do ładowania chunk'ów
	 *  - ChunkGenerator - do generowania chunk'ów
	 *  - WorldManager - do zarządzania obiektami World
	 *
	 * Świat posiada dwie nazwy: kodową i użytkownika, pierwsza to rzeczywista nazwa świata, druga to ta pokazywana
	 * graczowi.
	 */
	class World : public Object, public VirtualSharePtrObject<World>, public SavableObject {
	public:
		using VirtualSharePtrObject<World>::shared_from_this;
		using VirtualSharePtrObject<World>::weak_from_this;
		friend ChunkLoader;
		friend ChunkGenerator;
		friend WorldManager;
	protected:
		ChunkLoader chunk_loader;
		ChunkGenerator chunk_generator;
		std::map<Coord2D, map::ChunkPtr> chunks;
		std::string code_name;
		std::string display_name;

		ChunkPtr ejectChunk(const Coord2D &position);
		void insertChunk(map::ChunkPtr chunk);

		explicit World(const std::string &codeName);
		static WorldPtr create(const std::string &codeName);
	public:
		~World() override;

		/**
		 * Zapytanie, czy chunk jest dostępny
		 * @param position
		 * @return
		 */
		bool hasChunk(const Coord2D &position);
		ChunkWPtr getChunk(const Coord2D &position);

		/**
		 * @brief prośba o wczytanie chunk'u dla gracza
		 * @param position
		 */
		void loadForPlayer(game::PlayerPtr &player);

		/**
		 * @brief prośba o wczytanie chunk'u
		 * @param position
		 */
		void requestChunk(Coord2D position);

		void syncChunkWithLoader();

		const std::string &getDisplayName() const;
		void setDisplayName(const std::string &displayName);

		/**
		 * Nazwa kodowa świata
		 * @return
		 */
		const std::string &getCodeName() const;

		const std::map<Coord2D, map::ChunkPtr> &getLoadedChunks() const;

		const Signal<ChunkPtr> onChunkInserted;
		const Signal<ChunkPtr> onChunkEjected;

		//region SavableObject
	public:
		std::filesystem::path getDirectory() const;
		std::filesystem::path getSavePath() const override;
		json toJSON() const override;
		void fullSave();
	protected:
		void acceptState(json &json_obj) override;
		//endregion
	};
}
