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
	waiting_for_data.unlock();
	thread.join();
}


void BackWorkerQueue::threadWorker() {
	Function function;

	while (!endWorker) {

		{
			waiting_for_data.lock();
			waiting_for_data.unlock();
		}

		{
			std::lock_guard<std::mutex> lock(queue_access);
			if (queue.empty()) {
				waiting_for_data.lock();
				continue;
			}
			function = queue.front();
			queue.pop();
		}

		function();
	}
}

void BackWorkerQueue::push(const BackWorkerQueue::Function &function) {
	std::lock_guard<std::mutex> lock(queue_access);
	queue.push(function);

	waiting_for_data.unlock();
}

bool BackWorkerQueue::isDestroying() {
	return endWorker;
}

void BackWorkerQueue::awaitForQueueEnd() {
	endWorker = true;
	waiting_for_data.unlock();

	thread.join();
	thread = std::thread(&BackWorkerQueue::threadWorker, this);

	endWorker = false;
}
