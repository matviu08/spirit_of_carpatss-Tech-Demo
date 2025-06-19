#include "menu.h"

bool levelStarted = false;

void Menu::centerButton(sf::Text& button, sf::RenderWindow& window, float yOffset) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f pos_1(static_cast<float>(windowSize.x) / 2 - button.getLocalBounds().size.x / 2, static_cast<float>(windowSize.y) / 2 + yOffset);
    button.setPosition(pos_1);
}

Menu::Menu(sf::Font& font, sf::RenderWindow& window) : newGameButton(font), settingsButton(font), quitButton(font), chapterButton(font), backButton(font), languageButton(font), musicButton(font) {
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


    backButton.setString("Back");
    backButton.setCharacterSize(50);
    backButton.setFillColor(sf::Color(252, 228, 204));
    centerButton(backButton, window, 100);

  
    languageButton.setString("Language: English");
    languageButton.setCharacterSize(50);
    languageButton.setFillColor(sf::Color(252, 228, 204));
    centerButton(languageButton, window, -100);

    musicButton.setString("Music: ON");
    musicButton.setCharacterSize(50);
    musicButton.setFillColor(sf::Color(252, 228, 204));
    centerButton(musicButton, window, 0);

    if (!menuMusic.openFromFile("assets/sound/MainMenuMusicks.ogg")) {
        cout << "Помилка: не вдалося завантажити музику" << endl;
    }
    else {
        menuMusic.setLooping(true);
        menuMusic.setVolume(100);
        menuMusic.play();
    }
}

void Menu::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window, sf::Sprite& backgroundSprite) {
    if (event->is<sf::Event::MouseButtonPressed>()) {
        auto mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

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
                createLevel1(window, backgroundSprite, event);
            }
            else if (backButton.getGlobalBounds().contains(mouseWorldPos)) {
                levelStarted = false;
            }
        }

        else if (settingsOpened) {
            if (languageButton.getGlobalBounds().contains(mouseWorldPos) || musicButton.getGlobalBounds().contains(mouseWorldPos)) {
                if (languageButton.getGlobalBounds().contains(mouseWorldPos)) {
                    isEnglish = !isEnglish;
                    if (isEnglish) {
                        newGameButton.setString("New Game");
                        settingsButton.setString("Settings");
                        quitButton.setString("Quit");
                        chapterButton.setString("Chapter 1");
                        backButton.setString("Back");
                        languageButton.setString("Language: English");
                        musicButton.setString(musicEnabled ? "Music: ON" : "Music: OFF");
                        tohnoEnglish = true;
                    }
                    else {
                        std::cout << "Перемкнули на Українську!" << std::endl;
                        newGameButton.setString(L"Нова гра");
                        settingsButton.setString(L"Налаштування");
                        quitButton.setString(L"Вийти");
                        chapterButton.setString(L"Глава 1");
                        backButton.setString(L"Назад");
                        languageButton.setString(L"Мова: Українська");
                        musicButton.setString(musicEnabled ? L"Музика: Вкл" : L"Музика: Викл"); 
                        tohnoEnglish = false;
                    }
                }

                if (musicButton.getGlobalBounds().contains(mouseWorldPos)) {
                    musicEnabled = !musicEnabled;
                    if (musicEnabled) {
                        menuMusic.play();
                        if (!isEnglish) {
                            musicButton.setString(L"Музика: Вкл");
                        }
                        else {
                            musicButton.setString("Music: ON");
                        }
                    }
                    else {
                        menuMusic.pause();
                        if (!isEnglish) {
                            musicButton.setString(L"Музика: Викл");
                        }
                        else {
                            musicButton.setString("Music: OFF");
                        }
                    }
                }

                centerButton(newGameButton, window, -100);
                centerButton(settingsButton, window, 0);
                centerButton(quitButton, window, 100);
                centerButton(chapterButton, window, -100);
                centerButton(backButton, window, 100);
                centerButton(languageButton, window, -100);
                centerButton(musicButton, window, 0);
            }

            else if (backButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: Back!" << std::endl;
                settingsOpened = false;
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
        window.draw(backButton);
    }
    else if (settingsOpened) {
        window.draw(languageButton);
        window.draw(backButton);
        window.draw(musicButton);
    }
}
