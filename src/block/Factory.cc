/**
 * @file Factory.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Factory.h"
#include "type_ids.h"

#include "types/Stone.h"
#include "types/Dirt.h"
#include "types/Water.h"
#include "types/Grass.h"
#include "types/Sand.h"

block::BlockPtr block::Factory::create(json &data) {

	if (!data[TYPE_ID_ATTR_NAME].is_number_integer())
		throw zprException("solid_block::Factory::create", "wrong json");

	BlockTypeId type_id = data[TYPE_ID_ATTR_NAME];

	block::BlockPtr block = nullptr;

	switch (type_id) {

		case TYPE_ID_STONE:
			block = std::make_shared<Stone>(data);
			break;

		case TYPE_ID_DIRT:
			block = std::make_shared<Dirt>(data);
			break;

		case TYPE_ID_WATER:
			block = std::make_shared<Water>(data);
			break;

		case TYPE_ID_GRASS:
			block = std::make_shared<Grass>(data);
			break;

		case TYPE_ID_SAND:
			block = std::make_shared<Sand>(data);
			break;

		default:
			throw WrongJsonException();
	}

	return block;
}

block::BlockPtr block::Factory::clone(BlockPtr &data) {
	auto j = data->toJSON();
	return create(j);
}
