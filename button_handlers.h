#ifndef BUTTON_HANDLERS_H
#define BUTTON_HANDLERS_H

inline int draw_button1(sf::RenderWindow &window)
{
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(sf::Vector2f(150, 200));
    rect.setSize(sf::Vector2f(250, 100));

    window.draw(rect);
    return 1;
}

inline int draw_button2(sf::RenderWindow &window)
{
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(sf::Vector2f(150, 200));
    rect.setSize(sf::Vector2f(250, 100));

    window.draw(rect);
    return 1;
}

inline int draw_button3(sf::RenderWindow &window)
{
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(sf::Vector2f(150, 200));
    rect.setSize(sf::Vector2f(250, 100));

    window.draw(rect);
    return 1;
}

inline int draw_button4(sf::RenderWindow &window)
{
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(sf::Vector2f(150, 200));
    rect.setSize(sf::Vector2f(250, 100));

    window.draw(rect);
    return 1;
}

#endif //BUTTON_HANDLERS_H
