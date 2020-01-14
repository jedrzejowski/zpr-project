/**
 * @file ChunkLoader.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/lib/Coord.hpp"
#include "src/lib/Object.h"
#include "src/lib/BackWorkerQueue.h"
#include "ChunkGenerator.h"

namespace map {

	/**
	 * @brief Ładowanie chunk'ów, patrz World
	 */
	class ChunkLoader : public Object {
		friend World;
	private:
		World *world;
		BackWorkerQueuePtr worker_ptr = nullptr;

		std::list<Coord2D> chunks_to_remove;
		std::list<Coord2D> unloading_chunks_coords;

		std::list<Coord2D> loading_chunks_coords;
		std::list<map::ChunkPtr> chunks_to_add;

		std::mutex chunk_list_access;

		BackWorkerQueuePtr &getWorker();

	public:
		explicit ChunkLoader(World *world);

		void load(Coord2D coord);
		void unload(Coord2D coord);

		bool isChunkLoaded(const Coord2D &coord);
		bool isChunkLoading(const Coord2D &coord);
		bool isChunkUnloading(const Coord2D &coord);

		void syncWithWorld();
	};
}

