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
#include "logick.h"
#include "location.h"
#include "chapters.h"
#include "Chapter1.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include <optional>

using namespace std;

class Menu {
private:
    bool settingsOpened = false;
    bool isEnglish = true;
    bool tohnoEnglish = true;
    bool musicEnabled = true;
    bool waitingForLeftKey = false;
    bool waitingForRightKey = false;

    sf::Keyboard::Key leftKey = sf::Keyboard::Key::A;
    sf::Keyboard::Key rightKey = sf::Keyboard::Key::D;

    sf::RectangleShape newGameRect;
    sf::RectangleShape settingsRect;
    sf::RectangleShape quitRect;
    sf::Text newGameButton;
    sf::Text settingsButton;
    sf::Text quitButton;
    sf::RectangleShape chapterRect;
    sf::RectangleShape backRect;
    sf::Text chapterButton;
    sf::Text backButtonWithSetings;
    sf::Text backButtonWithChapters;
    sf::RectangleShape languageRect;
    sf::Text languageButton;

    sf::Text musicButton;
    sf::Music menuMusic;

    sf::Text leftKeyButton;
    sf::Text rightKeyButton;

    void centerButton(sf::Text& button, sf::RenderWindow& window, float yOffset);
    std::string keyToString(sf::Keyboard::Key key);
    std::wstring keyToWideString(sf::Keyboard::Key key);

public:
    Menu(sf::Font& font, sf::RenderWindow& window);
    void handleEvent(const std::optional<sf::Event>&, sf::RenderWindow&, sf::Sprite&);
    void draw(sf::RenderWindow& window);

    sf::Keyboard::Key getLeftKey() const { 
        return leftKey; 
    }
    sf::Keyboard::Key getRightKey() const {
        return rightKey;
    }

};
