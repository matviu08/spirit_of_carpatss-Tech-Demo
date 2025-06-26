#include "Chapter1.h"

const float SCALE = 50.0f;
const float CHARACTER_HALF_WIDTH = 0.5f;
const float CHARACTER_HALF_HEIGHT = 1.0f;
const float WORLD_WIDTH_METERS = 77.0f;
const float WORLD_HEIGHT_METERS = 20.0f;
const float wallHalfWidth = 0.5f;

extern bool levelStarted;

enum AnimationState {
    IDLE,
    WALKING_LEFT,
    WALKING_RIGHT
};


void createLevels1(sf::RenderWindow& window, sf::Sprite& background, sf::Text& backButtonWithSetings, Player& pl, sf::Font font, const std::optional<sf::Event>& event, Menu& menu) {
    sf::Vector2u windowSize = window.getSize();

    AnimationState currentAnimation = IDLE;


    const float REFERENCE_WIDTH = 1920.0f;
    const float REFERENCE_HEIGHT = 1080.0f;
    float scaleFactorX = (float)windowSize.x / REFERENCE_WIDTH;
    float scaleFactorY = (float)windowSize.y / REFERENCE_HEIGHT;
    float uniformScale = min(scaleFactorX, scaleFactorY);

    // Calculate screen-dependent positions
    float screenGroundY = -((float)windowSize.y * 0.35f) / SCALE; // Ground relative to screen bottom
    float screenCenterY = 0.0f; // Screen center in world coordinates
    float wallHalfHeight = ((float)windowSize.y * 0.5f) / SCALE; // Wall height based on screen height

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
    b2WorldId worldId = b2CreateWorld(&worldDef);

    // Ground positioned relative to screen
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position = b2Vec2{ WORLD_WIDTH_METERS / 2.0f, screenGroundY };
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);

    b2Polygon groundBox = b2MakeBox(WORLD_WIDTH_METERS / 2.0f, 1.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    groundShapeDef.density = 0.0f;
    groundShapeDef.material.friction = 100.0f;
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    // Left wall scaled to screen height
    b2BodyDef leftWallDef = b2DefaultBodyDef();
    leftWallDef.type = b2_staticBody;
    leftWallDef.position = b2Vec2{ 0.0f, screenCenterY };
    b2BodyId leftWallId = b2CreateBody(worldId, &leftWallDef);

    b2Polygon leftWallBox = b2MakeBox(wallHalfWidth, wallHalfHeight);
    b2ShapeDef leftWallShapeDef = b2DefaultShapeDef();
    leftWallShapeDef.density = 0.0f;
    leftWallShapeDef.material.friction = 0.5f;
    b2CreatePolygonShape(leftWallId, &leftWallShapeDef, &leftWallBox);

    // Right wall scaled to screen height
    b2BodyDef rightWallDef = b2DefaultBodyDef();
    rightWallDef.type = b2_staticBody;
    rightWallDef.position = b2Vec2{ WORLD_WIDTH_METERS + wallHalfWidth, screenCenterY };
    b2BodyId rightWallId = b2CreateBody(worldId, &rightWallDef);

    b2Polygon rightWallBox = b2MakeBox(wallHalfWidth, wallHalfHeight);
    b2ShapeDef rightWallShapeDef = b2DefaultShapeDef();
    rightWallShapeDef.density = 0.0f;
    rightWallShapeDef.material.friction = 0.5f;
    b2CreatePolygonShape(rightWallId, &rightWallShapeDef, &rightWallBox);

    // Character positioned relative to ground
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2{ 2.0f, screenGroundY + 2.0f }; // 2 meters above ground
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

    b2Polygon dynamicBox = b2MakeBox(CHARACTER_HALF_WIDTH, CHARACTER_HALF_HEIGHT);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    shapeDef.material.restitution = 0.0f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    b2Body_SetAwake(bodyId, true);
    b2Body_SetFixedRotation(bodyId, true);

    // Character visual scaled to screen
    sf::RectangleShape characterShape;
    float charVisualScale = uniformScale * ((float)windowSize.y / REFERENCE_HEIGHT);
    characterShape.setSize({ CHARACTER_HALF_WIDTH * 6 * SCALE * charVisualScale, CHARACTER_HALF_HEIGHT * 6 * SCALE * charVisualScale });
    characterShape.setOrigin({ CHARACTER_HALF_WIDTH * SCALE * charVisualScale * 3, CHARACTER_HALF_HEIGHT * SCALE * charVisualScale * 3 });
    characterShape.setFillColor(sf::Color::Transparent);

    std::vector<sf::Texture>idleFrame;
    const int counter = 4;

    for (int i = 1; i <= counter; ++i) {
        sf::Texture texture;
        std::string filname = "assets/img/Right_state_" + to_string(i) + ".png";
        if (!texture.loadFromFile(filname)) {
            cout << "errot player file!";

        }
        idleFrame.push_back(texture);
    }

    if (!characterTexture.loadFromFile("assets/img/pleyer_1cadr.png")) {
        cout << "Failed to load character texture!" << std::endl;
    }


    

    sf::Sprite characterSprite(characterTexture);

    sf::Texture grassTexture;
    sf::Texture rockTexture;
    sf::Texture treeTexture;
    sf::Texture newspaperTexture;
    sf::Texture backgroundTexture;



    rockTexture.loadFromFile("assets/img/Kamin.png");
    treeTexture.loadFromFile("assets/img/Tree_3.png");
    newspaperTexture.loadFromFile("assets/img/torn newspaper_2.png");
    backgroundTexture.loadFromFile("assets/img/levl1_bg.png");


    vector<sf::Sprite> ground;
    vector<sf::Sprite> grass;
    vector<sf::Sprite> rock;
    vector<sf::Sprite> trees;
    vector<sf::Sprite> news;

    vector<sf::Sprite> tiledBackgrounds;
    vector<sf::Sprite>bed;
    vector<sf::Sprite>bacground_home;


    generateForestScene(
        window,
        ground,
        grass,
        rock,
        trees,
        news,
        tiledBackgrounds,
        grassTexture,
        rockTexture,
        treeTexture,
        backgroundTexture,
        newspaperTexture
    );

    const float FIXED_TIMESTEP = 1.0f / 60.0f;
    const int SUB_STEP_COUNT = 4;

    // Movement constants scaled to screen size
    float screenMoveScale = (float)windowSize.y / REFERENCE_HEIGHT;
    const float MOVE_SPEED = 8.0f * screenMoveScale;
    const float JUMP_VELOCITY = 8.0f * screenMoveScale;
    const float AIR_CONTROL_FACTOR = 0.3f;

    bool jumpHeldLastFrame = false;
    bool mouseWasPressed = false;
    sf::Clock frameClock;
    float accumulator = 0.0f;

    sf::IntRect currentFrame;
    int frameWidth = 300;
    int frameHeight = 300;
    int currentFrameIndex = 0;
    int totalFrames = 4;
    sf::Clock animationClock;
    float animationSpeed = 0.2f;



    currentFrame = IntRect(Vector2i(40, 80), Vector2i(static_cast<int>(frameWidth), static_cast<int>(frameHeight)));

    characterSprite.setTextureRect(currentFrame);


    characterSprite.setOrigin(sf::Vector2f(frameWidth / 2.0f, frameHeight / 2.0f));

    while (window.isOpen()) {

        float deltaTime = frameClock.restart().asSeconds();

        deltaTime = min(deltaTime, 0.033f);
        accumulator += deltaTime;

        b2Vec2 velocity = b2Body_GetLinearVelocity(bodyId);
        b2Vec2 pos = b2Body_GetPosition(bodyId);

        // Ground detection relative to screen-based ground
        float groundCheckY = screenGroundY + 1.0f + CHARACTER_HALF_HEIGHT;
        bool onGround = (pos.y <= groundCheckY + 0.1f) && (velocity.y <= 0.1f);

        float horizontalInput = 0.0f;
        sf::Keyboard::Key leftBind = menu.getLeftKey();
        sf::Keyboard::Key rightBind = menu.getRightKey();

        AnimationState newAnimation = IDLE;

        if (sf::Keyboard::isKeyPressed(leftBind)) {
            horizontalInput = -1.0f;
            /*newAnimation = WALKING_LEFT;*/
        }
        else if (sf::Keyboard::isKeyPressed(rightBind)) {
            horizontalInput = 1.0f;
            /*newAnimation = WALKING_RIGHT;*/
        }

        float targetVelocityX = horizontalInput * MOVE_SPEED;
        float velocityChangeX = targetVelocityX - velocity.x;

        if (onGround) {
            velocity.x = targetVelocityX;
        }
        else {
            velocity.x += velocityChangeX * AIR_CONTROL_FACTOR;
        }

        bool jumpHeldThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        if (jumpHeldThisFrame && !jumpHeldLastFrame && onGround) {
            velocity.y = JUMP_VELOCITY;
        }
        jumpHeldLastFrame = jumpHeldThisFrame;

        if (newAnimation != currentAnimation) {
            currentAnimation = newAnimation;
            currentFrameIndex = 0;
            animationClock.restart();
        }

        /* if (animationClock.getElapsedTime().asSeconds() >= animationSpeed) {
            currentFrameIndex = (currentFrameIndex + 1) % totalFrames;


            int row = 0;
            switch (currentAnimation) {
            case IDLE:
                row = 0;
                break;
            case WALKING_LEFT:
                row = 1;
                break;
            case WALKING_RIGHT:
                row = 2;
                break;
            }
            currentFrame.position.x = currentFrameIndex * frameWidth;
            currentFrame.position.y = row * frameHeight;
            characterSprite.setTextureRect(currentFrame);

            animationClock.restart();
        }*/


        b2Body_SetLinearVelocity(bodyId, velocity);

        bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (!mousePressed && mouseWasPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            if (backButtonWithSetings.getGlobalBounds().contains(mouseWorldPos)) {
                std::cout << "backButton to menu!" << std::endl;
                levelStarted = false;
                b2DestroyWorld(worldId);
                window.close();
                return;
            }
        }
        mouseWasPressed = mousePressed;

        while (accumulator >= FIXED_TIMESTEP) {
            b2World_Step(worldId, FIXED_TIMESTEP, SUB_STEP_COUNT);
            accumulator -= FIXED_TIMESTEP;
        }

        pos = b2Body_GetPosition(bodyId);

        // Camera system that works with scaled world
        float viewWidth = (float)windowSize.x / uniformScale;
        float viewHeight = (float)windowSize.y / uniformScale;

        float cameraX = pos.x * SCALE;
        float cameraY = (float)windowSize.y * 0.5f;

        float halfViewWidth = viewWidth * 0.5f;
        float worldStartX = halfViewWidth;
        float worldEndX = WORLD_WIDTH_METERS * SCALE - halfViewWidth;

        cameraX = max(worldStartX, min(cameraX, worldEndX));

        sf::View gameView(sf::Vector2f(cameraX, cameraY), sf::Vector2f(viewWidth, viewHeight));
        window.setView(gameView);

        window.clear();

        for (auto& homeBg : bacground_home)
            window.draw(homeBg);

        for (auto& tile : tiledBackgrounds)
            window.draw(tile);

        for (auto& bedSprite : bed)
            window.draw(bedSprite);

        // Scale sprites based on screen size
        float spriteScale = uniformScale * screenMoveScale / 1.5f;




        for (auto& rockSprite : rock) {
            rockSprite.setScale(sf::Vector2f(spriteScale, spriteScale));
            window.draw(rockSprite);
        }

        for (auto& tile : tiledBackgrounds) {
            window.draw(tile);
        }

        for (auto& treeSprite : trees) {
            treeSprite.setScale(sf::Vector2f(spriteScale, spriteScale));
            window.draw(treeSprite);
        }

        for (auto& newsSprite : news) {
            newsSprite.setScale(sf::Vector2f(spriteScale, spriteScale));
            window.draw(newsSprite);
        }

        characterShape.setPosition(sf::Vector2f(
            pos.x * SCALE,
            (float)windowSize.y * 0.5f / uniformScale - pos.y * SCALE
        ));
        window.draw(characterShape);
        characterSprite.setPosition(sf::Vector2f(
            pos.x * SCALE,
            (float)windowSize.y * 0.5f / uniformScale - pos.y * SCALE
        ));
        characterSprite.setScale(sf::Vector2f(spriteScale, spriteScale));

        window.draw(characterSprite);

        sf::View defaultView = window.getDefaultView();
        window.setView(defaultView);
        window.draw(backButtonWithSetings);
        window.setView(gameView);

        window.display();
    }

    b2DestroyWorld(worldId);
}