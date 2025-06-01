#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

int generate_landscape(RenderWindow& window) {
    srand(static_cast<unsigned int>(time(nullptr)));

    // --- Загрузка текстур ---
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/img/Game_BackGround.png")) {
        cerr << "Error loading background\n";
        return -1;
    }
    Sprite background(backgroundTexture);

    Texture grassTexture;
    if (!grassTexture.loadFromFile("assets/img/grass.png")) {
        cerr << "Error loading grass texture\n";
        return -1;
    }

    Texture treeTexture;
    if (!treeTexture.loadFromFile("assets/img/tree_forest.png")) {
        cerr << "Error loading tree texture\n";
        return -1;
    }

    // --- Генерация травы ---
    vector<Sprite> grassTiles;
    int tileWidth = grassTexture.getSize().x;
    int tileHeight = grassTexture.getSize().y;

    int rows = 3;
    int cols = window.getSize().x / tileWidth + 1;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            Sprite tile(grassTexture);
            tile.setPosition(sf::Vector2f(static_cast<float>(x * tileWidth), static_cast<float>(window.getSize().y - (rows - y) * tileHeight)));
            grassTiles.push_back(tile);
        }
    }

    // --- Генерация деревьев случайно ---
    vector<Sprite> trees;
    for (int i = 0; i < 10; ++i) {
        Sprite tree(treeTexture);
        float x = static_cast<float>(rand() % (window.getSize().x - 100));
        float y = static_cast<float>(rand() % 200 + 250);
        tree.setPosition(sf::Vector2f(x, y));
        trees.push_back(tree);
    }



    // --- Отрисовка ---
    window.clear();
    window.draw(background);
    for (const auto& g : grassTiles) window.draw(g);
    for (const auto& t : trees) window.draw(t);
    window.display();

    return 0;

    //generate_landscape(window); -для виклику сцени через меню


}
