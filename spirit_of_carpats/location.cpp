#include "location.h"

void generateHomeScene(
    sf::RenderWindow& window,
    std::vector<sf::Sprite>& bed,
    std::vector<sf::Sprite>& bacground_home,
    const sf::Texture& background_home_texture,
    const sf::Texture& bed_texture){
    bed.clear();
    bacground_home.clear();

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
    float uniformScale = min(xRatio_stat,yRatio_stat);
    bed_spawn.setScale(sf::Vector2f(scale * uniformScale, scale * uniformScale));

    float x = start_bedX;

    bed_spawn.setPosition(Vector2f(x,y));
   

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


void generateForestScene(
    sf::RenderWindow& window,
    std::vector<sf::Sprite>& ground,
    std::vector<sf::Sprite>& grass,
    std::vector<sf::Sprite>& rock,
    std::vector<sf::Sprite>& trees,
    std::vector<sf::Sprite>& news,
    std::vector<sf::Sprite>& background,
    const sf::Texture& grassTexture,
    const sf::Texture& rockTexture,
    const sf::Texture& treeTexture,
    const sf::Texture& backgroundTexture,
    const sf::Texture& newspaperTexture)
{
    // Очистка попередніх спрайтів
    trees.clear();
    rock.clear();
    news.clear();
    grass.clear();
    ground.clear();
    background.clear();

    const int backgroundRepeatCount = 10; // 🔹 Розширюємо фон для великої сцени

    // 🎨 Генерація повторюваного бекграунду
    const float windowWidth = static_cast<float>(window.getSize().x);
    const float windowHeight = static_cast<float>(window.getSize().y);
    const float textureWidth = static_cast<float>(backgroundTexture.getSize().x);
    const float textureHeight = static_cast<float>(backgroundTexture.getSize().y);

   
    float scaleX = windowWidth / textureWidth;
    float scaleY = windowHeight / textureHeight;

    

    for (int i = 0; i < backgroundRepeatCount; ++i) {
        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setScale(Vector2f(scaleX, scaleY)); 
        backgroundSprite.setPosition(sf::Vector2f(i * windowWidth, 0.f)); 
        background.push_back(backgroundSprite);
    }
   

    // 📰 Генерація газет
    const float baseWidth = 1920.f;
    const float baseHeight = 1080.f;
    sf::Vector2u windowSize = window.getSize();

    float xRatio = static_cast<float>(windowSize.x) / baseWidth;
    float yRatio = static_cast<float>(windowSize.y) / baseHeight;

    const float baseStartX = 1000.f;
    const float baseY = 857.f;
    const float baseSpacing = 1200.f;

    float startX = baseStartX * xRatio;
    float y = baseY * yRatio;
    float spacing = baseSpacing * xRatio;

    int newsCount = 3;

    srand(time(NULL));
    float agle = rand() % (100 - 0) + 0;



    for (int i = 0; i < newsCount; ++i) {
        sf::Sprite newspaper(newspaperTexture);
        float scale = 0.8f + static_cast<float>(rand() % 40) / 100.0f;
        float uniformScale = min(xRatio, yRatio);
        newspaper.setScale(sf::Vector2f(scale * uniformScale, scale * uniformScale));
        
        float rotation = static_cast<float>((rand() % 31) - 15); // [-15, 15]
        newspaper.setRotation(sf::degrees(rotation));

        float x = startX + i * spacing;
        newspaper.setPosition(sf::Vector2f(x, y));

        news.push_back(newspaper);
    }
    // базове розширення
    const float baseWidth_for_tree = 1920.f;
    const float baseHeight_for_tree = 1080.f;

    float xRatio_tree = static_cast<float>(windowSize.x) / baseWidth;
    float yRatio_tree = static_cast<float>(windowSize.y) / baseHeight;

    //adaprive generation of tree
    const int treeCount = 3;
    const float baseTreeX = 1400.f;
    const float baseTreeY = 425.f;
    const float baseTreeSpacing = 1200.f;

    float treeX = baseTreeX * xRatio;
    float treeY = baseTreeY * yRatio;
    float treeSpacing = baseTreeSpacing * xRatio;

    for (int i = 0; i < treeCount; ++i) {
        sf::Sprite tree(treeTexture);
        float x = treeX + i * treeSpacing;
        tree.setPosition(sf::Vector2f(x, treeY));
        tree.setScale(sf::Vector2f(xRatio, yRatio)); 
        trees.push_back(tree);
    }

    // adaprive generation of rock
    const int rockCount = 1;
    const float baseRockX = -75.f;
    const float baseRockY = 975.f;

    float rockX = baseRockX * xRatio;
    float rockY = baseRockY * yRatio;

    for (int i = 0; i < rockCount; ++i) {
        sf::Sprite rockSprite(rockTexture);
        rockSprite.setPosition(sf::Vector2f(rockX, rockY));
        rockSprite.setScale(sf::Vector2f(xRatio, yRatio));
        rock.push_back(rockSprite);
    }
}
