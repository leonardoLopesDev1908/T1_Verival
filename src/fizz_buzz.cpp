#include "fizz_buzz.h"

FizzBuzz::FizzBuzz(int n)
{
	this->n = n;
	this->i = 1;	
}

void FizzBuzz::fizz(std::function<void()> printFizz) 
{
	while(i <= n)
	{
		//pre condition
		std::unique_lock<std::mutex> lck(mtx);
		while(i <= n && !(i % 3 == 0 && i % 5 != 0)		
            cv.wait(lck);
		if(i <= n)
		{
			printFizz();
			i++;
		}
        cv.notify_all();
		//post condition
	}
}

void FizzBuzz::buzz(std::function<void()> printBuzz) 
{
	//pre condition
	std::unique_lock<std::mutex> lck(mtx);
	while(i <= n && !(i % 3 != 0 && i % 5 == 0)
	    cv.wait(lck);
	if(i <= n)
	{
		printBuzz();
		i++;
	}
	cv.notify_all();
}

void FizzBuzz::fizzbuzz(std::function<void()> printFizzBuzz) 
{
	//pre condition
	std::unique_lock<std::mutex> lck(mtx);
	while(i <= n && !(i % 3 == 0 && i % 5 == 0)
		cv.wait(lck);
	if(i <= n)
    {	
        printFizzBuzz();
		i++;
	}
	cv.notify_all();
    //post condition
}

void FizzBuzz::number(std::function<(int)> printNumber)
{
	//pre condition
	std::unique_lock<std::mutex> lck(mtx);
	while(i <= n && !(i % 3 != 0 && i % 5 != 0)
		cv.wait(lck);
	if(i <= n)
	{
		printNumber(i);
		i++;
	}
	cv.notify_all();
	//post condition
}
