#pragma once

inline void Thread1_new()
{
    std::cout << "Hello world!!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

inline void program1_new()
{
    std::thread thread1(Thread1_new);
    if (thread1.joinable())
    {
        thread1.join();
    }
    else
    {
        std::cout << "Creating thread failed!" << std::endl;
    }
}
