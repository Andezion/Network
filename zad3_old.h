#pragma once

inline CRITICAL_SECTION critical;
inline HANDLE hThreads[THREAD_COUNT];
inline DWORD threadIds[THREAD_COUNT];

[[noreturn]] inline DWORD WINAPI Thread3(LPVOID lpParameter)
{
    const int threadNum = static_cast<int>(reinterpret_cast<size_t>(lpParameter));

    while (true)
    {
        EnterCriticalSection(&critical);

        for (char letter = 'A'; letter <= 'Z'; letter++)
        {
            if (threadNum == 9)
            {
                std::cout << letter << 0 << std::endl;
            }
            else
            {
                std::cout << letter << threadNum + 1 << std::endl;
            }
            Sleep(100);
        }

        LeaveCriticalSection(&critical);

        Sleep(1000);
    }
}

inline void program3_old()
{
    InitializeCriticalSection(&critical);

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        hThreads[i] = CreateThread(
            nullptr,
            0,
            Thread3,
            reinterpret_cast<LPVOID>(static_cast<size_t>(i)),
            0,
            &threadIds[i]);

        if (hThreads[i] == nullptr)
        {
            std::cerr << "Error in thread: " << i + 1 << std::endl;
            return;
        }
    }

    WaitForMultipleObjects(THREAD_COUNT, hThreads, TRUE, INFINITE);

    DeleteCriticalSection(&critical);
}
