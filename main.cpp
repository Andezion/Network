#include <iostream>
#include <windows.h>
#include <thread>
#include <future>
#include <vector>
#include <atomic>
#include <map>
#include <mutex>
#include <chrono>

#include <SFML/Graphics.hpp>
#include "button_handlers.h"

#include "zadanie1.h"
#include "zadanie2.h"
#include "zadanie3.h"
#include "zadanie4.h"

#define THREAD_COUNT 10

HANDLE hThreads[THREAD_COUNT];
DWORD threadIds[THREAD_COUNT];

volatile bool isRunning[THREAD_COUNT] = { false };
volatile int letterIndex[THREAD_COUNT] = {};

DWORD WINAPI Thread2(LPVOID lpParameter)
{
    int threadNum = static_cast<int>(reinterpret_cast<size_t>(lpParameter));
    char letter = 'A' + letterIndex[threadNum];

    while (true)
    {
        if (!isRunning[threadNum])
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
        letterIndex[threadNum]++;

        if (letter > 'Z')
        {
            letter = 'A';
            letterIndex[threadNum] = 0;
        }

        Sleep(1000);
    }
}
void Program2()
{
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        hThreads[i] = CreateThread(
            nullptr,
            0,
            Thread2,
            reinterpret_cast<LPVOID>(static_cast<size_t>(i)),
            CREATE_SUSPENDED,
            &threadIds[i]);

        if (hThreads[i] == nullptr)
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
                isRunning[threadNum] = true;
                ResumeThread(hThreads[threadNum]);
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
                isRunning[threadNum] = false;
                SuspendThread(hThreads[threadNum]);
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
                isRunning[i] = false;
                TerminateThread(hThreads[i], 0);
                CloseHandle(hThreads[i]);
            }
            return;
        }
        else
        {
            std::cout << "Incorrect command, use: start X, stop X, exit" << std::endl;
        }
    }
}

CRITICAL_SECTION critical;

DWORD WINAPI Thread3(LPVOID lpParameter)
{
    int threadNum = static_cast<int>(reinterpret_cast<size_t>(lpParameter));

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
void Program3()
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

std::map<int, std::future<void>> tasks;
std::map<int, std::atomic<bool>> is_Running;
std::mutex taskMutex;
std::mutex coutMutex;
std::mutex inputMutex;

void Thread4(const int user_pick)
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
void StartThreads()
{
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        is_Running[i] = true;
        tasks[i] = std::async(std::launch::async, Thread4, i);
    }
}
void StopThread(int threadNum)
{
    std::lock_guard<std::mutex> lock(taskMutex);

    if (tasks.find(threadNum) != tasks.end())
    {
        is_Running[threadNum] = false;
        tasks.erase(threadNum);
        {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << "Thread " << threadNum << " deleted.\n";
        }
    }
    else
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Thread " << threadNum << " not found.\n";
    }
}
void StopAllThreads()
{
    std::lock_guard<std::mutex> lock(taskMutex);
    for (auto& [num, running] : is_Running)
    {
        running = false;
    }
    tasks.clear();
}
void Program4()
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
        int num = std::stoi(command);
        switch (num)
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

int what_to_show = 0;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Lab1");
    sf::Font text;
    text.loadFromFile("text.ttf");

    while(window.isOpen())
    {
        sf::Event event{};
        {
            while(window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
        }

        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

        window.clear(sf::Color(76, 112, 176, 255));

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && what_to_show == 0)
        {
            what_to_show = button_handler(window, text, mouse_pos);
        }

        switch (what_to_show)
        {
            case 1: zadanie1(window, text, what_to_show); break;
            case 2: zadanie2(window, text, what_to_show); break;
            case 3: zadanie3(window, text, what_to_show); break;
            case 4: zadanie4(window, text, what_to_show); break;
            default: button_handler(window, text, mouse_pos); break;
        }

        window.display();
    }

    return 0;
}
