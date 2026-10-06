#ifndef FIZZ_BUZZ_H
#define FIZZ_BUZZ_H

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <vector>

class FizzBuzz
{
	int n;
	int i{1};

    std::vector<std::string> results;

	mutable std::mutex mtx;
	std::condition_variable cv;

    bool ehFizz(int i) const { return i % 3 == 0 && i % 5 != 0; }
    bool ehBuzz(int i) const { return i % 3 != 0 && i % 5 == 0; }
    bool ehFizzBuzz(int i) const { return i % 3 == 0 && i % 5 == 0; }
    bool ehNumber(int i) const { return i % 3 != 0 && i % 5 != 0; }

    bool invariant() const { 
        return 1 <= i && i <= n+1 
            && results.size() == static_cast<std::size_t>(i - 1); 
    }

public:

	explicit FizzBuzz(int n)
        pre(1 <= n && n <= 50)
        post(invariant());

	void fizz(std::function<void()> printFizz)
        pre(1 <= n && n <= 50)
        post(done());
	
    void buzz(std::function<void()> printBuzz)
        pre(1 <= n && n <= 50)
        post(done());   
	
    void fizz_buzz(std::function<void()> printFizzBuzz)
        pre(1 <= n && n <= 50)
        post(done());
	
    void number(std::function<void(int)> printNumber)
        pre(1 <= n && n <= 50)
        post(done());
   
    bool done() const 
    {
        std::lock_guard<std::mutex> lck(mtx);
        return i > n;
    }

    std::vector<std::string> getResults() const 
    { 
        std::lock_guard<std::mutex> lck(mtx);
        return this->results; 
    }
};

#endif
