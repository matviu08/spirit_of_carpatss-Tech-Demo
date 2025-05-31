#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

int location_1_home(RenderWindow& window) {
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/img/Game_BackGround.png")) {
        cerr << "Error loading background\n";
        return -1;
    }
    Sprite background(backgroundTexture);

    Texture home_element;
    if (!home_element.loadFromFile("assets/img/home_element.png")) {
        cerr << "Error loading home element\n";
        return -1;
    }

    vector<Sprite> home_elements;
    for (int i = 0; i < 4; ++i) {
        Sprite home_element_sprite(home_element);
        home_element_sprite.setPosition(Vector2f(100.f + i * 150.f, 400.f));
        home_elements.push_back(home_element_sprite);
    }

    window.clear();
    window.draw(background);
    for (const auto& e : home_elements) {
        window.draw(e);
    }
    window.display();

    return 0;
}

//int location_2_forest(RenderWindow& window) {
//    Texture forestBackground;
//    if (!forestBackground.loadFromFile("assets/img/Game_BackGround.png")) {
//        cerr << "Error loading background\n";
//        return -1;
//    }
//    Sprite background(forestBackground);
//
//    Texture treesTexture_forest;
//    if (!treesTexture_forest.loadFromFile("assets/img/tree_forest.png")) {
//        cerr << "Error loading tree texture\n";
//        return -1;
//    }
//
//    vector<Sprite> trees_forest;
//    for (int i = 0; i < 5; ++i) {
//        Sprite tree_forest(treesTexture_forest);
//        tree_forest.setPosition(Vector2f(100.f + i * 150.f, 300.f));
//        trees_forest.push_back(tree_forest);
//    }
//
//    Texture ground_texture;
//    if (!ground_texture.loadFromFile("assets/img/grass.png")) {
//        cerr << "Error loading grass texture\n";
//        return -1;
//    }
//
//    Sprite ground(ground_texture);
//    ground.setPosition(0, 550);
//    ground.setScale(
//        static_cast<float>(window.getSize().x) / ground_texture.getSize().x,
//        1.0f
//    );
//
//    window.clear();
//    window.draw(background);
//    for (const auto& t : trees_forest) {
//        window.draw(t);
//    }
//    window.draw(ground);
//    window.display();
//
//    return 0;
//}
