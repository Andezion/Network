#pragma once

inline DWORD WINAPI Thread1(LPVOID lpParameter)
{
    std::cout << "Hello world!!" << std::endl;
    return 0;
}

inline void program1_old()
{
    DWORD threadId;

    const HANDLE hThread = CreateThread(
        nullptr,
        0,
        Thread1,
        nullptr,
        0,
        &threadId);

    if(hThread == nullptr)
    {
        std::cout << "Creating thread failed!" << std::endl;
    }

    WaitForSingleObject(hThread, INFINITE);

    Sleep(1000);

    CloseHandle(hThread);
}