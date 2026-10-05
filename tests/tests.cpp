#include "fizz_buzz.h"

#include <gtest/gtest.h>

#include <thread>
#include <vector>

auto printFizz = []() {};
auto printBuzz = []() {};
auto printFizzBuzz = []() {};
auto printNumber = [](int) {};

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

    return fizz.getResults();
}

TEST(FizzBuzzContrato, NMenorQueMinimo)
{
    EXPECT_DEATH(FizzBuzz(0), "CONTRATO VIOLADO");
}

TEST(FizzBuzz, SequenciaCorreta1)
{
    std::vector<std::string> expected = {"1","2","fizz","4","buzz","fizz","7","8","fizz","buzz","11","fizz","13","14","fizzbuzz"};
    auto st = MethodTest(15);

    ASSERT_EQ(st.size(), expected.size()) << "Stacks results and expected are of unequal length";

    for (int i = 0; i < expected.size(); i++) 
    {
        EXPECT_EQ(expected[i], st[i]) << "Vectors results and expected differ at index " << i;
    }
}

TEST(FizzBuzz, SequenciaCorreta2)
{
    std::vector<std::string> expected = {"1","2","fizz","4","buzz","fizz","7","8","fizz","buzz"};
    auto st = MethodTest(10);

    ASSERT_EQ(st.size(), expected.size()) << "Stacks results and expected are of unequal length";

    for (int i = 0; i < expected.size(); i++) 
    {
        EXPECT_EQ(expected[i], st[i]) << "Vectors results and expected differ at index " << i;
    }
}
