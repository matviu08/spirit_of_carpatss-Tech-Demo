#include "menu.h"




Menu::Menu(sf::Font& font) : newGameButton(font), settingsButton(font), quitButton(font) {

    newGameButton.setString("New Game"); // Текст кнопки
    newGameButton.setCharacterSize(50);  // Розмір шрифту
    newGameButton.setFillColor(sf::Color::White); // Колір тексту
    newGameButton.setPosition({ 380.f, 400.f }); // Позиція на екрані

    settingsButton.setString("Settings");
    settingsButton.setCharacterSize(50);
    settingsButton.setFillColor(sf::Color::White);
    settingsButton.setPosition({ 400.f, 500.f });

    quitButton.setString("Quit");
    quitButton.setCharacterSize(50);
    quitButton.setFillColor(sf::Color::White);
    quitButton.setPosition({ 445.f, 600.f });

}

const float SCALE = 50.0f; // Box2D units to pixels
const float CHARACTER_HALF_WIDTH = 0.5f;  // Box2D units
const float CHARACTER_HALF_HEIGHT = 1.0f; // Box2D units

void Menu::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window) {
    if (event->is<sf::Event::MouseButtonPressed>()) {
        auto mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (newGameButton.getGlobalBounds().contains(mouseWorldPos)) {
            std::cout << "Натиснуто: New Game!" << std::endl;
            
            createLevel();
            
        }
        else if (settingsButton.getGlobalBounds().contains(mouseWorldPos)) {
            std::cout << "Натиснуто: Settings!" << std::endl;
        }
        else if (quitButton.getGlobalBounds().contains(mouseWorldPos)) {
            std::cout << "Натиснуто: Quit!" << std::endl;
            window.close();
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(newGameButton);
    window.draw(settingsButton);
    window.draw(quitButton);
}
