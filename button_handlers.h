#ifndef BUTTON_HANDLERS_H
#define BUTTON_HANDLERS_H

inline void custom_hover(sf::RectangleShape& rect, const sf::Vector2i& mousePos)
{
    if(rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        rect.setFillColor(sf::Color(20, 222, 97, 255));
    }
    else
    {
        rect.setFillColor(sf::Color(61, 166, 101, 255));
    }
}

inline int draw_button1(sf::RenderWindow &window, const sf::Font& text, const sf::Vector2i& mousePos)
{
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(61, 166, 101, 255));
    rect.setPosition(sf::Vector2f(150, 200));
    rect.setSize(sf::Vector2f(250, 100));

    sf::Text for_button;
    for_button.setFont(text);
    for_button.setCharacterSize(20);
    for_button.setFillColor(sf::Color::White);
    for_button.setPosition(sf::Vector2f(220, 235));
    for_button.setString("Zadanie 1");

    custom_hover(rect, mousePos);

    window.draw(rect);
    window.draw(for_button);

    return 1;
}

inline int draw_button2(sf::RenderWindow &window, const sf::Font& text, const sf::Vector2i& mousePos)
{
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(61, 166, 101, 255));
    rect.setPosition(sf::Vector2f(600, 200));
    rect.setSize(sf::Vector2f(250, 100));

    sf::Text for_button;
    for_button.setFont(text);
    for_button.setCharacterSize(20);
    for_button.setFillColor(sf::Color::White);
    for_button.setPosition(sf::Vector2f(670, 235));
    for_button.setString("Zadanie 2");

    custom_hover(rect, mousePos);

    window.draw(rect);
    window.draw(for_button);

    return 2;
}

inline int draw_button3(sf::RenderWindow &window, const sf::Font& text, const sf::Vector2i& mousePos)
{
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(61, 166, 101, 255));
    rect.setPosition(sf::Vector2f(150, 500));
    rect.setSize(sf::Vector2f(250, 100));

    sf::Text for_button;
    for_button.setFont(text);
    for_button.setCharacterSize(20);
    for_button.setFillColor(sf::Color::White);
    for_button.setPosition(sf::Vector2f(220, 535));
    for_button.setString("Zadanie 3");

    custom_hover(rect, mousePos);

    window.draw(rect);
    window.draw(for_button);

    return 3;
}

inline int draw_button4(sf::RenderWindow &window, const sf::Font& text, const sf::Vector2i& mousePos)
{
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color(61, 166, 101, 255));
    rect.setPosition(sf::Vector2f(600, 500));
    rect.setSize(sf::Vector2f(250, 100));

    sf::Text for_button;
    for_button.setFont(text);
    for_button.setCharacterSize(20);
    for_button.setFillColor(sf::Color::White);
    for_button.setPosition(sf::Vector2f(670, 535));
    for_button.setString("Zadanie 4");

    custom_hover(rect, mousePos);

    window.draw(rect);
    window.draw(for_button);

    return 4;
}

#endif //BUTTON_HANDLERS_H
