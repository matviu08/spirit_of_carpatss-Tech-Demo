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
    backgroundSprite.setTexture(newBackgroundTexture);

    sf::Font font;
    if (!font.openFromFile("assets/fonts/alagard-12px-unicode.ttf")) {
        cout << "Помилка: не вдалося завантажити шрифт!" << std::endl;
    }

    sf::Text backButtonForChap(font);
    backButtonForChap.setString("Back to Chapters");
    backButtonForChap.setCharacterSize(50);
    backButtonForChap.setFillColor(sf::Color::White);
    backButtonForChap.setPosition(sf::Vector2f(20.f, 20.f));


    sf::Vector2f textureSize = Vector2f(newBackgroundTexture.getSize());

    int repeatCount = 5;

    std::vector<sf::Sprite> tiledBackgrounds;
    for (int i = 0; i < repeatCount; ++i) {
        sf::Sprite tile(backgroundSprite);
        tile.setPosition(sf::Vector2f(static_cast<float>(i * textureSize.x), 0.f));
        tiledBackgrounds.push_back(tile);
    }
    
    while (window.isOpen()) {
                
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            window.clear();

            for (auto& tile : tiledBackgrounds) {
                window.draw(tile);
            }

            window.draw(backgroundSprite);

            window.draw(backgroundSprite);

            createLevels1(window, backgroundSprite, backButtonForChap, pl, font, event);

            sf::FloatRect bgBounds = backgroundSprite.getGlobalBounds();
            float bgWidth = bgBounds.size.x;

            int repeatCount = 5;

            for (int i = 0; i < repeatCount; ++i) {
                sf::Sprite tiledBg = backgroundSprite;
                tiledBg.setPosition(Vector2f(i * bgWidth, 0.f));
                window.draw(tiledBg);
            }

            window.display();
        }
    
}
