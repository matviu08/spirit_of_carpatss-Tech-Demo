#include "location.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

int location_1_home() {

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        return -1;
    }

    sf::Sprite background(backgroundTexture);

    Texture home_element;
    if (!home_element.loadFromFile("")) {
        return -1;
    }

    std::vector<Sprite> home_elements;
    for (int i = 0; i < 4; ++i) {
        Sprite home_element_sprite(home_element);
        home_element_sprite.setPosition(Vector2f(100.f + i * 150.f, 250.f));
        home_elements.push_back(home_element_sprite);
    }
    

    /*sf::Texture treeTexture;
    if (!treeTexture.loadFromFile("")) {
        return -1;
    }

    vector<sf::Sprite> trees;
    for (int i = 0; i < 5; ++i) {
        sf::Sprite tree(treeTexture);
        tree.setPosition(sf::Vector2f(100.f + i * 150.f, 250.f));
        trees.push_back(tree);
    }*/



    return 0;
}

int location_2_forest() {
    Texture forestBackground;
    if (!forestBackground.loadFromFile("images/background_forest.png")) {
        return -1;
    }
    Sprite background(forestBackground);

    Texture treesTexture_forest;
    if (!treesTexture_forest.loadFromFile("images/tree_forest.png")) {
        return -1;
    }
    vector<Sprite> trees_forest;
    for (int i = 0; i < 5; ++i) {
        Sprite tree_forest(treesTexture_forest);
        tree_forest.setPosition(Vector2f(100.f + i * 150.f, 250.f));
        trees_forest.push_back(tree_forest);
    }
}
