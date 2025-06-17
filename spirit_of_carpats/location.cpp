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

    // Налаштування
    const int backgroundRepeatCount = 5; // Кількість повторів фону
    const int baseOffsetX = 100;
    const int groundYShift = 5;
    const float treeScaleMin = 0.8f;
    const float treeScaleMax = 1.2f;
    const float newsScaleMin = 0.8f;
    const float newsScaleMax = 1.2f;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 100);

    int bgRepeatingCount = 5;

    // 🎨 Генерація повторюваного фону
    const float backgroundWidth = backgroundTexture.getSize().x;
    for (int i = 0; i < backgroundRepeatCount; ++i) {
        Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setPosition(Vector2f(i * backgroundWidth, 0.f));
        ground.push_back(backgroundSprite); // додаємо у ground
    }

    


    // 📰 Генерація газет
    int newsCount = 1;
    for (int i = 0; i < newsCount; ++i) {
        Sprite newspaper(newspaperTexture);
        float scale = newsScaleMin + static_cast<float>(distr(gen) % 440) / 200.0f;
        float x = 1000.f;
        float y = 856.f;

        newspaper.setScale(Vector2f(scale, scale));
        newspaper.setPosition(Vector2f(x, y));
        news.push_back(newspaper);
    }

    // 🌲 Генерація дерев
    int treeCount = 1;
    for (int i = 0; i < treeCount; ++i) {
        Sprite tree(treeTexture);
        float x = 1400.f;
        float y = 425.f;
        tree.setPosition(Vector2f(x, y));
        trees.push_back(tree);
    }

    // 🪨 Генерація каменів
    int rockCount = 1;
    for (int i = 0; i < rockCount; ++i) {
        Sprite rockSprite(rockTexture);
        float x = -75.f;
        float y = 975.f;
        rockSprite.setPosition(Vector2f(x, y));
        rock.push_back(rockSprite);
    }
}
