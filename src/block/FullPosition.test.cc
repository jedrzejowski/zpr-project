/**
 * @file FullPosition.test.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "FullPosition.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(block_FullPosition_getNeighbor) {

	auto pos1 = block::FullPosition(
			Coord2D(7, 6),
			Coord3D(8, 9, 10)
	);

	auto pos2 = pos1.getNeighbor(-30, -40, -50);
	pos2 = pos2.getNeighbor(20, 30, 40);

	BOOST_CHECK(pos1 != pos2);

	pos2 = pos2.getNeighbor(30, 40, 50);
	pos2 = pos2.getNeighbor(-20, -30, -40);

	BOOST_CHECK(pos1 == pos2);
}