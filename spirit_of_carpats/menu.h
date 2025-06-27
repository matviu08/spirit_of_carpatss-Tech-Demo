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
    bool bindsOpened = false;
    bool isEnglish = true;
    bool musicEnabled = true;
    bool waitingForLeftKey = false;
    bool waitingForRightKey = false;
    bool waitingForInteractionKey = false;
    bool waitingForJumpKey = false;
    string interactionText = "E";

    sf::Keyboard::Key leftKey = sf::Keyboard::Key::A;
    sf::Keyboard::Key rightKey = sf::Keyboard::Key::D;
    sf::Keyboard::Key interactionKey = sf::Keyboard::Key::E;
    sf::Keyboard::Key jumpKey = sf::Keyboard::Key::Space;

    sf::Text newGameButton;
    sf::Text settingsButton;
    sf::Text quitButton;
    sf::Text chapterButton;
    sf::Text backButtonWithSetings;
    sf::Text backButtonWithChapters;
    sf::Text languageButton;
    sf::Text bindsButton;
    sf::Text backButtonWithBinds;

    sf::Text musicButton;
    sf::Music menuMusic;

    sf::Text leftKeyButton;
    sf::Text rightKeyButton;
    sf::Text interactionKeyButton;
    sf::Text jumpKeyButton;

    void centerButton(sf::Text&, sf::RenderWindow&, float);
    string keyToString(sf::Keyboard::Key key);

public:
    Menu(sf::Font&, sf::RenderWindow&);
    void handleEvent(const std::optional<sf::Event>&, sf::RenderWindow&, sf::Sprite&, Menu&);
    void draw(sf::RenderWindow&);

    sf::Keyboard::Key getLeftKey() const { 
        return leftKey; 
    }
    sf::Keyboard::Key getRightKey() const {
        return rightKey;
    }
    sf::Keyboard::Key getInteractiontKey() const {
        return interactionKey;
    }
    sf::Keyboard::Key getJumptKey() const {
        return jumpKey;
    }
    string getInteractionText() {
       return interactionText;
    }
    bool getMusic() const {
        return musicEnabled;
    }
};
