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
#include "chapters.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include "Chapter1.h"

using namespace std;
using namespace sf;

int main() {
    VideoMode screenSize = VideoMode::getDesktopMode();
    RenderWindow window(screenSize, "Spirit of Carpatians", State::Fullscreen);

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/img/backgroundMenu_DecstopVersion.png")) {
        cout << "Помилка: неможливо завантажити backgroundMenu.png!" << endl;
    }
    Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale({
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        });

    Font font;
    if (!font.openFromFile("assets/fonts/alagard-12px-unicode.ttf")) {
        cout << "Помилка: не вдалося завантажити шрифт!" << endl;
    }

    Menu menu(font, window); 
    
    bool inLevel = false;

    while (window.isOpen()) {
        extern bool gamebuttonOn;
        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();

            menu.handleEvent(event, window, backgroundSprite, menu);
        }
        window.clear();
        window.draw(backgroundSprite);

        if (!gamebuttonOn) {
            menu.draw(window);
        }
        else {
            createLevel1(window, backgroundSprite, window.pollEvent(), menu);
        }
        
      

        window.display();
    }

}
