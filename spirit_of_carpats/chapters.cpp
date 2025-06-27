#include "chapters.h"
#include "location.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void createLevel1(sf::RenderWindow& window, sf::Sprite& backgroundSprite, const std::optional<sf::Event>& event, Menu& menu) {
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

    extern bool tohnoEnglish;
    sf::Text backButtonForChap(font);
    if (tohnoEnglish) {
        backButtonForChap.setString("Exit the game");
    }
    else {
        backButtonForChap.setString(L"Вихід з гри");
    }
    backButtonForChap.setCharacterSize(50);
    backButtonForChap.setFillColor(sf::Color::White);
    backButtonForChap.setPosition(sf::Vector2f(20.f, 20.f));

    sf::Text chapterText(font);
    if (tohnoEnglish) {
        chapterText.setString("Chapter 1");
    }
    else {
        chapterText.setString(L"Чаптерс 1");
    }
    chapterText.setCharacterSize(80);
    chapterText.setFillColor(sf::Color::White);
    sf::Vector2f pos_1(static_cast<float>(windowSize.x) / 2 - chapterText.getLocalBounds().size.x / 2, static_cast<float>(windowSize.y) / 2);
    chapterText.setPosition(pos_1);

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
            window.clear(sf::Color::Black);
            window.draw(chapterText);
            window.display();
            sf::sleep(sf::seconds(2));
            for (auto& tile : tiledBackgrounds) {
                window.draw(tile);
            }
            Generation_of_chapter1(window, backgroundSprite, backButtonForChap, pl, font, event, menu);
            window.display();
    }
    
}
