#ifndef FIZZ_BUZZ_H
#define FIZZ_BUZZ_H

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>

class FizzBuzz
{
	int n;
	int i{1};
	std::mutex mtx;
	std::condition_variable cv;

public:

	explicit FizzBuzz(int n);

	void fizz(std::function<void()> printFizz);
	void buzz(std::function<void()> printBuzz);
	void fizz_buzz(std::function<void()> printFizzBuzz);
	void number(std::function<void(int)> printNumber);
};

#endif
