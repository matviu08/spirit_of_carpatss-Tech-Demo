#include "menu.h"

void Menu::centerButton(sf::Text& button, sf::RenderWindow& window, float yOffset) {
    sf::Vector2u windowSize = window.getSize();
    if (tohnoEnglish) {
        if (&button == &newGameButton) {
            sf::Vector2f pos_1(static_cast<float>(windowSize.x) / 2 - 300 / 2, static_cast<float>(windowSize.y) / 2 + yOffset);
            button.setPosition(pos_1);
        }
        else if (&button == &settingsButton) {
            sf::Vector2f pos_2(static_cast<float>(windowSize.x) / 2 - 250 / 2, static_cast<float>(windowSize.y) / 2 + yOffset);
            button.setPosition(pos_2);
        }
        else if (&button == &quitButton) {
            sf::Vector2f pos_3(static_cast<float>(windowSize.x) / 2 - 160 / 2, static_cast<float>(windowSize.y) / 2 + yOffset);
            button.setPosition(pos_3);
        }
        else if (&button == &chapterButton) {
            sf::Vector2f pos_4(static_cast<float>(windowSize.x) / 2 - 280 / 2, static_cast<float>(windowSize.y) / 2 + yOffset);
            button.setPosition(pos_4);
        }
        else if (&button == &backButton) {
            sf::Vector2f pos_5(static_cast<float>(windowSize.x) / 2 - 200 / 2, static_cast<float>(windowSize.y) / 2 + yOffset);
            button.setPosition(pos_5);
        }
        else if (&button == &languageButton) {
            sf::Vector2f pos_6(static_cast<float>(windowSize.x) / 2 - 500 / 2, static_cast<float>(windowSize.y) / 2 + yOffset);
            button.setPosition(pos_6);
        }
    }
}

Menu::Menu(sf::Font& font, sf::RenderWindow& window) : newGameButton(font), settingsButton(font), quitButton(font), chapterButton(font), backButton(font), languageButton(font), backButtonForChap(font) {
    newGameButton.setString("New Game"); // Текст кнопки
    newGameButton.setCharacterSize(50);  // Розмір шрифту
    newGameButton.setFillColor(sf::Color(252, 228, 204)); // Колір тексту
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
    centerButton(backButton, window, 0);


    languageButton.setString("Language: English");
    languageButton.setCharacterSize(50);
    languageButton.setFillColor(sf::Color(252, 228, 204));
    centerButton(languageButton, window, -100);

    backButtonForChap.setString("Back to Chapters");
    backButtonForChap.setCharacterSize(50);
    backButtonForChap.setFillColor(sf::Color::White);
    backButtonForChap.setPosition(sf::Vector2f(20.f, 20.f));
}

void Menu::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window, sf::Sprite& backgroundSprite) {
    if (event->is<sf::Event::MouseButtonPressed>()) {
        auto mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Головне меню
        if (!levelStarted && !settingsOpened && !chapterOneRunning) {
            if (newGameButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: New Game!" << std::endl;
                levelStarted = true;
            }
            else if (settingsButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: Settings!" << std::endl;
                settingsOpened = true;
            }
            else if (quitButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: Quit!" << std::endl;
                window.close();
            }
        }

        // Меню чаптерів (2-й екран)
        else if (levelStarted && !chapterOneRunning) {
            if (chapterButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: Глава 1!" << std::endl;
                chapterOneRunning = true; // Переходимо на 3-й екран
                createLevel1(window, backgroundSprite);
            }
            else if (backButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: Back to Main Menu!" << std::endl;
                levelStarted = false;
            }
        }

        // Рівень (3-й екран)
        else if (chapterOneRunning) {
            if (backButtonForChap.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: Повернення до чаптерів!" << std::endl;
                chapterOneRunning = false;
                // Повертаємось до меню чаптерів
            }
        }

        // Налаштування
        else if (settingsOpened) {
            if (languageButton.getGlobalBounds().contains(mouseWorldPos)) {
                isEnglish = !isEnglish;
                if (isEnglish) {
                    std::cout << "Switched to English!" << std::endl;
                    newGameButton.setString("New Game");
                    settingsButton.setString("Settings");
                    quitButton.setString("Quit");
                    chapterButton.setString("Chapter 1");
                    backButton.setString("Back");
                    languageButton.setString("Language: English");
                    backButtonForChap.setString("Back");
                    tohnoEnglish = true;
                }
                else {
                    std::cout << "Перемкнули на Українську!" << std::endl;
                    newGameButton.setString(L"Нова гра");
                    settingsButton.setString(L"Налаштування");
                    quitButton.setString(L"Вийти");
                    chapterButton.setString(L"Глава 1");
                    backButton.setString(L"Назад");
                    languageButton.setString(L"Language: Українська");
                    backButtonForChap.setString(L"Назад");
                    tohnoEnglish = false;
                }
            }
            else if (backButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: Back!" << std::endl;
                settingsOpened = false;
            }
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    if (!levelStarted && !settingsOpened && !chapterOneRunning) {
        window.draw(newGameButton);
        window.draw(settingsButton);
        window.draw(quitButton);
    }
    else if (levelStarted && !chapterOneRunning) {
        window.draw(chapterButton);
        window.draw(backButton);
    }
    else if (chapterOneRunning) {
        window.draw(backButtonForChap);
    }
    else if (settingsOpened) {
        window.draw(languageButton);
        window.draw(backButton);
    }
}
