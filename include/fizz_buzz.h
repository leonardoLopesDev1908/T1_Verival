#include <condition_variable>
#include <contracts>
#include <functional>
#include <iostream>
#include <mutex>

class FizzBuzz
{
	int n;
	int i;
	std::mutex mtx;
	std::condition_variable cv;

public:

	FizzBuzz(int n);
	void fizz(std::function<void()> printFizz);
	void buzz(std::function<void()> printBuzz);
	void fizzbuzz(std::function<void()> printFizzBuzz);
	void number(std::function<void(int)> printNumber);
};
