/**
 * @file Block.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include "src/_classdef.h"
#include "src/lib/Coord.hpp"
#include "lib/json.hpp"

using json = nlohmann::json;


namespace block {

	/**
	 * @brief Podstawowa klasa bloku, każdy blok dziedziczy po niej
	 */
	class Block : public VirtualSharePtrObject<Block> {
	protected:
		map::ChunkWPtr chunk;
		Coord3D position;

	public:

		explicit Block() = default;

		/**
		 * @brief Tworzenie bloku z obiektu json
		 * @param data
		 */
		explicit Block(json &data);

		~Block() override = default;

		/**
		 * @brief Wkłada blok do chunk'a
		 * @param chunk_ptr
		 * @param pos
		 */
		void setPosition(map::ChunkPtr &chunk_ptr, const Coord3D &pos);

		virtual void insertToBuffers(std::vector<engine::Point3DeX> &vertices,
									 std::vector<engine::EboTriangle> &indices) = 0;

		/**
		 * @brief Określa czy blok wypełnia całą przestrzeń jaką może wypełnić
		 * @return
		 */
		virtual bool isSolid();

		virtual json toJSON();

		/**
		 * @brief Każdy typ bloku musi mieć unikalne ID swojego typu
		 * @return
		 */
		virtual int typeId() const = 0;

		/**
		 * @brief Pobiera sąsiadujący blok
		 * @param dx
		 * @param dy
		 * @param dz
		 * @return
		 */
		BlockWPtr getNeighbor(CoordDim dx, CoordDim dy, CoordDim dz) const;
	};

	extern const BlockWPtr Air;
	engine::SquareTextureReference getBlockTexture(int x, int y);
}

