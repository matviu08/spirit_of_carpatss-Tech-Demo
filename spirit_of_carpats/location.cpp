#include "location.h"

void generateForestScene(RenderWindow& window,
    vector<Sprite>& ground,
    vector<Sprite>& grass,
    vector<Sprite>& rock,
    vector<Sprite>& trees,
    vector<Sprite>& news,
    const Texture& grassTexture,
    const Texture& rockTexture,
    const Texture& treeTexture,
    const Texture& newspaperTexture)
{
    // Очистка попередніх спрайтів
    trees.clear();
    news.clear();
    rock.clear();
    grass.clear();
    ground.clear();

    // Налаштування
    const int baseOffsetX = 100;
    const int groundYShift = 5;
    const float treeScaleMin = 0.8f;
    const float treeScaleMax = 1.2f;
    const float newsScaleMin = 0.8f;
    const float newsScaleMax = 1.2f;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 100);

    // Розміри тайлів землі
    int groundTileWidth = groundTexture.getSize().x;
    int groundTileHeight = groundTexture.getSize().y;

    


    // Генерація трави
    int grassVariants = 3;
    int grassTexWidth = grassTexture.getSize().x / grassVariants;
    int grassTexHeight = grassTexture.getSize().y;
    for (int x = 0; x < 5; ++x) {
        if (distr(gen) % 3 == 0) {
            Sprite grass(grassTexture);
            grass.setPosition(Vector2f(
                static_cast<float>(x * groundTileWidth + (distr(gen) % 20 - 10)),
                static_cast<float>(window.getSize().y - groundTileHeight - grassTexHeight + groundYShift)
            ));
            grassSprites.push_back(grass);
        }
    }

    // Генерація дерев
    /*int treeCount = 1;
    for (int i = 0; i < treeCount; ++i) {
        if (!treeTextures.empty()) {
            const Texture& tex = treeTextures[distr(gen) % treeTextures.size()];
            Sprite tree(tex);

            float scale = treeScaleMin + static_cast<float>(distr(gen) % 40) / 100.0f;
            float x = 12.f;
            float y = 12.f;

            tree.setScale(Vector2f(scale, scale));
            tree.setPosition(Vector2f(x, y));
            trees.push_back(tree);
        }
    }*/

    // Генерація газет
    int newsCount = 1;
    for (int i = 0; i < newsCount; ++i) {
        if (!news_peperTexturs.empty()) {
            const Texture& tex = news_peperTexturs[distr(gen) % news_peperTexturs.size()];
            Sprite news(tex);

            float scale = newsScaleMin + static_cast<float>(distr(gen) % 40) / 100.0f;
            float x = 240.f;
            float y = 130.f;

            news.setScale(Vector2f(scale, scale));
            news.setPosition(Vector2f(x, y));
            news_tiles.push_back(news);
        }
    }

    // Кущі(поки що нахуй не треба)
    /*int bushCount = 6;
    for (int i = 0; i < bushCount; ++i) {
        Sprite bush(bushTexture);
        float x = static_cast<float>(baseOffsetX + distr(gen) % (window.getSize().x - 2 * baseOffsetX));
        float y = static_cast<float>(window.getSize().y - groundTileHeight - bushTexture.getSize().y + 10);
        bush.setPosition(Vector2f(x, y));
        bushes.push_back(bush);
    }*/

    int treeCount = 1;
    for(int i = 0; i < treeCount; ++i) {
        Sprite tree(treeTesture);
        float x = 100.f;
        float y = 120.f;
    }

    // Камені
    int rockCount = 1;
    for (int i = 0; i < rockCount; ++i) {
        Sprite rock(rockTexture);
        float x = -75.f;
        float y = 975.f;
        rock.setPosition(Vector2f(x, y));
        rocks.push_back(rock);
    }
}
