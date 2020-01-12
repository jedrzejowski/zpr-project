/**
 * @file Sub3Dobj.test.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Sub3DObj.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(engine_Sub3DObj_parenting) {

	struct Sub3DObj2 : engine::Sub3DObj {
		explicit Sub3DObj2(engine::Sub3DObjPtr parent) : Sub3DObj(parent) {}
		void updateBuffers() {};
	};

	auto one_ptr = std::make_shared<Sub3DObj2>(nullptr);

	{
		auto two_ptr = std::make_shared<Sub3DObj2>(one_ptr);
		auto three_ptr = std::make_shared<Sub3DObj2>(one_ptr);

		BOOST_CHECK(one_ptr->getChildCount() == 2);
	}

	BOOST_CHECK(one_ptr->getChildCount() == 0);
}