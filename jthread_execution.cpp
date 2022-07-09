#include "jthread_execution.h"

#include <iostream>
#include <string>
#include <thread>

#ifndef JTHREADS_ENABLED // See CMakeLists.txt for defenition

void runExampleJthreadExecution()
{
    std::cout << "Sorry, but seems your compiler doesn't support the std::jthread feature!";
}

#else // JTHREADS_ENABLED is true

using namespace std::chrono_literals; // We need it to use time literals like 200ms, 5s, etc.

// TODO: Figure out why we cannot use auto instead of int for the 'count' variable
void regularFunction(std::stop_token stoken, int count, const std::string& phrase)
{
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
 
    for (decltype(count) i = {}; i < count; ++i)
    {
        if (stoken.stop_requested())
        {
            std::cout << "We are leaving!\n";
            return;
        }

        std::cout << i << " " << phrase;
    }
}

class Functor
{
public:
    void method(int count, const std::string& phrase, std::stop_source ssource)
    {
        std::this_thread::sleep_for(20ms);
        ssource.request_stop(); // The sc callback will be executed after this call

        regularFunction({}, count, phrase);
    }

    void operator()(std::stop_token stoken, auto count, const std::string& phrase)
    {
        regularFunction(stoken, count, phrase);
    }
};

void runExampleJthreadExecution()
{
    std::string str1 = "I'm trying to learn how to use this thing...\n";
    std::string str2 = "Just show me your true power!\n";

    // The way to stop a thread execution
    std::jthread t1{ regularFunction, 100, std::ref(str1)};
    std::this_thread::sleep_for(1ms);

    t1.request_stop();
    t1.join(); // Just to check that the thread is finished

    // The way to stop a thread execution from another created thread
    std::jthread t2{ Functor{}, 1000, str1 };
    auto stoken = t2.get_stop_token();
    auto ssource = t2.get_stop_source();

    std::stop_callback sc{
        stoken,
        []() {
            std::cout << "Thread id: " << std::this_thread::get_id()
                << std::endl << "Stop callback is just here!" << std::endl;
        }
    };
    std::jthread t3{ &Functor::method, Functor{}, 1000, str2, ssource };
}
#endif