#include "fizz_buzz.h"

#include <string>

FizzBuzz::FizzBuzz(int n)
{
	this->n = n;
    contract_assert(n >= 1);           
	
    this->i = 1;
}

void FizzBuzz::fizz(std::function<void()> printFizz) 
{
	while(true)
	{
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, [this] { return i > n || (i % 3 == 0 && i % 5 != 0); });
		if(i > n) return;

        contract_assert(invariant());           
        contract_assert(i % 3 == 0 && i % 5 != 0);    
		
        printFizz();
        results.push("fizz");
        int savedIndex = i;
        i++;
        
        contract_assert(i == savedIndex + 1);
        contract_assert(invariant());

        cv.notify_all();
	}
}

void FizzBuzz::buzz(std::function<void()> printBuzz) 
{
	while(true)
    {
	    std::unique_lock<std::mutex> lck(mtx);
	    cv.wait(lck, [this] { return i > n || (i % 3 != 0 && i % 5 == 0); });
		if(i > n) return;

        contract_assert(invariant());           
        contract_assert(i % 3 != 0 && i % 5 == 0);    
		
        printBuzz();
        results.push("buzz");
        int savedIndex = i;
        i++;
        
        contract_assert(i == savedIndex + 1);
        contract_assert(invariant());

        cv.notify_all();
    }
}

void FizzBuzz::fizz_buzz(std::function<void()> printFizzBuzz) 
{
	while(true)
    {
	    std::unique_lock<std::mutex> lck(mtx);
	    cv.wait(lck, [this] { return i > n || (i % 3 == 0 && i % 5 == 0); });
		if(i > n) return;

        contract_assert(invariant());           
        contract_assert(i % 3 == 0 && i % 5 == 0);    
		if(i > n) return;
		
        printFizzBuzz();
        results.push("fizzbuzz");
        int savedIndex = i;
        i++;
        
        contract_assert(i == savedIndex + 1);
        contract_assert(invariant());

        cv.notify_all();
    }
}

void FizzBuzz::number(std::function<void(int)> printNumber)
{
	while(true)
    {
    	std::unique_lock<std::mutex> lck(mtx);
	    cv.wait(lck, [this] { return i > n || (i % 3 != 0 && i % 5 != 0); });
		if(i > n) return;

        contract_assert(invariant());           
        contract_assert(i % 3 != 0 && i % 5 != 0);    
		
        printNumber(i);
        results.push(std::to_string(i));
        int savedIndex = i;
        i++;
        
        contract_assert(i == savedIndex + 1);
        contract_assert(invariant());

        cv.notify_all();
    }
}
