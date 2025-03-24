#ifndef ZADANIE2_H
#define ZADANIE2_H

#include "button_handlers.h"

inline std::map<int, bool> active_threads;

inline void zadanie2(sf::RenderWindow &window, const sf::Font& text, int &what_to_show)
{
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

    static std::string our_output;

    for (int i = 0; i < buttons.size(); i++)
    {
        if (buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (i % 2 == 0)
            {
                int thread_id = i / 2;
                active_threads[thread_id] = true;

                our_output = "";
                int counter = 0;
                for (char letter = 'A'; letter <= 'Z'; letter++)
                {
                    if(counter == 4)
                    {
                        our_output += letter + std::to_string(thread_id) + "\n";
                        counter = 0;
                    }
                    else
                    {
                        our_output += letter + std::to_string(thread_id) + " ";
                    }
                    counter++;
                }
                our_output += "\n";
            }
            else
            {
                int thread_id = i / 2;
                if(active_threads[thread_id] == false)
                {
                    our_output = "Thread " + std::to_string(thread_id) + " was not active!";
                }
                else
                {
                    our_output = "Thread " + std::to_string(thread_id) + " is stopped!";
                }
            }
        }
    }

    if (button_exit_prog.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        our_output = "All threads stopped!";
    }

    sf::Text outputText;
    outputText.setFont(text);
    outputText.setCharacterSize(20);
    outputText.setFillColor(sf::Color::Black);
    outputText.setPosition(sf::Vector2f(110, 410));
    outputText.setString(our_output);
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
