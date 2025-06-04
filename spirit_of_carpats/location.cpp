#include "location.h"

//void textures(RenderWindow& window,
//    vector<Sprite>& rocks
//    ) 
//
//{
//    Vector2fu windowSizeSprite = window.getSize();
//
//    Vector2f pos_rock(static_cast<float>(windowSizeSprite.x) / 2 - 300 / 2, static_cast<float>(windowSizeSprite.y) / 2);
//
//
//}

void generateHomeScene(RenderWindow& window,const Texture& bed)
{

}

void generateForestScene(RenderWindow& window,
    vector<Sprite>& trees,
    vector<Sprite>& bushes,
    vector<Sprite>& news_tiles,
    vector<Sprite>& rocks,
    vector<Sprite>& grassSprites,
    vector<Sprite>& groundTiles,
    vector<Sprite>& news_peper,
    const vector<Texture>& treeTextures,
    const Texture& bushTexture,
    const vector<Texture>& news_peperTexturs,
    const Texture& rockTexture,
    const Texture& grassTexture,
    const Texture& groundTexture) {
    trees.clear();
    news_tiles.clear();
    bushes.clear();
    rocks.clear();
    grassSprites.clear();
    groundTiles.clear();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 100);

    int groundTileWidth = static_cast<int>(groundTexture.getSize().x);
    int groundTileHeight = static_cast<int>(groundTexture.getSize().y);
    int groundCols = window.getSize().x / groundTileWidth + 2;

    for (int x = 0; x < groundCols; ++x) {
        Sprite tile(groundTexture); // 🔴 SFML 3.0 — обов’язково з текстурою
        tile.setPosition(Vector2f(static_cast<float>(x * groundTileWidth),
            static_cast<float>(window.getSize().y - groundTileHeight)));
        groundTiles.push_back(tile);
    }

    int grassVariants = 3;
    int grassTexWidth = grassTexture.getSize().x / grassVariants;
    int grassTexHeight = grassTexture.getSize().y;

    for (int x = 0; x < groundCols; ++x) {
        for (int v = 0; v < grassVariants; ++v) {
            if (distr(gen) % 3 == 0) {
                Sprite grass(grassTexture); // ✅ обов’язково передати текстуру
                grass.setPosition(Vector2f(
                    static_cast<float>(x * groundTileWidth + (distr(gen) % 50 - 25)),
                    static_cast<float>(window.getSize().y - groundTileHeight - grassTexHeight + 10)
                ));
                grassSprites.push_back(grass);
            }
        }
    }

    int treeCount = 15 + (distr(gen) % 10);
    for (int i = 0; i < treeCount; ++i) {
        if (!treeTextures.empty()) {
            const Texture& tex = treeTextures[distr(gen) % treeTextures.size()];
            Sprite tree(tex); // ✅ передаємо одразу текстуру

            float x = static_cast<float>(distr(gen) % (window.getSize().x + 200) - 100);
            float y = static_cast<float>(window.getSize().y - groundTileHeight - tex.getSize().y + 20);
            float scale = 0.8f + static_cast<float>(distr(gen) % 40) / 100.0f;

            tree.setScale(Vector2f(scale, scale));
            tree.setPosition(Vector2f(x, y - (scale - 1.0f) * tex.getSize().y * 0.5f));
            trees.push_back(tree);
        }
    }

    int news_peper_count = 3 + (distr(gen) % 10);
    for (int i = 0; i < news_peper_count; ++i) {
        if (!news_peperTexturs.empty()) {
            const Texture& tex = news_peperTexturs[distr(gen) % news_peperTexturs.size()];
            Sprite news_tile(tex);

            float x = static_cast<float>(distr(gen) % (window.getSize().x + 200) - 100);
            float y = static_cast<float>(window.getSize().y - tex.getSize().y);  // або інше значення, де буде "газета"

            float scale = 0.8f + static_cast<float>(distr(gen) % 40) / 100.0f;

            news_tile.setScale(Vector2f(scale, scale));
            news_tile.setPosition(Vector2f(x, y - (scale - 1.0f) * tex.getSize().y * 0.5f));

            news_tiles.push_back(news_tile);
        }
    }

    class news_peper {
    public:
        string MessegPeper[100];
        void news_text_peper_1(string MessegPeper) {
            MessegPeper = { "some text for lore" };
        }
    };

    int bushCount = 10 + (distr(gen) % 10);
    for (int i = 0; i < bushCount; ++i) {
        Sprite bush(bushTexture); // ✅
        float x = static_cast<float>(distr(gen) % window.getSize().x);
        float y = static_cast<float>(window.getSize().y - groundTileHeight - bushTexture.getSize().y + 15);
        bush.setPosition(Vector2f(x, y));
        bushes.push_back(bush);
    }

    int rockCount = 5 + (distr(gen) % 6);
    for (int i = 0; i < rockCount; ++i) {
        Sprite rock(rockTexture); // ✅
        float x = static_cast<float>(distr(gen) % window.getSize().x);
        float y = static_cast<float>(window.getSize().y - groundTileHeight - rockTexture.getSize().y + 5);
        rock.setPosition(Vector2f(x, y));
        rocks.push_back(rock);
    }
}