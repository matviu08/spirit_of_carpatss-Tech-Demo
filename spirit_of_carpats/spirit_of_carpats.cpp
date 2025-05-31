#pragma comment (lib, "winmm.lib")
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <cmath>
#include <algorithm>
#include <fstream>
#include "menu.h"
#include "logick.h"
#include "location.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Spirit of Carpats");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/img/backgroundMenu.png")) {
        cout << "Помилка: неможливо завантажити backgroundMenu.png!" << std::endl;
    }

    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale({
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        });

    sf::Font font;
    if (!font.openFromFile("assets/fonts/alagard-12px-unicode.ttf")) {
        cout << "Помилка: не вдалося завантажити шрифт!" << std::endl;
    }

    Menu menu(font); // Створюємо об'єкт меню

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            // **Обробка натискання кнопок**
            menu.handleEvent(event, window);
        }

        window.clear();
        window.draw(backgroundSprite);

        // **Тут малюємо кнопки**
        menu.draw(window);

        window.display();
    }

}
