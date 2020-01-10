/**
 * @file Factory.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Factory.h"
#include "type_ids.h"

#include "Blocks.h"

block::BlockPtr block::Factory::create(json &data) {

	if (!data[JSON_ATTR_TYPE_ID].is_number_integer())
		throw zprException("solid_block::Factory::create", "wrong json");

	BlockTypeId type_id = data[JSON_ATTR_TYPE_ID];

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

		case TYPE_ID_BRICK:
			block = std::make_shared<Brick>(data);
			break;

		case TYPE_ID_LOG:
			block = std::make_shared<Log>(data);
			break;

		case TYPE_ID_COBBLESTONE:
			block = std::make_shared<Cobblestone>(data);
			break;

		case TYPE_ID_WOOD:
			block = std::make_shared<Wood>(data);
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
