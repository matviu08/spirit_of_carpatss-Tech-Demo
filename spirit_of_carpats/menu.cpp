#include "menu.h"
void printBackgroundImg(){
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Spirit of Carpats");

    // Завантаження текстури для фону
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/img/backgroundMenu.png")) {
        cout << "Помилка: неможливо завантажити шрифт!" << endl;
    }

    // Створення спрайта та прив'язка текстури
    sf::Sprite backgroundSprite(backgroundTexture);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(backgroundSprite); // Відображення фону
        window.display();
    }
}
