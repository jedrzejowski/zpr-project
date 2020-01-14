/**
 * @file WorldManager.test.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "WorldManager.h"

#include <boost/filesystem/operations.hpp>
#include <boost/test/unit_test.hpp>

const char *TEST1_CN = "test1";
const char *TEST2_CN = "test2";

BOOST_AUTO_TEST_CASE(test_map_WorldManager_opening) {
	auto &world_manager = map::WorldManager::get();

	map::WorldWPtr world_wptr;

	{
		auto world_ptr = world_manager.openWorld(TEST1_CN);
		world_wptr = world_ptr;
		BOOST_CHECK(world_ptr.use_count() == 1);
	}

	BOOST_CHECK(world_wptr.expired());

	{
		auto world_ptr = world_manager.openWorld(TEST2_CN);
		world_wptr = world_ptr;
		BOOST_CHECK(world_ptr.use_count() == 1);
	}

	BOOST_CHECK(world_wptr.expired());

	BOOST_CHECK(world_manager.exists(TEST1_CN));
	BOOST_CHECK(world_manager.exists(TEST2_CN));
}

BOOST_AUTO_TEST_CASE(test_map_WorldManager_delete) {
	auto &world_manager = map::WorldManager::get();

	{
		auto world_ptr1 = world_manager.openWorld(TEST1_CN);
		auto world_ptr2 = world_manager.openWorld(TEST2_CN);

		BOOST_CHECK(world_manager.exists(TEST1_CN));
		BOOST_CHECK(world_manager.exists(TEST2_CN));
	}

	{
		world_manager.deleteWorld(TEST1_CN);

		BOOST_CHECK(!world_manager.exists(TEST1_CN));
		BOOST_CHECK(world_manager.exists(TEST2_CN));

		BOOST_CHECK(!boost::filesystem::is_directory(world_manager.getWorldsDirectory() / TEST1_CN));
	}
}