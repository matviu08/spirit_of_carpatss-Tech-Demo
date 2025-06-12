#include "Chapter1.h"

const float SCALE = 50.0f;
const float CHARACTER_HALF_WIDTH = 0.5f;
const float CHARACTER_HALF_HEIGHT = 1.0f;

extern bool levelStarted;

void createLevels1(RenderWindow& window, sf::Sprite& background, sf::Text& backButton, Player& pl) {
    sf::Vector2u windowSize = window.getSize();

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
    b2WorldId worldId = b2CreateWorld(&worldDef);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position = b2Vec2{ (float)windowSize.x - windowSize.x,(float) windowSize.y- windowSize.y};
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);

    b2Polygon groundBox = b2MakeBox(windowSize.x, 2.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    groundShapeDef.density = 0.0f; 
    groundShapeDef.material.friction = 100.0f;
    
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);


    b2BodyDef leftWallDef = b2DefaultBodyDef();
    leftWallDef.type = b2_staticBody;
    leftWallDef.position = b2Vec2{ -10.0f, 5.0f };
    b2BodyId leftWallId = b2CreateBody(worldId, &leftWallDef);

    b2Polygon leftWallBox = b2MakeBox(0.5f, 50.0f);
    b2ShapeDef leftWallShapeDef = b2DefaultShapeDef();
    leftWallShapeDef.density = 0.0f;
    leftWallShapeDef.material.friction = 0.5f;
    b2CreatePolygonShape(leftWallId, &leftWallShapeDef, &leftWallBox);

    float worldWidth = (float)window.getSize().x * 2;
    b2BodyDef rightWallDef = b2DefaultBodyDef();
    rightWallDef.type = b2_staticBody;
    rightWallDef.position = b2Vec2{ worldWidth - 10.0f, 5.0f };
    b2BodyId rightWallId = b2CreateBody(worldId, &rightWallDef);

    b2Polygon rightWallBox = b2MakeBox(0.5f, 50.0f);
    b2ShapeDef rightWallShapeDef = b2DefaultShapeDef();
    rightWallShapeDef.density = 0.0f;
    rightWallShapeDef.material.friction = 0.5f;
    b2CreatePolygonShape(rightWallId, &rightWallShapeDef, &rightWallBox);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{ 0.0f, 5.0f };
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

    vector<Sprite> ground;
    vector<Sprite> grass;
    vector<Sprite> rock;
    vector<Sprite> trees;
    vector<Sprite> news;

    Texture grassTexture;
    Texture rockTexture;
    Texture treeTexture;
    Texture newspaperTexture;
    
    rockTexture.loadFromFile("assets/img/Kamin.png");
    treeTexture.loadFromFile("assets/img/Tree_3.png");
    newspaperTexture.loadFromFile("assets/img/torn newspaper_2.png");



    generateForestScene(
        window,
        ground,
        grass,
        rock,
        trees,
        news,
        grassTexture,
        rockTexture,
        treeTexture,
        newspaperTexture
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
        b2Vec2 pos = b2Body_GetPosition(bodyId);
        float groundY = -2.0f + 4.0f + CHARACTER_HALF_HEIGHT;
        bool onGround = (fabs(pos.y - groundY) < 0.05f) && (fabs(velocity.y) < 0.5f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            move = -moveSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            move = moveSpeed;
        }
        float airControl = onGround ? 5.0f : 1.5f;
        velocity.x = move * airControl * deltaTime * SCALE * 8.0f;
        


        
        
        float jumpVelocity = 9.0f;
        float gravity = 6.0f;

        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && onGround) {
            velocity.y = jumpVelocity;
        }

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


        for (const auto& rock : rock) window.draw(rock);
        for (const auto& tree : trees) window.draw(tree);
        for (const auto& newspaper : news) window.draw(newspaper);

        characterShape.setPosition({ 1000 / 2 + pos.x * SCALE, 1000 - pos.y * SCALE });
        window.draw(characterShape);
        pos = b2Body_GetPosition(bodyId);
        window.draw(backButton);
        window.display();
    }
    b2DestroyWorld(worldId);
}
