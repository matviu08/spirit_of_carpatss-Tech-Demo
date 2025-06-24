#include "location.h"
#include "chapter1_house.h"

void Generation_of_locations(sf::RenderWindow& window, sf::Sprite& background) {
    // Загружаем необходимые текстуры
    sf::Texture grassTexture;
    sf::Texture rockTexture;
    sf::Texture treeTexture;
    sf::Texture newspaperTexture;
    sf::Texture backgroundTexture;

    sf::Texture background_home_texture;
    sf::Texture bed_texture;

    backgroundTexture.loadFromFile("assets/img/levl1_bg.png");
    rockTexture.loadFromFile("assets/img/Kamin.png");
    treeTexture.loadFromFile("assets/img/Tree_3.png");
    newspaperTexture.loadFromFile("assets/img/torn newspaper_2.png");

    background_home_texture.loadFromFile("assets/img/home_bg.png");
    bed_texture.loadFromFile("assets/img/bed_texture.png");

    // Объявляем векторы спрайтов для различных элементов
    std::vector<sf::Sprite> ground;
    std::vector<sf::Sprite> grass;
    std::vector<sf::Sprite> rock;
    std::vector<sf::Sprite> trees;
    std::vector<sf::Sprite> news;

    std::vector<sf::Sprite> tiledBackgrounds;
    std::vector<sf::Sprite> bed;
    std::vector<sf::Sprite> bacground_home;

    generateHomeScene(window, bed, bacground_home, background_home_texture, bed_texture);


    for (auto& sprite : bacground_home)
        window.draw(sprite);

    for (auto& sprite : tiledBackgrounds)
        window.draw(sprite);

    for (auto& sprite : bed)
        window.draw(sprite);

    for (auto& sprite : ground)
        window.draw(sprite);

    for (auto& sprite : grass)
        window.draw(sprite);

    for (auto& sprite : rock)
        window.draw(sprite);

    for (auto& sprite : trees)
        window.draw(sprite);

    for (auto& sprite : news)
        window.draw(sprite);

    window.draw(background);
}
