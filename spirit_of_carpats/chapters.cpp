#include "chapters.h"
#include "location.h"
void createLevel1(sf::RenderWindow& window, sf::Sprite& backgroundSprite) {
    std::cout << "Запускаємо Level 1..." << std::endl;
    Player pl;
       
    sf::Texture newBackgroundTexture;
    if (!newBackgroundTexture.loadFromFile("assets/img/background_level 2.png")) {
        std::cerr << "неможливо завантажити background.jpg!" << std::endl;
        return;
    }
    backgroundSprite.setTexture(newBackgroundTexture);

    //КОМЕНТАРІ НЕ ВИДАЛЯТИ ЦЕ КОД З ЯКИМ Я БУДУ ПРАЦЮВАТИ

    /*sf::Texture news_peper;
    if (!news_peper.loadFromFile("assets/img/torn newspaper.png")) {
        std::cerr << "неможливо завантажити background.jpg!" << std::endl;
        return;
    }
    news_Sprite.setTexture(news_peper);*/
    /*news_Sprite.setPosition(Vector2f(-65.f, 20.f));*/

    /*sf::Texture BackgorundContinet;
    if (!BackgorundContinet.loadFromFile("some bg")) {
        std::cerr << "неможливо завантажити background.jpg!" << std::endl;
        return;
    }
    SpriteBgCountined.setTexture(BackgorundContinet);*/
    /*SpriteBgCountined.setPosition(sf::Vector2f(100.f, 100.f));*/
    
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
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            window.clear();
            window.draw(backgroundSprite);
            //ТУТ ТОЖЕ НЕ ВИДАЛЯТИ,Я ТЕСТУЮ!!!!!!!!!!
            /*window.draw(SpriteBgCountined);*/
            /*window.draw(news_Sprite);*/
            createLevels1(window, backgroundSprite, backButtonForChap, pl);
            window.display();
        }
    }
}
