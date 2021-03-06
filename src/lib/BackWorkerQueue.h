/**
 * @file BackWorkerQueue.h
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */

#pragma once

#include <mutex>
#include <queue>
#include <functional>
#include <thread>

#include "src/_classdef.h"

/**
 * @brief Implementuje kolejkę funkcji, które wykonując się w tle
 */
class BackWorkerQueue {
	typedef std::function<void()> Function;
private:
	std::thread::id mainThreadId;
	std::mutex objectAlive;

	std::queue<Function> queue;
	std::mutex waiting_for_data, queue_access;
	std::thread thread;

	bool endWorker = false;

	void threadWorker();
public:
	BackWorkerQueue();
	~BackWorkerQueue();
	void push(const Function &function);

	bool isDestroying();

	void awaitForQueueEnd();
};

