#include "chapter1_house.h"
#include "logick.h"

void generateHomeScene(
    sf::RenderWindow& window,
    std::vector<sf::Sprite>& bed,
    std::vector<sf::Sprite>& bacground_home,
    const sf::Texture& background_home_texture,
    const sf::Texture& bed_texture) {
    
    bed.clear();
    bacground_home.clear();
    
    //sf::FloatRect Colision(300, 100, 100, 100);
    //sf::Vector2f velociry(0.1f, 0.0f);


    const float windowWidth = static_cast<float>(window.getSize().x);
    const float windowHeight = static_cast<float>(window.getSize().y);
    const float textureWidth_home = static_cast<float>(background_home_texture.getSize().x);
    const float textureHeight_home = static_cast<float>(background_home_texture.getSize().y);

    float scaleX = windowWidth / textureWidth_home;
    float scaleY = windowHeight / textureHeight_home;

    for (int i = 0; i < 1; ++i) {
        sf::Sprite backgroundSprite_home(background_home_texture);
        backgroundSprite_home.setScale(Vector2f(scaleX, scaleY));
        backgroundSprite_home.setPosition(sf::Vector2f(i * windowWidth, 0.f));
        bacground_home.push_back(backgroundSprite_home);
    }

    //const float baseWidth = 1920.f;
    //const float baseHeight = 1080.f;

    //start width for adaptation
    const float statWindth = 1920.f;
    const float statHeinght = 1080.f;

    sf::Vector2u windowSieStat = window.getSize();

    //вісі позицій
    float xRatio_stat = static_cast<float>(windowSieStat.x) / statWindth;
    float yRatio_stat = static_cast<float>(windowSieStat.y) / statHeinght;

    //start position
    const float startValueX = 1000.f;
    const float startValueY = 857.f;

    float start_bedX = startValueX * xRatio_stat;
    float y = startValueY * yRatio_stat;


    sf::Sprite bed_spawn(bed_texture);
    float scale = 0.8f + static_cast<float>(rand() % 40) / 100.0f;
    float uniformScale = min(xRatio_stat, yRatio_stat);
    bed_spawn.setScale(sf::Vector2f(scale * uniformScale, scale * uniformScale));

    float x = start_bedX;

    bed_spawn.setPosition(Vector2f(x, y));


    //for (int i = 0; i < newsCount; ++i) {
    //    sf::Sprite newspaper(newspaperTexture);
    //    float scale = 0.8f + static_cast<float>(rand() % 40) / 100.0f;
    //    float uniformScale = min(xRatio, yRatio);
    //    newspaper.setScale(sf::Vector2f(scale * uniformScale, scale * uniformScale));

    //    float rotation = static_cast<float>((rand() % 31) - 15); // [-15, 15]
    //    newspaper.setRotation(sf::degrees(rotation));

    //    float x = startX + i * spacing;
    //    newspaper.setPosition(sf::Vector2f(x, y));

    //    news.push_back(newspaper);
    //}


}
