#include "Chapter1.h"

const float SCALE = 50.0f;
const float CHARACTER_HALF_WIDTH = 0.5f;
const float CHARACTER_HALF_HEIGHT = 1.0f;

extern bool levelStarted;

void createLevels1(sf::RenderWindow& window, sf::Sprite& background, sf::Text& backButton, Player& pl) {
    sf::Vector2u windowSize = window.getSize();

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
    b2WorldId worldId = b2CreateWorld(&worldDef);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position = b2Vec2{ (float)windowSize.x - windowSize.x,(float) windowSize.y- windowSize.y - 2.0f};
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



    sf::Texture groundTexture, grassTexture, bushTexture, rockTexture, news_peper;
    std::vector<sf::Texture> treeTextures, news_peperTexturs;

    grassTexture.loadFromFile("assets/img/grass_new.png");
    rockTexture.loadFromFile("assets/img/Kamin.png");

    vector<Sprite> trees;
    vector<Sprite> bushes;
    vector<Sprite> rocks;
    vector<Sprite> grassSprites;
    vector<Sprite> groundTiles;
    vector<Sprite> news_tiles;

    generateForestScene(
        window,
        trees,
        bushes,
        rocks,
        grassSprites,
        groundTiles,
        news_tiles,
        treeTextures,
        news_peperTexturs,
        bushTexture,
        rockTexture,
        grassTexture,
        groundTexture

    );
    
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;
    bool jumpHeldLastFrame = false;
    sf::Clock frameClock;
    float accumulator = 0.0f;
    while (window.isOpen()) {
        float deltaTime = frameClock.restart().asSeconds();

        b2Vec2 velocity = b2Body_GetLinearVelocity(bodyId);
        float moveSpeed = pl.characterSpeed();
        float move = 0.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            move = -moveSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            move = moveSpeed;
        }
        velocity.x = move * deltaTime * 60.0f * 4.5f;


        b2Vec2 pos = b2Body_GetPosition(bodyId);
        float groundY = -2.0f + 2.0f + CHARACTER_HALF_HEIGHT;
        bool onGround = (fabs(pos.y - groundY) < 0.05f) && (fabs(velocity.y) < 0.5f);
        float jumpVelocity = 9.0f;
        float gravity = 6.0f;


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && onGround) {
            velocity.y = jumpVelocity;
        }
        bool jumpHeldThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        if (jumpHeldThisFrame && !jumpHeldLastFrame && onGround) {
            velocity.y = jumpVelocity;

        }
        jumpHeldLastFrame = jumpHeldThisFrame;

        if (!onGround) {
            b2Body_SetAwake(bodyId, false);
            velocity.y -= gravity * timeStep;
            sf::Clock timer;
            while (timer.getElapsedTime().asSeconds() < 0.008f) {
            }

            b2Body_SetAwake(bodyId, true);
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && backButton.getGlobalBounds().contains(mouseWorldPos)) {
            cout << "backButton to menu!" << endl;
            levelStarted = false;
            window.close();
        }

        b2Body_SetLinearVelocity(bodyId, velocity);
        while (accumulator >= timeStep) {
            b2World_Step(worldId, timeStep, subStepCount);
            accumulator -= timeStep;
        }


        b2World_Step(worldId, timeStep, subStepCount);
        sf::Vector2f windowSize(window.getSize().x, window.getSize().y);
        sf::View view(windowSize * 0.5f, windowSize);
        window.setView(view);

        float worldStartX = 0.0f;
        float worldEndX = (float)windowSize.x * 2;

        float viewWidth = window.getSize().x;
        float halfViewWidth = viewWidth / 2.0f;

        pos = b2Body_GetPosition(bodyId);
        sf::Vector2f charScreenPos(1000 / 2 + pos.x * SCALE, 1000 - pos.y * SCALE);

        float unclampedCenterX = charScreenPos.x;
        float minCenterX = worldStartX + halfViewWidth;
        float maxCenterX = worldEndX - halfViewWidth;
        float clampedCenterX = max(minCenterX, min(unclampedCenterX, maxCenterX));


        sf::View view1(sf::Vector2f(clampedCenterX, window.getSize().y / 2.0f), sf::Vector2f(viewWidth, window.getSize().y));
        window.setView(view1);
        window.clear();
        window.draw(background);

        for (const auto& tile : groundTiles) window.draw(tile);
        for (const auto& grass : grassSprites) window.draw(grass);
        for (const auto& bush : bushes) window.draw(bush);
        for (const auto& rock : rocks) window.draw(rock);
        for (const auto& tree : trees) window.draw(tree);


        pos = b2Body_GetPosition(bodyId);
        window.draw(backButton);
        window.display();
    }

    b2DestroyWorld(worldId);
}
