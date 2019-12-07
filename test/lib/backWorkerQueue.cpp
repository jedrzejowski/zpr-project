#include <chrono>

#include "src/lib/backWorkerQueue.h"

std::mutex mutex;
int counter = 0;

void bump() {
	mutex.lock();

	counter++;

	mutex.unlock();
}

void sleep(int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

int main() {
	auto worker1 = new BackWorkerQueue();
	auto worker2 = new BackWorkerQueue();

	worker1->push([] {
		logger.log("start").log(1);

		sleep(1);
		bump();

		logger.log("end").log(1);
	});

	worker2->push([] {
		logger.log("start").log(2);

		sleep(2);
		bump();

		logger.log("end").log(2);
	});

	worker1->push([] {
		logger.log("start").log(3);

		sleep(3);
		bump();

		logger.log("end").log(3);
	});

	worker2->push([] {
		logger.log("start").log(4);

		sleep(4);
		bump();

		logger.log("end").log(4);
	});

	return 1;

//	worker1->awaitForQueueEnd();
//	worker2->awaitForQueueEnd();
//
//	delete (worker1);
//	delete (worker2);
//
//	return 4 - counter;
}