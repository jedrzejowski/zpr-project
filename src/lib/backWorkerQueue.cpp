//
// Created by adam on 08.11.2019.
//

#include "backWorkerQueue.h"

BackWorkerQueue::BackWorkerQueue() :
		mainThreadId(std::this_thread::get_id()),
		thread(&BackWorkerQueue::threadWorker, this) {
}


void BackWorkerQueue::threadWorker() {
	while (!destructing) {
		queueAccess.lock();

		if (queue.empty()) {
			queueAccess.unlock();
			waitingForData.lock();

			if (destructing) return;

			waitingForData.lock();
			waitingForData.unlock();

			queueAccess.lock();
		}

		Function function = queue.front();
		queue.pop();
		queueAccess.unlock();

		function();
	}
}

void BackWorkerQueue::push(BackWorkerQueue::Function function) {
	queueAccess.lock();

	queue.push(function);

	queueAccess.unlock();
	waitingForData.unlock();
}

bool BackWorkerQueue::isDestroying() {
	return destructing;
}

BackWorkerQueue::~BackWorkerQueue() {
	destructing = true;
	waitingForData.unlock();

	thread.join();
}
