#ifndef ZADANIE1_H
#define ZADANIE1_H

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

    custom_hover(rect, mouse_pos);

    window.draw(rect);
    window.draw(back);
    window.draw(display);
}

#endif //ZADANIE1_H
