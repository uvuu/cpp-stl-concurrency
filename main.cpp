#include <iostream>
#include <string>
#include <thread>

using namespace std;

void f(int& i){}

int main()
{
    cout << "Hello World!" << endl;

    const auto func = [](auto count, const std::string& phrase)
    {
        for (decltype(count) i = {}; i < count; ++i)
        {
            std::cout << phrase;
        }
    };

    const auto func1 = [](auto count, const std::string& phrase)
    {
        for (decltype(count) i = {}; i < count; ++i)
        {
            std::cerr << phrase;
        }
    };

    std::string str1 = "I'm trying to learn how to use this thing...\n";
    std::string str2 = "Just show me your true power!\n";

    // It's a pity! Seems std::jthread doesn't present in my version on the compiler/library(gcc-8)
    // and I need to have the new one(gcc-10) but if to use it I need to install a new version of OS
    //std::jthread t1{ func, 1000, std::ref(str1)};
    //std::jthread t2{ func, 1000, str2};

    std::thread t1{ func, 1000000, std::ref(str1)};
    std::thread t2{ func1, 1000000, str2};

    t1.join();
    t2.join();


    return 0;
}
