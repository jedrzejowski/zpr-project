/**
 * @file ChunkGenerator.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/lib/PerlinNoise.h"
#include "src/lib/Coord.hpp"
#include "src/lib/SavableObject.h"

namespace map {
	/**
	 * @brief Generator chunk'ów, patrz World
	 */
	class ChunkGenerator : public SavableObject {
		friend World;
	private:
		PerlinNoise noise;
		World *world;
	public:
		explicit ChunkGenerator(World *world);

		void fillChunk(ChunkPtr &chunk);

		//region SavableObject

	public:
		[[nodiscard]] boost::filesystem::path getSavePath() const override;
		[[nodiscard]] json toJSON() const override;

	protected:
		void acceptState(json &json_obj) override;

		//endregion
	};
}
