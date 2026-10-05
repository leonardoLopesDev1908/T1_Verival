#ifndef FIZZ_BUZZ_H
#define FIZZ_BUZZ_H

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <stack>

class FizzBuzz
{
	int n;
	int i{1};

    std::stack<std::string> results;

	mutable std::mutex mtx;
	std::condition_variable cv;

public:

	explicit FizzBuzz(int n)
        pre(1 <= n && n <= 50)
        post(invariant());

	void fizz(std::function<void()> printFizz)
        pre(1 <= n && n <= 50)
        post(invariant());
	
    void buzz(std::function<void()> printBuzz)
        pre(1 <= n && n <= 50)
        post(invariant());
	
    void fizz_buzz(std::function<void()> printFizzBuzz)
        pre(1 <= n && n <= 50)
        post(invariant());
	
    void number(std::function<void(int)> printNumber)
        pre(1 <= n && n <= 50)
        post(invariant());
   
    bool done() const 
    {
        std::lock_guard<std::mutex> lck(mtx);
        return i > n;
    }

    bool invariant() const { return 1 <= i && i <= n+1; }

    std::stack<std::string> getResults() const { return this->results; }
};

#endif
