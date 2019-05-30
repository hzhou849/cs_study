#pragma once
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Semaphore.h"

class ThreadPool
{
private:
	std::vector<std::thread*> threads;
	std::queue<std::function<void()>> tasks;
	std::mutex lock;
	Semaphore workSemaphore;
	void workLoop();
public:
	void AddWork(std::function<void()>);
	ThreadPool();
};