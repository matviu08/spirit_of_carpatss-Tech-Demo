#include "location.h"

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
    news.clear();
    rock.clear();
    grass.clear();
    ground.clear();
    background.clear();

    const int backgroundRepeatCount = 10; // 🔹 Розширюємо фон для великої сцени

    // 🎨 Генерація повторюваного бекграунду
    const float backgroundWidth = backgroundTexture.getSize().x;
    for (int i = 0; i < backgroundRepeatCount; ++i) {
        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setPosition(sf::Vector2f(i * backgroundWidth, 0.0f));
        background.push_back(backgroundSprite); // додаємо у background
    }

    // 📰 Генерація газет
    int newsCount = 1;
    for (int i = 0; i < newsCount; ++i) {
        sf::Sprite newspaper(newspaperTexture);
        float scale = 0.8f + static_cast<float>(rand() % 40) / 100.0f;
        float x = 1000.f;
        float y = 856.f;
        newspaper.setScale(sf::Vector2f(scale, scale));
        newspaper.setPosition(sf::Vector2f(x, y));
        news.push_back(newspaper);
    }

    // 🌲 Генерація дерев
    int treeCount = 1;
    for (int i = 0; i < treeCount; ++i) {
        sf::Sprite tree(treeTexture);
        float x = 1400.f;
        float y = 425.f;
        tree.setPosition(sf::Vector2f(x, y));
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
