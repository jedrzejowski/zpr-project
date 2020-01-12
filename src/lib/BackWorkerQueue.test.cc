/**
 * @file BackWorkerQueue.test.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#include "BackWorkerQueue.h"
#include <chrono>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(BackWorkerQueue_1) {

	std::mutex mutex;
	int counter = 0;

	auto bump = [&]() {
		mutex.lock();
		counter++;
		mutex.unlock();
	};

	auto sleep = [](int seconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(seconds));
	};

	auto worker1 = new BackWorkerQueue();
	auto worker2 = new BackWorkerQueue();

	worker1->push([&] {
		sleep(1);
		bump();
	});

	worker2->push([&] {
		sleep(2);
		bump();
	});

	worker1->push([&] {
		sleep(3);
		bump();
	});

	worker2->push([&] {
		sleep(4);
		bump();
	});

	worker1->awaitForQueueEnd();
	worker2->awaitForQueueEnd();

	delete (worker1);
	delete (worker2);

	BOOST_CHECK(counter == 4);
}