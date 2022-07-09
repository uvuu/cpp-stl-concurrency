#include "thread_execution.h"

#include <iostream>
#include <string>
#include <thread>

void runExampleThreadExecution()
{

    // If you will remove the constness here than it is necessary to pass args
    // to the function with a std::ref() wrapper because it is impossible to
    // assign a rvalue to a non-stant reference. The rvalue appears here because
    // the way args passing to the std::thread object, i.e. as rvalues.
    const auto func = [](auto count, /*const*/ std::string& phrase)
    {
        for (decltype(count) i = {}; i < count; ++i)
        {
            std::cout << i << " " << phrase;
        }
    };

    std::string str1 = "I'm trying to learn how to use this thing...\n";
    std::string str2 = "Just show me your true power!\n";

    // We may avoid using the std::ref() wrappers there if we resotre constness to the lambda argument
    std::thread t1{ func, 1000, std::ref(str1) };
    std::thread t2{ func, 1000, std::ref(str2) };

    // We cannot detach threads before joining because we will face exception.
    // At the same time using detach() without join() probably will lead to the inability
    // to complete execution of these threads because of their determination after main()
    // goes out of scope.
    //t1.detach();
    //t2.detach();

    // We need to join these threads otherwise we will face std::terminate
    // if the threads are still in progress.
    t1.join();
    t2.join();
}
