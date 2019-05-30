// Restaurant.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "ThreadPool.h"

void notMain();

int main()
{
	notMain();
	std::this_thread::sleep_for(std::chrono::seconds(10));
}

void notMain()
{
	ThreadPool tp;
	int i = 0;

	tp.AddWork([&i]() {
		std::cout << "Thread " << std::this_thread::get_id() << " is sleeping..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		i++;
		std::cout << "Thread " << std::this_thread::get_id() << " done sleeping." << std::endl;
		std::cout << i << std::endl;
	});

	tp.AddWork([&i]() {
		std::cout << "Thread " << std::this_thread::get_id() << " is sleeping..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		i++;
		std::cout << "Thread " << std::this_thread::get_id() << " done sleeping." << std::endl;
		std::cout << i << std::endl;
	});

	tp.AddWork([&i]() {
		std::cout << "Thread " << std::this_thread::get_id() << " is sleeping..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(7));
		i++;
		std::cout << "Thread " << std::this_thread::get_id() << " done sleeping." << std::endl;
		std::cout << i << std::endl;
	});
}