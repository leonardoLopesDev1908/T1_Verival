#include "fizz_buzz.h"

#include <iostream>
#include <string>
#include <thread>
#include <vector>

std::vector<std::string> output;

void printFizz() 
{ 
    std::cout << "fizz ";
    output.push_back("fizz");
}

void printBuzz() 
{
    std::cout << "buzz ";
    output.push_back("buzz");
}

void printFizzBuzz()
{
    std::cout << "fizzbuzz ";
    output.push_back("fizzbuzz");
}

void printNumber(int i)
{
    std::cout << i << " ";
    output.push_back(std::to_string(i));
}

int main() 
{
    int n{1};
    std::cout << "Enter n: ";
    std::cin >> n;
    std::cout << "\n";

    FizzBuzz fizz(n);

    std::thread t_fizz(&FizzBuzz::fizz, &fizz, printFizz);
    std::thread t_buzz(&FizzBuzz::buzz, &fizz, printBuzz);
    std::thread t_fizz_buzz(&FizzBuzz::fizz_buzz, &fizz, printFizzBuzz);
    std::thread t_number(&FizzBuzz::number, &fizz, printNumber);
     
    t_fizz.join();
    t_buzz.join();
    t_fizz_buzz.join();
    t_number.join();

    for(std::string& i : output)
        std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}

