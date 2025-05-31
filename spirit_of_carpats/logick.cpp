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
const float SCALE = 50.0f; 
const float CHARACTER_HALF_WIDTH = 0.5f;
const float CHARACTER_HALF_HEIGHT = 1.0f;

void Player::characterMovement(sf::RenderWindow& window)
{
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/img/Game_BackGround.png")) {
        std::cout << "Помилка: неможливо завантажити background.jpg!" << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale({
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        });

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
    b2WorldId worldId = b2CreateWorld(&worldDef);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position = b2Vec2{ 0.0f, -2.0f };
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);

    b2Polygon groundBox = b2MakeBox(100.0f, 2.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    groundShapeDef.density = 0.0f;
    groundShapeDef.material.friction = 100.0f;
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{ 0.0f, 3.0f };
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

    b2Polygon dynamicBox = b2MakeBox(CHARACTER_HALF_WIDTH, CHARACTER_HALF_HEIGHT);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    shapeDef.material.restitution = 0.0f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    b2Body_SetAwake(bodyId, true);
    b2Body_SetFixedRotation(bodyId, true);

    sf::RectangleShape characterShape;
    characterShape.setSize({ CHARACTER_HALF_WIDTH * 2 * SCALE, CHARACTER_HALF_HEIGHT * 2 * SCALE });
    characterShape.setOrigin({ CHARACTER_HALF_WIDTH * SCALE, CHARACTER_HALF_HEIGHT * SCALE });
    characterShape.setFillColor(sf::Color::Red);

    /*sf::Texture characterTexture;
    characterTexture.loadFromFile("assets/img/character.png");
    characterShape.setTexture(&characterTexture);*/


    sf::RectangleShape groundShape;
    groundShape.setSize({ 200.0f * SCALE, 4.0f * SCALE });
    groundShape.setOrigin({ 100.0f * SCALE, 2.0f * SCALE });
    groundShape.setFillColor(sf::Color(100, 70, 30));

    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;
    bool jumpHeldLastFrame = false;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        b2Vec2 velocity = b2Body_GetLinearVelocity(bodyId);
        float moveSpeed = 0.5f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            velocity.x = -moveSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            velocity.x = moveSpeed;
        }
        else {
            velocity.x = 0.0f;
        }
        
        b2Vec2 pos = b2Body_GetPosition(bodyId);
        float groundY = -2.0f + 2.0f + CHARACTER_HALF_HEIGHT;
        bool onGround = (fabs(pos.y - groundY) < 0.05f) && (fabs(velocity.y) < 0.5f);
        float jumpDuration = 1.8f;
        float jumpVelocity = 12.0f;
        float gravity = 6.0f; 
        float jumpTimer = 0.0f;

        bool jumpHeldThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        if (jumpHeldThisFrame && !jumpHeldLastFrame && onGround) {
            velocity.y = jumpVelocity;
            jumpTimer = jumpDuration;

        }
        jumpHeldLastFrame = jumpHeldThisFrame;

        if (jumpTimer > 0.0f) {
            jumpTimer -= timeStep;
            velocity.y = jumpVelocity * pow(jumpTimer / jumpDuration, 0.8f);
            

        }
        else if (!onGround) {
            b2Body_SetAwake(bodyId, false);
            velocity.y -= gravity * timeStep;
            sf::Clock timer;
            while (timer.getElapsedTime().asSeconds() < 0.01f){}
            
            b2Body_SetAwake(bodyId, true);
        }
        

        b2Body_SetLinearVelocity(bodyId, velocity);

        b2World_Step(worldId, timeStep, subStepCount);

        window.clear();
        window.draw(backgroundSprite);
        groundShape.setPosition({ 1000 / 2, 1000 - ((-2.0f + 2.0f) * SCALE) });
        window.draw(groundShape);
        pos = b2Body_GetPosition(bodyId);
        characterShape.setPosition({ 1000 / 2 + pos.x * SCALE, 1000 - pos.y * SCALE });
        window.draw(characterShape);
        window.display();
    }

    b2DestroyWorld(worldId);
}