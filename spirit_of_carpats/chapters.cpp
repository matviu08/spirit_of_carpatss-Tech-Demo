#include "chapters.h"


void createLevel1(sf::RenderWindow& window, sf::Sprite& backgroundSprite) {
    std::cout << "Запускаємо Level 1..." << std::endl;


    sf::Texture newBackgroundTexture;
    if (!newBackgroundTexture.loadFromFile("assets/img/Game_BackGround.png")) {
        std::cerr << "неможливо завантажити background.jpg!" << std::endl;
        return;
    }
    backgroundSprite.setTexture(newBackgroundTexture);

    sf::Font font;
    if (!font.openFromFile("assets/fonts/alagard-12px-unicode.ttf")) {
        cout << "Помилка: не вдалося завантажити шрифт!" << std::endl;
    }

    Player pl;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            window.clear();
            window.draw(backgroundSprite);
            pl.characterMovement(window, backgroundSprite);
            window.display();
        }
    }
}
