#include "fizz_buzz.h"

#include <gtest>

#include <iostream>
#include <thread>
#include <vector>

std::vector<std::string> MethodTest(int n)
{
    FizzBuzz fizz(n);

    std::thread t_fizz(&FizzBuzz::fizz, &fizz, printFizz);
    std::thread t_buzz(&FizzBuzz::buzz, &fizz, printBuzz);
    std::thread t_fizz_buzz(&FizzBuzz::fizz_buzz, &fizz, printFizzBuzz);
    std::thread t_number(&FizzBuzz::number, &fizz, printNumber);
     
    t_fizz.join();
    t_buzz.join();
    t_fizz_buzz.join();
    t_number.join();

    return fizz.results;;
}

void test_one()
{

}

void test_two()
{

}

void test_three()
{

}

int main()
{


    return 0;
}