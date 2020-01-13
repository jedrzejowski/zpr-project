/**
 * @file Factory.test.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Factory.h"
#include "Blocks.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_block_Factory_clone) {

	block::BlockPtr block1 = std::make_shared<block::Brick>();
	block::BlockPtr block2 = block::Factory::clone(block1);
	block::BlockPtr block3 = block::Factory::clone(block2);

	BOOST_CHECK(block1->typeId() == block3->typeId());
}