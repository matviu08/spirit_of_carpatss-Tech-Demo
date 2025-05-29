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

using namespace std;

const float SCALE = 50.0f; // Box2D units to pixels
const float CHARACTER_HALF_WIDTH = 0.5f;  // Box2D units
const float CHARACTER_HALF_HEIGHT = 1.0f; // Box2D units

int main() {
    // --- SFML Setup ---
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Spirit of Carpats");

    // Background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/img/backgroundMenu.png")) {
        std::cout << "Помилка: неможливо завантажити backgroundMenu.png!" << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale({
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        });

    // Font
    sf::Font font;
    if (!font.openFromFile("assets/fonts/alagard-12px-unicode.ttf")) {
        std::cout << "Помилка: не вдалося завантажити шрифт!" << std::endl;
    }

    // --- Box2D World Setup ---
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
    b2WorldId worldId = b2CreateWorld(&worldDef);

    // Ground
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = b2Vec2{ 0.0f, -9.0f };
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(10.0f, 1.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    // Character
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{ 0.0f, 0.0f };
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(CHARACTER_HALF_WIDTH, CHARACTER_HALF_HEIGHT);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    // SFML Rectangle for character
    sf::RectangleShape characterShape;
    characterShape.setSize({ CHARACTER_HALF_WIDTH * 2 * SCALE, CHARACTER_HALF_HEIGHT * 2 * SCALE });
    characterShape.setOrigin({ CHARACTER_HALF_WIDTH * SCALE, CHARACTER_HALF_HEIGHT * SCALE });
    characterShape.setFillColor(sf::Color::Red);

    // SFML Rectangle for ground
    sf::RectangleShape groundShape;
    groundShape.setSize({ 20.0f * SCALE, 2.0f * SCALE });
    groundShape.setOrigin({ 10.0f * SCALE, 1.0f * SCALE });
    groundShape.setFillColor(sf::Color(100, 70, 30));

    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    // ---- MAIN GAME LOOP ----
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            b2Vec2 velocity = b2Body_GetLinearVelocity(bodyId);
            float moveSpeed = 7.0f;
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
            groundShape.setPosition({ 500, 1000 - (9.0f * SCALE) });
            window.draw(groundShape);
            b2Vec2 pos = b2Body_GetPosition(bodyId);
            characterShape.setPosition({ 500 + pos.x * SCALE, 1000 - pos.y * SCALE });
            window.draw(characterShape);
            window.display();
        }

        
        
    }
    b2DestroyWorld(worldId);
}