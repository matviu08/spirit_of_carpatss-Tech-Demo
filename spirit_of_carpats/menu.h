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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <box2d/box2d.h>
#include <optional>

using namespace std;
using namespace sf;

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

    Keyboard::Key leftKey = Keyboard::Key::A;
    Keyboard::Key rightKey = Keyboard::Key::D;
    Keyboard::Key interactionKey = Keyboard::Key::E;
    Keyboard::Key jumpKey = Keyboard::Key::Space;

    Text newGameButton;
    Text settingsButton;
    Text quitButton;
    Text chapterButton;
    Text backButtonWithSetings;
    Text backButtonWithChapters;
    Text languageButton;
    Text bindsButton;
    Text backButtonWithBinds;

    Text musicButton;

    Text leftKeyButton;
    Text rightKeyButton;
    Text interactionKeyButton;
    Text jumpKeyButton;

    void centerButton(Text&, RenderWindow&, float);
    string keyToString(Keyboard::Key key);

public:
    Menu(Font&, RenderWindow&);
    void handleEvent(const optional<Event>&, RenderWindow&, Sprite&, Menu&);
    void draw(RenderWindow&);

    Keyboard::Key getLeftKey() const { 
        return leftKey; 
    }
    Keyboard::Key getRightKey() const {
        return rightKey;
    }
    Keyboard::Key getInteractiontKey() const {
        return interactionKey;
    }
    Keyboard::Key getJumptKey() const {
        return jumpKey;
    }
    string getInteractionText() {
       return interactionText;
    }

};
