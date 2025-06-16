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

    
    while (window.isOpen()) {
        
        
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            window.clear();

            window.draw(backgroundSprite);


            window.draw(backgroundSprite);

            createLevels1(window, backgroundSprite, backButtonForChap, pl, font, event);

            sf::FloatRect bgBounds = backgroundSprite.getGlobalBounds();
            float bgWidth = bgBounds.size.x;

            int repeatCount = (window.getSize().x / bgWidth) + 2; // +2 на запас

            for (int i = 0; i < repeatCount; ++i) {
                sf::Sprite tiledBg = backgroundSprite;
                tiledBg.setPosition(Vector2f(i * bgWidth, 0.f));
                window.draw(tiledBg);
            }

            window.display();
        }
    
}
