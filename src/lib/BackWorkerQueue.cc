/**
 * @file BackWorkerQueue.cc
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

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
	Function function;

	while (!endWorker) {

		{
			waitingForData.lock();
			waitingForData.unlock();
		}

		{
			std::lock_guard<std::mutex> lock(queueAccess);
			if (queue.empty()) {
				waitingForData.lock();
				continue;
			}
			function = queue.front();
			queue.pop();
		}

		function();
	}
}

void BackWorkerQueue::push(const BackWorkerQueue::Function &function) {
	std::lock_guard<std::mutex> lock(queueAccess);
	queue.push(function);

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
