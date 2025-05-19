#pragma once

#define THREAD_COUNT 10

inline HANDLE hThreads_full[THREAD_COUNT];
inline HANDLE hStartEvents_full[THREAD_COUNT];

inline bool isRunning_full[THREAD_COUNT] = { false };
inline volatile bool running_full = true;

inline DWORD WINAPI Threads_full(LPVOID lpParameter)
{
    int threadNum = static_cast<int>(reinterpret_cast<size_t>(lpParameter));;
    char letter = 'A';

    while (running_full)
    {
        WaitForSingleObject(hStartEvents_full[threadNum], INFINITE);
        ResetEvent(hStartEvents_full[threadNum]);

        while (running_full && isRunning_full[threadNum])
        {
            DWORD result = WaitForSingleObject(hStartEvents_full[threadNum], 0);
            if(result == WAIT_OBJECT_0)
            {
                break;
            }

            std::cout << letter << (threadNum + 1) << std::endl;
            letter++;

            if(letter > 'Z') letter = 'A';
            Sleep(2000);
        }
    }
    return 0;
}

inline void program2_full()
{
    for (auto & i : hStartEvents_full)
    {
        i = CreateEvent(
            nullptr,
            TRUE,
            FALSE,
            nullptr);
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        hThreads_full[i] = CreateThread(
            nullptr,
            0,
            Threads_full,
            reinterpret_cast<LPVOID>(i),
            0,
            nullptr);
    }

    std::string command;
    std::cout << "Enter command: ";
    while (true)
    {
        std::getline(std::cin, command);

        if (command.rfind("start ", 0) == 0)
        {
            if (const int threadNum = std::stoi(command.substr(6)) - 1;
                threadNum >= 0 && threadNum < THREAD_COUNT)
            {
                isRunning_full[threadNum] = true;
                SetEvent(hStartEvents_full[threadNum]);
            }
            else
            {
                std::cout << "Incorrect thread number" << std::endl;
            }
        }
        else if (command.rfind("stop ", 0) == 0)
        {
            if (const int threadNum = std::stoi(command.substr(5)) - 1;
                threadNum >= 0 && threadNum < THREAD_COUNT)
            {
                isRunning_full[threadNum] = false;
                ResetEvent(hStartEvents_full[threadNum]);
            }
            else
            {
                std::cout << "Incorrect thread number" << std::endl;
            }
        }
        else if (command == "exit")
        {
            running_full = false;
            std::cout << "Closing program..." << std::endl;

            for (const auto & i : hStartEvents_full)
            {
                SetEvent(i);
            }

            for (int i = 0; i < THREAD_COUNT; i++)
            {
                WaitForSingleObject(hThreads_full[i], INFINITE);
                CloseHandle(hThreads_full[i]);
                CloseHandle(hStartEvents_full[i]);
            }
            return;
        }
        else
        {
            std::cout << "Incorrect command, use: start X, stop X, exit" << std::endl;
        }
    }
}