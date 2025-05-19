#pragma once

#define THREAD_COUNT 10

inline std::vector<std::thread> threads2_new;
inline std::atomic<bool> running2_new = true;
inline std::atomic<bool> isRunning2_new[THREAD_COUNT] = {};
inline std::condition_variable condVars2_new[THREAD_COUNT];
inline std::mutex mtx2_new[THREAD_COUNT];

inline void Threads_new(int threadNum)
{
    char letter = 'A';

    while (running2_new)
    {
        std::unique_lock lock(mtx2_new[threadNum]);
        condVars2_new[threadNum].wait(lock, [threadNum]
        {
            return isRunning2_new[threadNum] || !running2_new;
        });

        if (!running2_new) break;

        while (isRunning2_new[threadNum] && running2_new)
        {
            std::cout << letter << threadNum + 1 << std::endl;
            if (letter == 'Z')
            {
                letter = 'A';
            }
            else
            {
                letter = letter + 1;
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}

inline void program2_new()
{
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threads2_new.emplace_back(Threads_new, i);
    }

    std::string command;
    std::cout << "Enter command: ";

    while (true)
    {
        std::getline(std::cin, command);

        if (command.rfind("start ", 0) == 0)
        {
            int threadNum = std::stoi(command.substr(6)) - 1;
            if (threadNum >= 0 && threadNum < THREAD_COUNT)
            {
                isRunning2_new[threadNum] = true;
                condVars2_new[threadNum].notify_one();
            }
            else
            {
                std::cout << "Incorrect thread number\n";
            }
        }
        else if (command.rfind("stop ", 0) == 0)
        {
            int threadNum = std::stoi(command.substr(5)) - 1;
            if (threadNum >= 0 && threadNum < THREAD_COUNT)
            {
                isRunning2_new[threadNum] = false;
            }
            else
            {
                std::cout << "Incorrect thread number\n";
            }
        }
        else if (command == "exit")
        {
            std::cout << "Closing program...\n";
            running2_new = false;

            for (auto & condVar : condVars2_new)
            {
                condVar.notify_one();
            }

            for (auto& t : threads2_new)
            {
                if (t.joinable())
                {
                    t.join();
                }
            }
            return;
        }
        else
        {
            std::cout << "Incorrect command, use: start X, stop X, exit\n";
        }
    }
}