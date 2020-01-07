//
// Created by adam on 08.11.2019.
//

#include "BackWorkerQueue.h"

BackWorkerQueue::BackWorkerQueue() :
		mainThreadId(std::this_thread::get_id()),
		thread(&BackWorkerQueue::threadWorker, this) {
}

BackWorkerQueue::~BackWorkerQueue() {
	endWorker = true;
	waitingForData.unlock();

	thread.join();
}


void BackWorkerQueue::threadWorker() {
	while (!endWorker) {
		queueAccess.lock();

		if (queue.empty()) {
			queueAccess.unlock();
			waitingForData.lock();

			if (endWorker) return;

			waitingForData.lock();
			waitingForData.unlock();

			queueAccess.lock();
		}

		if (endWorker) return;

		Function function = queue.front();
		queue.pop();
		queueAccess.unlock();

		function();
	}
}

void BackWorkerQueue::push(const BackWorkerQueue::Function &function) {
	queueAccess.lock();

	queue.push(function);

	queueAccess.unlock();
	waitingForData.unlock();
}

bool BackWorkerQueue::isDestroying() {
	return endWorker;
}

void BackWorkerQueue::awaitForQueueEnd() {
	endWorker = true;
	waitingForData.unlock();

	thread.join();
	thread = std::thread(&BackWorkerQueue::threadWorker, this);

	endWorker = false;
}
