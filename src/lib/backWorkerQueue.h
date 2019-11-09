#pragma once

#include <mutex>
#include <queue>
#include <functional>
#include <thread>

class BackWorkerQueue {
	typedef std::function<void()> Function;
private:
	std::thread::id mainThreadId;

	std::queue<Function> queue;
	std::mutex waitingForData, queueAccess;
	std::thread thread;

	void pop();

	void threadWorker();
public:
	BackWorkerQueue();
	void push(Function &function);
};

