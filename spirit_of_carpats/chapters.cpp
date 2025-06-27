#include "chapters.h"
#include "location.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void createLevel1(RenderWindow& window, Sprite& backgroundSprite, const optional<Event>& event, Menu& menu) {
    cout << "Запускаємо Level 1..." << endl;
    Player pl;
       
    Texture newBackgroundTexture;
    if (!newBackgroundTexture.loadFromFile("assets/img/levl1_bg.png")) {
        cout << "неможливо завантажити background.jpg!" << endl;
        return;
    }

    Vector2u textureSize = newBackgroundTexture.getSize();
    Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    backgroundSprite.setScale(Vector2f(scaleX, scaleY));
    backgroundSprite.setPosition(Vector2f(0.f, 0.f));

    Font font;
    if (!font.openFromFile("assets/fonts/alagard-12px-unicode.ttf")) {
        cout << "Помилка: не вдалося завантажити шрифт!" << endl;
    }

    extern bool tohnoEnglish;
    Text backButtonForChap(font);
    if (tohnoEnglish) {
        backButtonForChap.setString("Exit the game");
    }
    else {
        backButtonForChap.setString(L"Вихід з гри");
    }
    backButtonForChap.setCharacterSize(50);
    backButtonForChap.setFillColor(Color::White);
    backButtonForChap.setPosition(Vector2f(20.f, 20.f));

    Text chapterText(font);
    if (tohnoEnglish) {
        chapterText.setString("Chapter 1");
    }
    else {
        chapterText.setString(L"Чаптерс 1");
    }
    chapterText.setCharacterSize(80);
    chapterText.setFillColor(Color::White);
    Vector2f pos_1(static_cast<float>(windowSize.x) / 2 - chapterText.getLocalBounds().size.x / 2, static_cast<float>(windowSize.y) / 2 - chapterText.getLocalBounds().size.y / 2);
    chapterText.setPosition(pos_1);

    Vector2f textureSizeF = static_cast<Vector2f>(Vector2u(newBackgroundTexture.getSize()));
    int repeatCount = 5;

    vector<Sprite> tiledBackgrounds;
    for (int i = 0; i < repeatCount; ++i) {
        Sprite tile(backgroundSprite);
        tile.setPosition(Vector2f(i * static_cast<float>(textureSize.x), 0.f));
        tiledBackgrounds.push_back(tile);
    }
    
    while (window.isOpen()) {
            Vector2i mousePos = Mouse::getPosition(window);
            Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            window.clear(Color::Black);
            window.draw(chapterText);
            window.display();
            sleep(seconds(2));
            for (auto& tile : tiledBackgrounds) {
                window.draw(tile);
            }
            Generation_of_chapter1(window, backgroundSprite, backButtonForChap, pl, font, event, menu);
            window.display();
    }
    
}
