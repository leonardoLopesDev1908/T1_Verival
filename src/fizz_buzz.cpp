#include "fizz_buzz.h"

#include <string>

FizzBuzz::FizzBuzz(int n)
{
	this->n = n;
    contract_assert(n >= 1);           
    contract_assert(n <= 50);	
    this->i = 1;
}

void FizzBuzz::fizz(std::function<void()> printFizz) 
{
	while(true)
	{
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, [this] { return i > n || (ehFizz(i)); });
		if(i > n) return;

        contract_assert(ehFizz(i));    
		
        printFizz();
        results.push_back("fizz");
        i++;
        
        contract_assert(invariant());

        cv.notify_all();
	}
}

void FizzBuzz::buzz(std::function<void()> printBuzz) 
{
	while(true)
    {
	    std::unique_lock<std::mutex> lck(mtx);
	    cv.wait(lck, [this] { return i > n || (ehBuzz(i)); });
		if(i > n) return;

        contract_assert(ehBuzz(i));    
		
        printBuzz();
        results.push_back("buzz");
        i++;
        
        contract_assert(invariant());

        cv.notify_all();
    }
}

void FizzBuzz::fizz_buzz(std::function<void()> printFizzBuzz) 
{
	while(true)
    {
	    std::unique_lock<std::mutex> lck(mtx);
	    cv.wait(lck, [this] { return i > n || (ehFizzBuzz(i)); });
		if(i > n) return;

        contract_assert(ehFizzBuzz(i));    
		
        printFizzBuzz();
        results.push_back("fizzbuzz");
        i++;
        
        contract_assert(invariant());

        cv.notify_all();
    }
}

void FizzBuzz::number(std::function<void(int)> printNumber)
{
	while(true)
    {
    	std::unique_lock<std::mutex> lck(mtx);
	    cv.wait(lck, [this] { return i > n || (ehNumber(i)); });
        if(i > n) return;

        contract_assert(ehNumber(i));    
		
        printNumber(i);
        results.push_back(std::to_string(i));
        i++;
        
        contract_assert(invariant());

        cv.notify_all();
    }
}