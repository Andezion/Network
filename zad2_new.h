#pragma once

#define THREAD_COUNT 10

inline std::vector<std::thread> threads;
inline std::atomic<bool> running = true;
inline std::atomic<bool> isRunning[THREAD_COUNT] = {};
inline std::condition_variable condVars[THREAD_COUNT];
inline std::mutex mtx[THREAD_COUNT];

inline void threadFunction(int threadNum)
{
    char letter = 'A';

    while (running)
    {
        std::unique_lock lock(mtx[threadNum]);
        condVars[threadNum].wait(lock, [threadNum]
        {
            return isRunning[threadNum] || !running;
        });

        if (!running) break;

        while (isRunning[threadNum] && running)
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
        threads.emplace_back(threadFunction, i);
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
                isRunning[threadNum] = true;
                condVars[threadNum].notify_one();
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
                isRunning[threadNum] = false;
            }
            else
            {
                std::cout << "Incorrect thread number\n";
            }
        }
        else if (command == "exit")
        {
            std::cout << "Closing program...\n";
            running = false;

            for (auto & condVar : condVars)
            {
                condVar.notify_one();
            }

            for (auto& t : threads)
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