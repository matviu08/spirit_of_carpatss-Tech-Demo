#include "chapters.h"
#include "location.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
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

   /* sf::Texture news_peper;
    if (!news_peper.loadFromFile("assets/img/torn newspaper.png")) {
        std::cerr << "неможливо завантажити background.jpg!" << std::endl;
        return;
    }
    news_Sprite.setTexture(news_peper);
    news_Sprite.setPosition(Vector2f(-65.f, 20.f));*/

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

    /*std::vector<sf::Texture> treeTextures;
    std::vector<sf::Texture> news_peperTextures;
    sf::Texture bushTexture, rockTexture, grassTexture, groundTexture;

    sf::Texture treeTex;
    if (treeTex.loadFromFile("assets/img/tree1.png")) {
        treeTextures.push_back(treeTex);
    }
    else {
        std::cerr << "Не вдалося завантажити tree1.png" << std::endl;
    }

    sf::Texture newsTex;
    if (newsTex.loadFromFile("assets/img/torn newspaper.png")) {
        news_peperTextures.push_back(newsTex);
    }
    else {
        std::cerr << "Не вдалося завантажити torn newspaper.png" << std::endl;
    }

    if (!rockTexture.loadFromFile("assets/img/Kamin.png")) {
        std::cerr << "Не вдалося завантажити rock.png" << std::endl;
    }
    if (!grassTexture.loadFromFile("assets/img/grass_new.png")) {
        std::cerr << "Не вдалося завантажити grass.png" << std::endl;
    }

    std::vector<sf::Sprite> trees, bushes, rocks, grassSprites, groundTiles, news_tiles;

    generateForestScene(
        window,
        trees,
        bushes,
        rocks,
        grassSprites,
        groundTiles,
        news_tiles,
        treeTextures,
        news_peperTextures,
        bushTexture,
        rockTexture,
        grassTexture,
        groundTexture
    );*/

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            window.clear();

            window.draw(backgroundSprite);
            //for (const auto& tile : groundTiles) window.draw(tile);
            //for (const auto& grass : grassSprites) window.draw(grass);
            //for (const auto& tree : trees) window.draw(tree);
            //for (const auto& bush : bushes) window.draw(bush);
            //for (const auto& rock : rocks) window.draw(rock);
            //for (const auto& news : news_tiles) window.draw(news);

            window.draw(backgroundSprite);
            //ТУТ ТОЖЕ НЕ ВИДАЛЯТИ,Я ТЕСТУЮ!!!!!!!!!!
            /*window.draw(SpriteBgCountined);*/
           /* window.draw(news_Sprite);*/
            createLevels1(window, backgroundSprite, backButtonForChap, pl);
            window.display();
        }
    }
}
