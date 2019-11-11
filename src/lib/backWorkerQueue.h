#pragma once

#include <mutex>
#include <queue>
#include <functional>
#include <thread>

#include "src/_classdef.h"

class BackWorkerQueue {
	typedef std::function<void()> Function;
private:
	std::thread::id mainThreadId;
	std::mutex objectAlive;

	std::queue<Function> queue;
	std::mutex waitingForData, queueAccess;
	std::thread thread;

	bool destructing = false;

	void threadWorker();
public:
	BackWorkerQueue();
	~BackWorkerQueue();
	void push(Function function);

	bool isDestroying();
};

