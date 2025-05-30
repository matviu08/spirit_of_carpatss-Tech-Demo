#include "logick.h"

Player::Player()
{
	hp = 100;
	damage = 0;
	velocity = 1;
	maxHp = 100;
}
void Player::addDamage(int damage) {
	this->damage += damage;
}
void Player::heal(int heal) {
	if (hp + heal < maxHp) {
		hp += heal;
	}
	else {
		hp = maxHp;
	}
}
void Player::hpIncrease(int incr) {
	hp += incr;
	maxHp += incr;
}

void Player::damageTaken(int damageTaken)
{
	hp -= damageTaken;
}

void Player::playerSpeed(int speed)
{
	this->velocity += speed;
}

int Player::characterHp() const
{
	return hp;
}

int Player::characterSpeed() const
{
	return velocity;
}

int Player::characterDamage() const
{
	return damage;
}

int Player::characterMaxHp() const
{
	return maxHp;
}
const float SCALE = 50.0f; // Box2D units to pixels
const float CHARACTER_HALF_WIDTH = 0.5f;  // Box2D units
const float CHARACTER_HALF_HEIGHT = 1.0f; // Box2D units
void Player::characterMovement(sf::RenderWindow& window)
{
    
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/img/background.jpg")) {
        std::cout << "Помилка: неможливо завантажити backgroundMenu.png!" << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale({ static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x, static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y });

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
    b2WorldId worldId = b2CreateWorld(&worldDef);

    // Ground
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.type = b2_staticBody; // Земля нерухома
    groundBodyDef.position = b2Vec2{ 0.0f, 1.5f };
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);

    b2Polygon groundBox = b2MakeBox(100.0f, 2.0f); // Земля стала товстіша для коректної колізії
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    groundShapeDef.density = 0.0f; // Земля статична
    groundShapeDef.material.friction = 100.0f; // Додано тертя для кращої взаємодії
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    // Character
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{ 0.0f, 3.0f }; // Піднято вище, щоб персонаж не провалювався крізь землю
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                velocity.x = -moveSpeed;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                velocity.x = moveSpeed;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                velocity.y = moveSpeed;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                velocity.y = -moveSpeed;
            }
            else {
                velocity.x = 0.0f;
                velocity.y = 0.0f;
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
