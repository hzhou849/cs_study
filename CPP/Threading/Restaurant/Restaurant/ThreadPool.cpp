#include "ThreadPool.h"
#include "Semaphore.h"

void ThreadPool::workLoop()
{
	while (true)
	{
		this->workSemaphore.wait();
		this->lock.lock();
		std::function<void()> work = this->tasks.front();
		this->tasks.pop();
		this->lock.unlock();
		work();
	}
}

void ThreadPool::AddWork(std::function<void()> work)
{
	this->lock.lock();
	this->tasks.push(work);
	this->lock.unlock();
	this->workSemaphore.notify();
}

ThreadPool::ThreadPool()
{
	for (int i = 0; i < 3; i++)
	{
		std::thread *t = new std::thread(&ThreadPool::workLoop, this);
		this->threads.push_back(t);
	}
}