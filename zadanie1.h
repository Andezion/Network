#ifndef ZADANIE1_H
#define ZADANIE1_H


inline std::string threadOutput = "Waiting for thread...";
inline std::mutex textMutex;

inline bool threadRunning = false;

inline void ThreadFunction()
{
    DWORD threadId = GetCurrentThreadId();

    Sleep(1000);

    {
        std::lock_guard<std::mutex> lock(textMutex);
        threadOutput = "Hello World!\n"
                       "Thread ID: " + std::to_string(threadId);
    }

    Sleep(2000);

    {
        std::lock_guard<std::mutex> lock(textMutex);
        threadOutput += "\nThread finished!";
    }

    Sleep(1000);

    {
        std::lock_guard<std::mutex> lock(textMutex);
        threadOutput = "Waiting for thread...";
    }

    Sleep(1000);

    threadRunning = false;
}

inline void Program1()
{
    if (!threadRunning)
    {
        threadRunning = true;
        std::thread worker(ThreadFunction);
        worker.detach();
    }
}

inline void zadanie1(sf::RenderWindow &window, const sf::Font& text, int &what_to_show)
{
    sf::Text display;
    display.setFont(text);
    display.setCharacterSize(40);
    display.setFillColor(sf::Color::White);
    display.setPosition(sf::Vector2f(10, 10));
    display.setString("Zadanie 1");

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
        what_to_show = 0;
    }

    sf::RectangleShape main_activity;
    main_activity.setFillColor(sf::Color(184, 191, 204, 255));
    main_activity.setOutlineColor(sf::Color::Black);
    main_activity.setOutlineThickness(2);
    main_activity.setPosition(sf::Vector2f(100, 300));
    main_activity.setSize(sf::Vector2f(800, 400));

    sf::Text outputText;
    outputText.setFont(text);
    outputText.setCharacterSize(50);
    outputText.setFillColor(sf::Color::Black);
    outputText.setPosition(sf::Vector2f(170, 380));

    {
        std::lock_guard<std::mutex> lock(textMutex);
        outputText.setString(threadOutput);
    }

    Program1();

    custom_hover(rect, mouse_pos);

    window.draw(main_activity);
    window.draw(rect);
    window.draw(back);
    window.draw(display);
    window.draw(outputText);
}

#endif //ZADANIE1_H
