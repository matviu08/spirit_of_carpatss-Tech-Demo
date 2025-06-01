#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>

using namespace sf;
using namespace std;
//
//int main() {
//    RenderWindow window(VideoMode(1280, 720), "Forest Scene");
//
//    random_device rd;
//    mt19937 gen(rd());
//    uniform_int_distribution<> distr(0, 100);
//
//    Texture backgroundFarTexture;
//    if (!backgroundFarTexture.loadFromFile("assets/img/forest/bg_far.png")) {
//        cerr << "Error loading backgroundFarTexture\n";
//        return -1;
//    }
//
//    Texture backgroundMidTexture;
//    if (!backgroundMidTexture.loadFromFile("assets/img/forest/bg_mid.png")) {
//        cerr << "Error loading backgroundMidTexture\n";
//        return -1;
//    }
//
//    Texture groundTexture;
//    if (!groundTexture.loadFromFile("assets/img/forest/ground.png")) {
//        cerr << "Error loading ground texture\n";
//        return -1;
//    }
//
//    Texture grassTexture;
//    if (!grassTexture.loadFromFile("assets/img/forest/grass.png")) {
//        cerr << "Error loading grass texture\n";
//        return -1;
//    }
//
//    Texture bushTexture;
//    if (!bushTexture.loadFromFile("assets/img/forest/bush.png")) {
//        cerr << "Error loading bush texture\n";
//    }
//
//    Texture rockTexture;
//    if (!rockTexture.loadFromFile("assets/img/forest/rock.png")) {
//        cerr << "Error loading rock texture\n";
//    }
//
//    vector<Texture> treeTextures;
//    for (int i = 1; i <= 5; ++i) {
//        Texture treeTex;
//        if (!treeTex.loadFromFile("assets/img/forest/tree_" + to_string(i) + ".png")) {
//            cerr << "Error loading tree texture " << i << endl;
//            continue;
//        }
//        treeTextures.push_back(treeTex);
//    }
//
//    Sprite backgroundFar(backgroundFarTexture);
//    backgroundFar.setScale(
//        static_cast<float>(window.getSize().x) / static_cast<float>(backgroundFarTexture.getSize().x),
//        static_cast<float>(window.getSize().y) / static_cast<float>(backgroundFarTexture.getSize().y)
//    );
//
//    Sprite backgroundMid(backgroundMidTexture);
//    backgroundMid.setScale(
//        static_cast<float>(window.getSize().x) / static_cast<float>(backgroundMidTexture.getSize().x),
//        static_cast<float>(window.getSize().y) / static_cast<float>(backgroundMidTexture.getSize().y)
//    );
//
//    vector<Sprite> groundTiles;
//    int groundTileWidth = static_cast<int>(groundTexture.getSize().x);
//    int groundTileHeight = static_cast<int>(groundTexture.getSize().y);
//    int groundCols = window.getSize().x / groundTileWidth + 1;
//
//    for (int x = 0; x < groundCols; ++x) {
//        Sprite tile(groundTexture);
//        tile.setPosition(static_cast<float>(x * groundTileWidth),
//            static_cast<float>(window.getSize().y - groundTileHeight));
//        groundTiles.push_back(tile);
//    }
//
//    vector<Sprite> grassSprites;
//    int grassVariants = 3;
//    for (int x = 0; x < groundCols; ++x) {
//        for (int v = 0; v < grassVariants; ++v) {
//            if (distr(gen) % 3 == 0) {
//                Sprite grass(grassTexture);
//                grass.setTextureRect(IntRect(
//                    v * static_cast<int>(grassTexture.getSize().x) / grassVariants,
//                    0,
//                    static_cast<int>(grassTexture.getSize().x) / grassVariants,
//                    static_cast<int>(grassTexture.getSize().y)
//                ));
//                grass.setPosition(
//                    static_cast<float>(x * groundTileWidth + (distr(gen) % 50 - 25)),
//                    static_cast<float>(window.getSize().y - groundTileHeight - grass.getLocalBounds().height + 10)
//                );
//                grassSprites.push_back(grass);
//            }
//        }
//    }
//
//    vector<Sprite> trees;
//    int treeCount = 15 + (distr(gen) % 10);
//    for (int i = 0; i < treeCount; ++i) {
//        if (!treeTextures.empty()) {
//            const Texture& tex = treeTextures[distr(gen) % treeTextures.size()];
//            Sprite tree(tex);
//
//            float x = static_cast<float>(distr(gen) % (window.getSize().x + 200) - 100);
//            float y = static_cast<float>(window.getSize().y - groundTileHeight - tex.getSize().y + 20);
//
//            float scale = 0.8f + static_cast<float>(distr(gen) % 40) / 100.0f;
//            tree.setScale(scale, scale);
//
//            tree.setPosition(x, y - (scale - 1.0f) * tex.getSize().y * 0.5f);
//            trees.push_back(tree);
//        }
//    }
//
//    vector<Sprite> bushes;
//    int bushCount = 10 + (distr(gen) % 10);
//    for (int i = 0; i < bushCount; ++i) {
//        Sprite bush(bushTexture);
//        float x = static_cast<float>(distr(gen) % window.getSize().x);
//        float y = static_cast<float>(window.getSize().y - groundTileHeight - bushTexture.getSize().y + 15);
//        bush.setPosition(x, y);
//        bushes.push_back(bush);
//    }
//
//    vector<Sprite> rocks;
//    int rockCount = 5 + (distr(gen) % 6);
//    for (int i = 0; i < rockCount; ++i) {
//        Sprite rock(rockTexture);
//        float x = static_cast<float>(distr(gen) % window.getSize().x);
//        float y = static_cast<float>(window.getSize().y - groundTileHeight - rockTexture.getSize().y + 5);
//        rock.setPosition(x, y);
//        rocks.push_back(rock);
//    }
//
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                window.close();
//            }
//        }
//
//        window.clear(Color(135, 206, 235));
//
//        window.draw(backgroundFar);
//        window.draw(backgroundMid);
//
//        for (const auto& tree : trees) {
//            window.draw(tree);
//        }
//
//        for (const auto& tile : groundTiles) {
//            window.draw(tile);
//        }
//
//        for (const auto& grass : grassSprites) {
//            window.draw(grass);
//        }
//
//        for (const auto& bush : bushes) {
//            window.draw(bush);
//        }
//
//        for (const auto& rock : rocks) {
//            window.draw(rock);
//        }
//
//        window.display();
//    }
//
//    return 0;
//}