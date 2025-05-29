#include "menu.h"




Menu::Menu(sf::Font& font) : newGameButton(font), settingsButton(font), quitButton(font) {

    newGameButton.setString("New Game"); // Текст кнопки
    newGameButton.setCharacterSize(50);  // Розмір шрифту
    newGameButton.setFillColor(sf::Color::White); // Колір тексту
    newGameButton.setPosition({ 380.f, 400.f }); // Позиція на екрані

    settingsButton.setString("Settings");
    settingsButton.setCharacterSize(50);
    settingsButton.setFillColor(sf::Color::White);
    settingsButton.setPosition({ 400.f, 500.f });

    quitButton.setString("Quit");
    quitButton.setCharacterSize(50);
    quitButton.setFillColor(sf::Color::White);
    quitButton.setPosition({ 445.f, 600.f });

}

const float SCALE = 50.0f; // Box2D units to pixels
const float CHARACTER_HALF_WIDTH = 0.5f;  // Box2D units
const float CHARACTER_HALF_HEIGHT = 1.0f; // Box2D units

void Menu::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window) {
    if (event->is<sf::Event::MouseButtonPressed>()) {
        auto mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (newGameButton.getGlobalBounds().contains(mouseWorldPos)) {
            std::cout << "Натиснуто: New Game!" << std::endl;
            
            sf::VideoMode screenSize = sf::VideoMode::getDesktopMode();
            sf::RenderWindow window(screenSize, "game!!");

            // Background
            sf::Texture backgroundTexture;
            if (!backgroundTexture.loadFromFile("assets/img/backgroundMenu_Decstop.png")) {
                std::cout << "Помилка: неможливо завантажити backgroundMenu.png!" << std::endl;
            }
            sf::Sprite backgroundSprite(backgroundTexture);
            backgroundSprite.setScale({ static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x, static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y});

            b2WorldDef worldDef = b2DefaultWorldDef();
            worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
            b2WorldId worldId = b2CreateWorld(&worldDef);

            // Ground
            b2BodyDef groundBodyDef = b2DefaultBodyDef();
            groundBodyDef.type = b2_staticBody; // Земля нерухома
            groundBodyDef.position = b2Vec2{ 0.0f, -7.0f };
            b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);

            b2Polygon groundBox = b2MakeBox(100.0f, 2.0f); // Земля стала товстіша для коректної колізії
            b2ShapeDef groundShapeDef = b2DefaultShapeDef();
            groundShapeDef.density = 0.0f; // Земля статична
            groundShapeDef.material.friction = 100.0f; // Додано тертя для кращої взаємодії
            b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

            // Character
            b2BodyDef bodyDef = b2DefaultBodyDef();
            bodyDef.type = b2_dynamicBody;
            bodyDef.position = b2Vec2{ 0.0f, 15.0f }; // Піднято вище, щоб персонаж не провалювався крізь землю
            b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

            b2Polygon dynamicBox = b2MakeBox(CHARACTER_HALF_WIDTH, CHARACTER_HALF_HEIGHT);
            b2ShapeDef shapeDef = b2DefaultShapeDef();
            shapeDef.density = 1.0f;
            shapeDef.material.friction = 0.3f;
            shapeDef.material.restitution = 0.0f; // Вимкнено відскок
            b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

            // Увімкнення персонажа для коректної взаємодії
            b2Body_SetAwake(bodyId, true);
            b2Body_SetFixedRotation(bodyId, true);

            // SFML Rectangle for character
            sf::RectangleShape characterShape;
            characterShape.setSize({ CHARACTER_HALF_WIDTH * 2 * SCALE, CHARACTER_HALF_HEIGHT * 2 * SCALE });
            characterShape.setOrigin({ CHARACTER_HALF_WIDTH * SCALE, CHARACTER_HALF_HEIGHT * SCALE });
            characterShape.setFillColor(sf::Color::Red);

            // SFML Rectangle for ground
            sf::RectangleShape groundShape;
            groundShape.setSize({ 80.0f * SCALE, 4.0f * SCALE }); // Візуальна висота для відповідності фізичній моделі
            groundShape.setOrigin({ 10.0f * SCALE, 2.0f * SCALE });
            groundShape.setFillColor(sf::Color(100, 70, 30));

            float timeStep = 1.0f / 60.0f;
            int subStepCount = 4;

            // ---- MAIN GAME LOOP ----
            while (window.isOpen()) {
                while (const std::optional event = window.pollEvent()) {
                    if (event->is<sf::Event::Closed>())
                        window.close();

                    b2Vec2 velocity = b2Body_GetLinearVelocity(bodyId);
                    float moveSpeed = 14.0f;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                        velocity.x = -moveSpeed;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                        velocity.x = moveSpeed;
                    }
                    else {
                        velocity.x = 0.0f;
                    }
                    b2Body_SetLinearVelocity(bodyId, velocity);

                    // Step physics
                    b2World_Step(worldId, timeStep, subStepCount);

                    // Drawing
                    window.clear();
                    window.draw(backgroundSprite);
                    groundShape.setPosition({ 1400, 1800 - (9.0f * SCALE) });
                    window.draw(groundShape);
                    b2Vec2 pos = b2Body_GetPosition(bodyId);
                    characterShape.setPosition({ 500 + pos.x * SCALE, 1000 - pos.y * SCALE });
                    window.draw(characterShape);
                    window.display();
                }
            }
            b2DestroyWorld(worldId);
            
        }
        else if (settingsButton.getGlobalBounds().contains(mouseWorldPos)) {
            std::cout << "Натиснуто: Settings!" << std::endl;
        }
        else if (quitButton.getGlobalBounds().contains(mouseWorldPos)) {
            std::cout << "Натиснуто: Quit!" << std::endl;
            window.close();
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(newGameButton);
    window.draw(settingsButton);
    window.draw(quitButton);
}
