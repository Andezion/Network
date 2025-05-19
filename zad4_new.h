#pragma once

inline std::map<int, std::future<void>> tasks;
inline std::map<int, std::atomic<bool>> is_Running;
inline std::mutex taskMutex;
inline std::mutex coutMutex;
inline std::mutex inputMutex;

inline void Thread4(const int user_pick)
{
    char letter = 'A';

    while (is_Running[user_pick])
    {
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << letter << (user_pick == 9 ? 0 : user_pick + 1) << std::endl;
        }
        letter++;
        if (letter > 'Z') letter = 'A';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Thread " << user_pick << " stopped." << std::endl;
    }
}

inline void StartThreads()
{
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        is_Running[i] = true;
        tasks[i] = std::async(std::launch::async, Thread4, i);
    }
}

inline extern void StartThread(int threadNum)
{
    std::lock_guard<std::mutex> lock(taskMutex);

    if (tasks.find(threadNum) == tasks.end())
    {
        is_Running[threadNum] = true;
        tasks[threadNum] = std::async(std::launch::async, Thread4, threadNum);
        std::cout << "Thread " << threadNum << " started.\n";
    }
}

inline void StopThread(int threadNum)
{
    std::lock_guard<std::mutex> lock(taskMutex);

    if (tasks.find(threadNum) != tasks.end())
    {
        is_Running[threadNum] = false;

        tasks[threadNum].wait();

        tasks.erase(threadNum);
        {
            std::lock_guard<std::mutex> lock1(coutMutex);
            std::cout << "Thread " << threadNum << " deleted.\n";
        }
    }
    else
    {
        std::lock_guard<std::mutex> lock1(coutMutex);
        std::cout << "Thread " << threadNum << " not found.\n";
    }
}

inline void StopAllThreads()
{
    std::lock_guard<std::mutex> lock(taskMutex);
    for (auto& [num, running] : is_Running)
    {
        running = false;
    }
    tasks.clear();
}

inline void program4_new()
{
    StartThreads();

    std::string command;
    while (true)
    {
        std::lock_guard<std::mutex> lock(inputMutex);
        std::cin >> command;

        if (command == "exit")
        {
            StopAllThreads();
            break;
        }
        switch (std::stoi(command))
        {
            case 1: StopThread(1); break;
            case 2: StopThread(2); break;
            case 3: StopThread(3); break;
            case 4: StopThread(4); break;
            case 5: StopThread(5); break;
            case 6: StopThread(6); break;
            case 7: StopThread(7); break;
            case 8: StopThread(8); break;
            case 9: StopThread(9); break;
            case 0: StopThread(0); break;
            default: std::cout << "Error!" << std::endl; return;
        }
    }

    std::cout << "Exiting program.\n";
}