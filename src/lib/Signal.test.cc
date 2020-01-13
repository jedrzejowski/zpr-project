/**
 * @file Signal.test.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "Signal.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_Signal) {

	Signal<int> mySignal;

	int number = 0;

	mySignal.connect([&](int n) {
		number += n;
	});

	mySignal([&](int n) {
		number += n + 1;
	});

	mySignal.emit(3);
	mySignal(4);

	BOOST_CHECK(number == 16);
}

