#include "menu.h"

bool levelStarted = false;
bool gamebuttonOn = false;
bool tohnoEnglish = true;

void Menu::centerButton(sf::Text& button, sf::RenderWindow& window, float yOffset) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f pos_1(static_cast<float>(windowSize.x) / 2 - button.getLocalBounds().size.x / 2, static_cast<float>(windowSize.y) / 2 + yOffset);
    button.setPosition(pos_1);
}

Menu::Menu(sf::Font& font, sf::RenderWindow& window) : newGameButton(font), settingsButton(font), quitButton(font), chapterButton(font), backButtonWithSetings(font), languageButton(font), musicButton(font), leftKeyButton(font), rightKeyButton(font), backButtonWithChapters(font), bindsButton(font), backButtonWithBinds(font) {
    newGameButton.setString("New Game");
    newGameButton.setCharacterSize(50); 
    newGameButton.setFillColor(sf::Color(252, 228, 204));
    centerButton(newGameButton, window, -100);

    settingsButton.setString("Settings");
    settingsButton.setCharacterSize(50);
    settingsButton.setFillColor(sf::Color(252, 228, 204));
    centerButton(settingsButton, window, 0);


    quitButton.setString("Quit");
    quitButton.setCharacterSize(50);
    quitButton.setFillColor(sf::Color(252, 228, 204));
    centerButton(quitButton, window, 100);


    chapterButton.setString("chapter 1");
    chapterButton.setCharacterSize(50);
    chapterButton.setFillColor(sf::Color(252, 228, 204));
    centerButton(chapterButton, window, -100);


    backButtonWithSetings.setString("Back");
    backButtonWithSetings.setCharacterSize(50);
    backButtonWithSetings.setFillColor(sf::Color(252, 228, 204));
    centerButton(backButtonWithSetings, window, 200);

    backButtonWithChapters.setString("Back");
    backButtonWithChapters.setCharacterSize(50);
    backButtonWithChapters.setFillColor(sf::Color(252, 228, 204));
    centerButton(backButtonWithChapters, window, 0);
  
    languageButton.setString("Language: English");
    languageButton.setCharacterSize(50);
    languageButton.setFillColor(sf::Color(252, 228, 204));
    centerButton(languageButton, window, -100);

    musicButton.setString("Music: ON");
    musicButton.setCharacterSize(50);
    musicButton.setFillColor(sf::Color(252, 228, 204));
    centerButton(musicButton, window, 0);

    leftKeyButton.setCharacterSize(50);
    leftKeyButton.setFillColor(sf::Color(252, 228, 204));
    leftKeyButton.setString("Left: " + keyToString(leftKey));
    centerButton(leftKeyButton, window, -100);

    rightKeyButton.setCharacterSize(50);
    rightKeyButton.setFillColor(sf::Color(252, 228, 204));
    rightKeyButton.setString("Right: " + keyToString(rightKey));
    centerButton(rightKeyButton, window, 0);

    bindsButton.setCharacterSize(50);
    bindsButton.setFillColor(sf::Color(252, 228, 204));
    bindsButton.setString("Binds");
    centerButton(bindsButton, window, 100);

    backButtonWithBinds.setCharacterSize(50);
    backButtonWithBinds.setFillColor(sf::Color(252, 228, 204));
    backButtonWithBinds.setString("Back");
    centerButton(backButtonWithBinds, window, 100);


    if (!menuMusic.openFromFile("assets/sound/MainMenuMusicks.ogg")) {
        cout << "Помилка: не вдалося завантажити музику" << endl;
    }
    else {
        menuMusic.setLooping(true);
        menuMusic.setVolume(100);
        menuMusic.play();
    }
}

void Menu::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window, sf::Sprite& backgroundSprite, Menu& menu) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (event->is<sf::Event::MouseButtonPressed>()) {
        if (!levelStarted && !settingsOpened) {
            if (newGameButton.getGlobalBounds().contains(mouseWorldPos)) {
                levelStarted = true;
            }
            else if (settingsButton.getGlobalBounds().contains(mouseWorldPos)) {
                settingsOpened = true;
            }
            else if (quitButton.getGlobalBounds().contains(mouseWorldPos)) {
                window.close();
            }
        }
        else if (levelStarted) {
            if (chapterButton.getGlobalBounds().contains(mouseWorldPos)) {
                levelStarted = true;
                gamebuttonOn = true;
            }
            else if (backButtonWithChapters.getGlobalBounds().contains(mouseWorldPos)) {
                levelStarted = false;
            }
        }
        else if (settingsOpened) {
            if (bindsOpened) {
                if (leftKeyButton.getGlobalBounds().contains(mouseWorldPos)) {
                    waitingForLeftKey = true;
                    if (isEnglish)
                        leftKeyButton.setString("Left: ...");
                    else
                        leftKeyButton.setString(L"Вліво: ...");
                }
                else if (rightKeyButton.getGlobalBounds().contains(mouseWorldPos)) {
                    waitingForRightKey = true;
                    if (isEnglish)
                        rightKeyButton.setString("Right: ...");
                    else
                        rightKeyButton.setString(L"Вправо: ...");
                }
                else if (backButtonWithBinds.getGlobalBounds().contains(mouseWorldPos)) {
                    bindsOpened = false;
                }
            }
            else {
                if (languageButton.getGlobalBounds().contains(mouseWorldPos)) {
                    isEnglish = !isEnglish;
                    if (isEnglish) {
                        newGameButton.setString("New Game");
                        settingsButton.setString("Settings");
                        quitButton.setString("Quit");
                        chapterButton.setString("Chapter 1");
                        backButtonWithSetings.setString("Back");
                        backButtonWithChapters.setString("Back");
                        languageButton.setString("Language: English");
                        musicButton.setString(musicEnabled ? "Music: ON" : "Music: OFF");
                        leftKeyButton.setString("Left: " + keyToString(leftKey));
                        rightKeyButton.setString("Right: " + keyToString(rightKey));
                        bindsButton.setString("Binds");
                        backButtonWithBinds.setString("Back");
                        tohnoEnglish = true;
                    }
                    else {
                        newGameButton.setString(L"Нова гра");
                        settingsButton.setString(L"Налаштування");
                        quitButton.setString(L"Вийти");
                        chapterButton.setString(L"Глава 1");
                        backButtonWithSetings.setString(L"Назад");
                        backButtonWithChapters.setString(L"Назад");
                        languageButton.setString(L"Мова: Українська");
                        musicButton.setString(musicEnabled ? L"Музика: Вкл" : L"Музика: Викл");
                        leftKeyButton.setString(L"Вліво: " + keyToWideString(leftKey));
                        rightKeyButton.setString(L"Вправо: " + keyToWideString(rightKey));
                        bindsButton.setString(L"Бінди");
                        backButtonWithBinds.setString(L"Назад");
                        tohnoEnglish = false;
                    }
                }
                else if (musicButton.getGlobalBounds().contains(mouseWorldPos)) {
                    musicEnabled = !musicEnabled;
                    if (musicEnabled) {
                        menuMusic.play();
                        if (isEnglish)
                            musicButton.setString("Music: ON");
                        else
                            musicButton.setString(L"Музика: Вкл");
                    }
                    else {
                        menuMusic.pause();
                        if (isEnglish)
                            musicButton.setString("Music: OFF");
                        else
                            musicButton.setString(L"Музика: Викл");
                    }
                }
                else if (bindsButton.getGlobalBounds().contains(mouseWorldPos)) {
                    bindsOpened = true;
                }
                else if (backButtonWithSetings.getGlobalBounds().contains(mouseWorldPos)) {
                    settingsOpened = false;
                }
            }

            centerButton(newGameButton, window, -100);
            centerButton(settingsButton, window, 0);
            centerButton(quitButton, window, 100);
            centerButton(chapterButton, window, -100);
            centerButton(backButtonWithChapters, window, 0);
            centerButton(backButtonWithSetings, window, 200);
            centerButton(languageButton, window, -100);
            centerButton(musicButton, window, 0);
            centerButton(leftKeyButton, window, -100);
            centerButton(rightKeyButton, window, 0);
            centerButton(bindsButton, window, 100);
            centerButton(backButtonWithBinds, window, 100);
        }
    }
    else if (event->is<sf::Event::KeyPressed>()) {
        if (const auto* keyEvt = event->getIf<sf::Event::KeyPressed>()) {
            sf::Keyboard::Key pressed = sf::Keyboard::localize(keyEvt->scancode);
            if (waitingForLeftKey) {
                leftKey = pressed;
                if (isEnglish)
                    leftKeyButton.setString("Left: " + keyToString(leftKey));
                else
                    leftKeyButton.setString(L"Вліво: " + keyToWideString(leftKey));
                centerButton(leftKeyButton, window, -100);
                waitingForLeftKey = false;
            }
            else if (waitingForRightKey) {
                rightKey = pressed;
                if (isEnglish)
                    rightKeyButton.setString("Right: " + keyToString(rightKey));
                else
                    rightKeyButton.setString(L"Вправо: " + keyToWideString(rightKey));
                centerButton(rightKeyButton, window, 0);
                waitingForRightKey = false;
            }
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    if (!levelStarted && !settingsOpened) {
        window.draw(newGameButton);
        window.draw(settingsButton);
        window.draw(quitButton);
    }
    else if (levelStarted) {
        window.draw(chapterButton);
        window.draw(backButtonWithChapters);
    }
    else if (settingsOpened) {
        if (bindsOpened) {
            window.draw(leftKeyButton);
            window.draw(rightKeyButton);
            window.draw(backButtonWithBinds);
        }
        else {
            window.draw(languageButton);
            window.draw(musicButton);
            window.draw(backButtonWithSetings);
            window.draw(bindsButton);
        }
    }
}


std::string Menu::keyToString(sf::Keyboard::Key key) {
    using K = sf::Keyboard::Key;
    switch (key) {
    case K::A: return "A";
    case K::B: return "B";
    case K::C: return "C";
    case K::D: return "D";
    case K::E: return "E";
    case K::F: return "F";
    case K::G: return "G";
    case K::H: return "H";
    case K::I: return "I";
    case K::J: return "J";
    case K::K: return "K";
    case K::L: return "L";
    case K::M: return "M";
    case K::N: return "N";
    case K::O: return "O";
    case K::P: return "P";
    case K::Q: return "Q";
    case K::R: return "R";
    case K::S: return "S";
    case K::T: return "T";
    case K::U: return "U";
    case K::V: return "V";
    case K::W: return "W";
    case K::X: return "X";
    case K::Y: return "Y";
    case K::Z: return "Z";
    case K::Left: return "←";
    case K::Right: return "→";
    case K::Space: return "Space";
    case K::Enter: return "Enter";
    case K::LControl: return "Ctrl";
    case K::LShift: return "Shift";
    default: return "Unknown";
    }
}

std::wstring Menu::keyToWideString(sf::Keyboard::Key key) {
    std::string latin = keyToString(key);
    return std::wstring(latin.begin(), latin.end());
}
