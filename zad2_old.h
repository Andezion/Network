#pragma once

#define THREAD_COUNT 10

inline HANDLE hThreads_old[THREAD_COUNT];
inline DWORD threadIds_old[THREAD_COUNT];

inline volatile bool isRunning_old[THREAD_COUNT] = { false };
inline int letterIndex_old[THREAD_COUNT] = {};

[[noreturn]] inline DWORD WINAPI Thread2_old(LPVOID lpParameter)
{
    int threadNum = static_cast<int>(reinterpret_cast<size_t>(lpParameter));
    char letter = 'A' + letterIndex_old[threadNum];

    while (true)
    {
        if (!isRunning_old[threadNum])
        {
            Sleep(100);
            continue;
        }

        if (threadNum == 9)
        {
            std::cout << letter << 0 << std::endl;
        }
        else
        {
            std::cout << letter << threadNum + 1 << std::endl;
        }

        letter++;
        letterIndex_old[threadNum]++;

        if (letter > 'Z')
        {
            letter = 'A';
            letterIndex_old[threadNum] = 0;
        }

        Sleep(2000);
    }
}

inline void program2_old()
{
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        hThreads_old[i] = CreateThread(
            nullptr,
            0,
            Thread2_old,
            reinterpret_cast<LPVOID>(static_cast<size_t>(i)),
            CREATE_SUSPENDED,
            &threadIds_old[i]);

        if (hThreads_old[i] == nullptr)
        {
            std::cerr << "Error in thread: " << i + 1 << std::endl;
            return;
        }
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
                isRunning_old[threadNum] = true;
                ResumeThread(hThreads_old[threadNum]);
            }
            else
            {
                std::cout << "Incorrect thread number" << std::endl;
            }
        }
        else if (command.rfind("stop ", 0) == 0)
        {
            int threadNum = std::stoi(command.substr(5)) - 1;
            if (threadNum >= 0 && threadNum < THREAD_COUNT)
            {
                isRunning_old[threadNum] = false;
                SuspendThread(hThreads_old[threadNum]);
            }
            else
            {
                std::cout << "Incorrect thread number" << std::endl;
            }
        }
        else if (command == "exit")
        {
            std::cout << "Closing program..." << std::endl;
            for (int i = 0; i < THREAD_COUNT; i++)
            {
                isRunning_old[i] = false;
                TerminateThread(hThreads_old[i], 0);
                CloseHandle(hThreads_old[i]);
            }
            return;
        }
        else
        {
            std::cout << "Incorrect command, use: start X, stop X, exit" << std::endl;
        }
    }
}