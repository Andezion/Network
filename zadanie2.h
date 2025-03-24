#ifndef ZADANIE2_H
#define ZADANIE2_H

#include "button_handlers.h"

inline std::mutex outputLogsMutex;

#define thread_new_count 10
inline HANDLE hThreads2[thread_new_count];
inline DWORD thread_id2[thread_new_count];

inline volatile bool isRunning2[thread_new_count] = { false };
inline int letterIndex2[thread_new_count] = {};
inline volatile bool shouldExit2[thread_new_count] = { false };

inline std::vector<std::string> outputLogs;

inline DWORD WINAPI Thread22(LPVOID lpParameter)
{
    int threadNum = static_cast<int>(reinterpret_cast<size_t>(lpParameter));
    char letter = 'A' + letterIndex2[threadNum];

    while (!shouldExit2[threadNum])  // Цикл, пока поток не должен завершиться
    {
        if (!isRunning2[threadNum])
        {
            Sleep(100);  // Чтобы не грузить процессор
            continue;
        }

        {
            // Блокируем доступ к outputLogs (потребуется мьютекс)
            std::lock_guard<std::mutex> lock(outputLogsMutex);
            std::stringstream ss;
            ss << "Thread " << threadNum + 1 << ": " << letter;
            outputLogs.push_back(ss.str());
        }

        letter++;
        letterIndex2[threadNum]++;

        if (letter > 'Z') break;  // Завершаем поток после 'Z'
    }

    return 0;
}

inline void InitThreads2()
{
    for (int i = 0; i < thread_new_count; i++)
    {
        hThreads2[i] = CreateThread(
            nullptr,
            0,
            Thread22,
            reinterpret_cast<LPVOID>(static_cast<size_t>(i)),
            CREATE_SUSPENDED,
            &thread_id2[i]);

        if (hThreads2[i] == nullptr)
        {
            std::cerr << "Error creating thread: " << i + 1 << std::endl;
        }
    }
}

inline void StartThread2(const int threadNum)
{
    if (threadNum >= 0 && threadNum < thread_new_count)
    {
        if (hThreads2[threadNum] == nullptr)  // Если поток завершён, создаём новый
        {
            hThreads2[threadNum] = CreateThread(
                nullptr, 0, Thread22,
                reinterpret_cast<LPVOID>(static_cast<size_t>(threadNum)),
                0, &thread_id2[threadNum]
            );

            if (hThreads2[threadNum] == nullptr)
            {
                std::cerr << "Error creating thread: " << threadNum + 1 << std::endl;
                return;
            }
        }

        isRunning2[threadNum] = true;
        ResumeThread(hThreads2[threadNum]);

        {
            std::lock_guard<std::mutex> lock(outputLogsMutex);
            outputLogs.push_back("Started thread " + std::to_string(threadNum + 1));
        }
    }
}

inline void StopThread2(const int threadNum)
{
    if (threadNum >= 0 && threadNum < thread_new_count)
    {
        isRunning2[threadNum] = false;
        SuspendThread(hThreads2[threadNum]);
        outputLogs.push_back("Stopped thread " + std::to_string(threadNum + 1));
    }
}

void StopAllThreads2()
{
    for (int i = 0; i < thread_new_count; i++)
    {
        shouldExit2[i] = true;  // Устанавливаем флаг завершения потока
        isRunning2[i] = false;  // Останавливаем выполнение внутри цикла

        if (hThreads2[i] != nullptr)
        {
            WaitForSingleObject(hThreads2[i], INFINITE);  // Ждем завершения
            CloseHandle(hThreads2[i]);  // Закрываем дескриптор потока
            hThreads2[i] = nullptr;
        }
    }

    outputLogs.push_back("All threads stopped.");
}

inline void zadanie2(sf::RenderWindow &window, const sf::Font& text, int &what_to_show)
{
    InitThreads2();

    sf::Text display;
    display.setFont(text);
    display.setCharacterSize(40);
    display.setFillColor(sf::Color::White);
    display.setPosition(sf::Vector2f(10, 10));
    display.setString("Zadanie 2");

    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(850, 10));
    rect.setSize(sf::Vector2f(100, 50));
    rect.setFillColor(sf::Color(61, 166, 101, 255));

    sf::Text back;
    back.setFont(text);
    back.setCharacterSize(30);
    back.setString("Back");
    back.setFillColor(sf::Color::White);
    back.setPosition(sf::Vector2f(865, 15));

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    if(rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        StopAllThreads2();
        what_to_show = 0;
    }

    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonLabels;

    for (int i = 0; i < 4; i++)
    {
        sf::RectangleShape startButton(sf::Vector2f(120, 50));
        startButton.setPosition(sf::Vector2f(100, 100 + i * 60));
        startButton.setFillColor(sf::Color(61, 166, 101, 255));
        buttons.push_back(startButton);

        sf::Text startLabel;
        startLabel.setFont(text);
        startLabel.setCharacterSize(25);
        startLabel.setString("start " + std::to_string(i));
        startLabel.setFillColor(sf::Color::White);
        startLabel.setPosition(sf::Vector2f(105, 108 + i * 60));
        buttonLabels.push_back(startLabel);

        sf::RectangleShape stopButton(sf::Vector2f(120, 50));
        stopButton.setPosition(sf::Vector2f(435, 100 + i * 60));
        stopButton.setFillColor(sf::Color(166, 61, 61, 255));
        buttons.push_back(stopButton);

        sf::Text stopLabel;
        stopLabel.setFont(text);
        stopLabel.setCharacterSize(25);
        stopLabel.setString("stop " + std::to_string(i));
        stopLabel.setFillColor(sf::Color::White);
        stopLabel.setPosition(sf::Vector2f(445, 108 + i * 60));
        buttonLabels.push_back(stopLabel);
    }


    sf::RectangleShape button_exit_prog;
    button_exit_prog.setPosition(sf::Vector2f(780, 150));
    button_exit_prog.setSize(sf::Vector2f(120, 50));
    button_exit_prog.setFillColor(sf::Color(61, 166, 101, 255));

    sf::Text exit_prog;
    exit_prog.setFont(text);
    exit_prog.setCharacterSize(30);
    exit_prog.setString("exit");
    exit_prog.setFillColor(sf::Color::White);
    exit_prog.setPosition(sf::Vector2f(805, 155));

    sf::RectangleShape main_activity;
    main_activity.setFillColor(sf::Color(184, 191, 204, 255));
    main_activity.setOutlineColor(sf::Color::Black);
    main_activity.setOutlineThickness(2);
    main_activity.setPosition(sf::Vector2f(100, 350));
    main_activity.setSize(sf::Vector2f(800, 400));

    for (int i = 0; i < buttons.size(); i++)
    {
        if (buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (i % 2 == 0)
            {
                StartThread2(i / 2);
            }
            else
            {
                StopThread2(i / 2);
            }
        }
    }

    if (button_exit_prog.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        StopAllThreads2();
    }

    sf::Text outputText;
    outputText.setFont(text);
    outputText.setCharacterSize(20);
    outputText.setFillColor(sf::Color::Black);
    outputText.setPosition(sf::Vector2f(110, 410));

    std::string outputString;
    for (size_t i = (outputLogs.size() > 1 ? outputLogs.size() - 1 : 0); i < outputLogs.size(); i++)
    {
        outputString += outputLogs[i] + "\n";
    }
    outputText.setString(outputString);

    custom_hover(rect, mouse_pos);

    for (auto& button : buttons)
    {
        custom_hover(button, mouse_pos);
    }

    custom_hover(button_exit_prog, mouse_pos);

    window.draw(rect);
    window.draw(back);
    window.draw(display);

    window.draw(button_exit_prog);
    window.draw(exit_prog);

    for (auto& button : buttons) window.draw(button);
    for (auto& label : buttonLabels) window.draw(label);

    window.draw(main_activity);
    window.draw(outputText);
}

#endif //ZADANIE2_H
