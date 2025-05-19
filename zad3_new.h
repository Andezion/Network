#pragma once

#define THREAD_COUNT 10

inline std::vector<std::thread> threads3_new;
inline std::mutex critical3;
inline std::atomic<bool> running3_new = true;

inline void Thread3_new(int threadNum)
{
    while (running3_new)
    {
        {
            std::lock_guard<std::mutex> lock(critical3);

            for (char letter = 'A'; letter <= 'Z'; letter++)
            {
                if (threadNum == 9)
                    std::cout << letter << 0 << std::endl;
                else
                    std::cout << letter << threadNum + 1 << std::endl;

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

inline void program3_new()
{
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threads3_new.emplace_back(Thread3_new, i);
    }

    for (auto& t : threads3_new)
    {
        if (t.joinable())
        {
            t.join();
        }
    }
}