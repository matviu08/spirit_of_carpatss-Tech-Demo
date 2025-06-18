#include "location.h"

void generateHomeScene(
    sf::RenderWindow& window,
    std::vector<sf::Sprite>& spawn_pleyer,
    std::vector<sf::Sprite>& background_home)
{
    background_home.clear();


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
    int newsCount = 3;
    float startX = 1000.f;
    float y = 856.f;
    float spacing = 1200.f;
    for (int i = 0; i < newsCount; ++i) {

        sf::Sprite newspaper(newspaperTexture);

        float scale = 0.8f + static_cast<float>(rand() % 40) / 100.0f;
        newspaper.setScale(sf::Vector2f(scale, scale));

        float x = startX + i * spacing;
        newspaper.setPosition(sf::Vector2f(x, y));
        
        news.push_back(newspaper);
    }

    // 🌲 Генерація дерев
    const int treeCount = 3;
    float pos_tree_x = 1400.f;
    float y_pos_tree = 425.f;
    float space_tree = 1200.f;

    for (int i = 0; i < treeCount; ++i) {
        sf::Sprite tree(treeTexture);
        float x_tree = pos_tree_x + i * space_tree;
        tree.setPosition(sf::Vector2f(x_tree, y_pos_tree));
        trees.push_back(tree);
    }

    // 🪨 Генерація каменів
    int rockCount = 1;
    for (int i = 0; i < rockCount; ++i) {
        sf::Sprite rockSprite(rockTexture);
        float x = -75.f;
        float y = 975.f;
        rockSprite.setPosition(sf::Vector2f(x, y));
        rock.push_back(rockSprite);
    }
}
