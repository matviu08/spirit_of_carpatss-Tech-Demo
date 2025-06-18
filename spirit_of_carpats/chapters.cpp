#include "chapters.h"
#include "location.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void createLevel1(sf::RenderWindow& window, sf::Sprite& backgroundSprite, const std::optional<sf::Event>& event) {
    std::cout << "Запускаємо Level 1..." << std::endl;
    Player pl;
       
    sf::Texture newBackgroundTexture;
    if (!newBackgroundTexture.loadFromFile("assets/img/levl1_bg.png")) {
        std::cerr << "неможливо завантажити background.jpg!" << std::endl;
        return;
    }

    sf::Vector2u textureSize = newBackgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    backgroundSprite.setScale(sf::Vector2f(scaleX, scaleY));
    backgroundSprite.setPosition(Vector2f(0.f, 0.f));

    sf::Font font;
    if (!font.openFromFile("assets/fonts/alagard-12px-unicode.ttf")) {
        cout << "Помилка: не вдалося завантажити шрифт!" << std::endl;
    }

    sf::Text backButtonForChap(font);
    backButtonForChap.setString("Back to Chapters");
    backButtonForChap.setCharacterSize(50);
    backButtonForChap.setFillColor(sf::Color::White);
    backButtonForChap.setPosition(sf::Vector2f(20.f, 20.f));

    sf::Vector2f textureSizeF = static_cast<sf::Vector2f>(sf::Vector2u(newBackgroundTexture.getSize()));
    int repeatCount = 5;

    std::vector<sf::Sprite> tiledBackgrounds;
    for (int i = 0; i < repeatCount; ++i) {
        sf::Sprite tile(backgroundSprite);
        tile.setPosition(sf::Vector2f(i * static_cast<float>(textureSize.x), 0.f));
        tiledBackgrounds.push_back(tile);
    }
    
    while (window.isOpen()) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            window.clear();
            for (auto& tile : tiledBackgrounds) {
                window.draw(tile);
            }
            createLevels1(window, backgroundSprite, backButtonForChap, pl, font, event);
            window.display();
        }
    
}
