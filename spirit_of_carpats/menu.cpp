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

void Menu::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window) {
    if (event->is<sf::Event::MouseButtonPressed>()) {
        auto mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (newGameButton.getGlobalBounds().contains(mouseWorldPos)) {
            std::cout << "Натиснуто: New Game!" << std::endl;
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

void printBackgroundImg() {
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Spirit of Carpats");

    // Завантаження текстури для фону
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/img/backgroundMenu.png")) {
        cout << "Помилка: неможливо завантажити backgroundMenu.png!" << std::endl;
    }

    // Створення спрайта фону
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale({static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x, static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y});

    // Завантаження шрифту
    sf::Font font;
    if (!font.openFromFile("assets/fonts/alagard-12px-unicode.ttf")) {
        cout << "Помилка: не вдалося завантажити шрифт!" << std::endl;
    }

    Menu menu(font);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else
                menu.handleEvent(event, window);
        }

        window.clear();
        window.draw(backgroundSprite);
        menu.draw(window);
        window.display();
    }
}