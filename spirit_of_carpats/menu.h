#pragma once
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
#include <optional>

using namespace std;

class Menu {
private:
    sf::RectangleShape newGameRect;
    sf::RectangleShape settingsRect;
    sf::RectangleShape quitRect;
    sf::Text newGameButton;
    sf::Text settingsButton;
    sf::Text quitButton;
public:
    Menu(sf::Font& font);
    void handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

void printBackgroundImg();