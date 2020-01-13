/**
 * @file LiveData.test.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "LiveData.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_LiveData_float) {
	float number1 = 1.23456789;
	float number2 = 9.87654321;

	LiveData<float> liveNumber = number1;

	BOOST_CHECK(liveNumber.get() == number1);

	bool wasValidCallback = false;

	liveNumber.onChange([&](const float &old_value, const float &new_value) {
		wasValidCallback = old_value == number1 && number2 == new_value;
	});

	liveNumber.set(number2);

	BOOST_CHECK(wasValidCallback);

	BOOST_CHECK(liveNumber.get() == number2);
}