#include "menu.h"




Menu::Menu(sf::Font& font) : newGameButton(font), settingsButton(font), quitButton(font), chapterButton(font), backButton(font), languageButton(font) {
    newGameButton.setString("New Game"); // Текст кнопки
    newGameButton.setCharacterSize(50);  // Розмір шрифту
    newGameButton.setFillColor(sf::Color(252, 228, 204)); // Колір тексту
    newGameButton.setPosition({ 380.f, 400.f }); // Позиція на екрані

    settingsButton.setString("Settings");
    settingsButton.setCharacterSize(50);
    settingsButton.setFillColor(sf::Color(252, 228, 204));
    settingsButton.setPosition({ 400.f, 500.f });

    quitButton.setString("Quit");
    quitButton.setCharacterSize(50);
    quitButton.setFillColor(sf::Color(252, 228, 204));
    quitButton.setPosition({ 445.f, 600.f });

    chapterButton.setString("chapter 1");
    chapterButton.setCharacterSize(50);
    chapterButton.setFillColor(sf::Color(252, 228, 204));
    chapterButton.setPosition({ 400.f, 400.f });

    backButton.setString("Back");
    backButton.setCharacterSize(50);
    backButton.setFillColor(sf::Color(252, 228, 204));
    backButton.setPosition({ 450.f, 500.f });

    languageButton.setString("Language: English");
    languageButton.setCharacterSize(50);
    languageButton.setFillColor(sf::Color(252, 228, 204));
    languageButton.setPosition({ 300.f, 400.f });
}

void Menu::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window) {
    if (event->is<sf::Event::MouseButtonPressed>()) {
        auto mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // **Якщо меню активне**
        if (!levelStarted && !settingsOpened) {
            if (newGameButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: New Game!" << std::endl;
                levelStarted = true;
            }
            else if (settingsButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: Settings!" << std::endl;
                settingsOpened = true; // **Активуємо меню налаштувань**
            }
            else if (quitButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: Quit!" << std::endl;
                window.close();
            }
        }
        // **Якщо рівень активний**
        else if (levelStarted) {
            if (chapterButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: Глава 1! Запускаємо createLevel()..." << std::endl;
                createLevel();
            }
            else if (backButton.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "Натиснуто: Back!" << std::endl;
                levelStarted = false;
            }
        }
        // **Якщо налаштування активні**
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
                }
                else {
                    std::cout << "Перемкнули на Українську!" << std::endl;
                    newGameButton.setString(L"Нова гра");
                    settingsButton.setString(L"Налаштування");
                    quitButton.setString(L"Вийти");
                    chapterButton.setString(L"Глава 1");
                    backButton.setString(L"Назад");
                    languageButton.setString(L"Language: Українська");
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
    }
}
