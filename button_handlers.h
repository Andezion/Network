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

inline int button_handler(sf::RenderWindow &window, const sf::Font& text, const sf::Vector2i& mousePos)
{
    // Begin of button 1
    sf::RectangleShape rect1;
    rect1.setFillColor(sf::Color(61, 166, 101, 255));
    rect1.setPosition(sf::Vector2f(150, 200));
    rect1.setSize(sf::Vector2f(250, 100));

    sf::Text for_button1;
    for_button1.setFont(text);
    for_button1.setCharacterSize(20);
    for_button1.setFillColor(sf::Color::White);
    for_button1.setPosition(sf::Vector2f(220, 235));
    for_button1.setString("Zadanie 1");

    custom_hover(rect1, mousePos);

    window.draw(rect1);
    window.draw(for_button1);
    // End of button 1


    // Begin of button 2
    sf::RectangleShape rect2;
    rect2.setFillColor(sf::Color(61, 166, 101, 255));
    rect2.setPosition(sf::Vector2f(600, 200));
    rect2.setSize(sf::Vector2f(250, 100));

    sf::Text for_button2;
    for_button2.setFont(text);
    for_button2.setCharacterSize(20);
    for_button2.setFillColor(sf::Color::White);
    for_button2.setPosition(sf::Vector2f(670, 235));
    for_button2.setString("Zadanie 2");

    custom_hover(rect2, mousePos);

    window.draw(rect2);
    window.draw(for_button2);
    // End of button 2


    // Begin of button 3
    sf::RectangleShape rect3;
    rect3.setFillColor(sf::Color(61, 166, 101, 255));
    rect3.setPosition(sf::Vector2f(150, 500));
    rect3.setSize(sf::Vector2f(250, 100));

    sf::Text for_button3;
    for_button3.setFont(text);
    for_button3.setCharacterSize(20);
    for_button3.setFillColor(sf::Color::White);
    for_button3.setPosition(sf::Vector2f(220, 535));
    for_button3.setString("Zadanie 3");

    custom_hover(rect3, mousePos);

    window.draw(rect3);
    window.draw(for_button3);
    // End of button 3


    // Begin of button 4
    sf::RectangleShape rect4;
    rect4.setFillColor(sf::Color(61, 166, 101, 255));
    rect4.setPosition(sf::Vector2f(600, 500));
    rect4.setSize(sf::Vector2f(250, 100));

    sf::Text for_button4;
    for_button4.setFont(text);
    for_button4.setCharacterSize(20);
    for_button4.setFillColor(sf::Color::White);
    for_button4.setPosition(sf::Vector2f(670, 535));
    for_button4.setString("Zadanie 4");

    custom_hover(rect4, mousePos);

    window.draw(rect4);
    window.draw(for_button4);
    // End of button 4

    if(rect1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        return 1;
    }
    if(rect2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        return 2;
    }
    if(rect3.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        return 3;
    }
    if(rect4.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
        return 4;
    }
    return 0;
}

#endif //BUTTON_HANDLERS_H
