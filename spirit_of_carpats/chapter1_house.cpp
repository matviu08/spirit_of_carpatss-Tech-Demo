#include "chapter1_house.h"
#include "logick.h"

const float SCALE = 50.0f;
const float CHARACTER_HALF_WIDTH = 0.5f;
const float CHARACTER_HALF_HEIGHT = 1.0f;
const float WORLD_WIDTH_METERS = 77.0f;
const float WORLD_HEIGHT_METERS = 20.0f;
const float wallHalfWidth = 0.5f;

extern bool levelStarted;
void generateHomeScene(
    sf::RenderWindow& window, sf::Sprite& background, sf::Text& backButtonWithSetings, Player& pl, sf::Font font, const std::optional<sf::Event>& event,
    std::vector<sf::Sprite>& bed,
    std::vector<sf::Sprite>& bacground_home,
    const sf::Texture& background_home_texture,
    const sf::Texture& bed_texture) {
    sf::Vector2u windowSize = window.getSize();

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
    characterShape.setSize({ CHARACTER_HALF_WIDTH * 2 * SCALE * charVisualScale, CHARACTER_HALF_HEIGHT * 2 * SCALE * charVisualScale });
    characterShape.setOrigin({ CHARACTER_HALF_WIDTH * SCALE * charVisualScale, CHARACTER_HALF_HEIGHT * SCALE * charVisualScale });
    characterShape.setFillColor(sf::Color::Red);




    bed.clear();
    bacground_home.clear();

    //sf::FloatRect Colision(300, 100, 100, 100);
    //sf::Vector2f velociry(0.1f, 0.0f);


    const float windowWidth = static_cast<float>(window.getSize().x);
    const float windowHeight = static_cast<float>(window.getSize().y);
    const float textureWidth_home = static_cast<float>(background_home_texture.getSize().x);
    const float textureHeight_home = static_cast<float>(background_home_texture.getSize().y);

    float scaleX = windowWidth / textureWidth_home;
    float scaleY = windowHeight / textureHeight_home;

    for (int i = 0; i < 1; ++i) {
        sf::Sprite backgroundSprite_home(background_home_texture);
        backgroundSprite_home.setScale(Vector2f(scaleX, scaleY));
        backgroundSprite_home.setPosition(sf::Vector2f(i * windowWidth, 0.f));
        bacground_home.push_back(backgroundSprite_home);
    }

    //const float baseWidth = 1920.f;
    //const float baseHeight = 1080.f;

    //start width for adaptation
    const float statWindth = 1920.f;
    const float statHeinght = 1080.f;

    sf::Vector2u windowSieStat = window.getSize();

    //вісі позицій
    float xRatio_stat = static_cast<float>(windowSieStat.x) / statWindth;
    float yRatio_stat = static_cast<float>(windowSieStat.y) / statHeinght;

    //start position
    const float startValueX = 1000.f;
    const float startValueY = 857.f;

    float start_bedX = startValueX * xRatio_stat;
    float y = startValueY * yRatio_stat;


    sf::Sprite bed_spawn(bed_texture);
    float scale = 0.8f + static_cast<float>(rand() % 40) / 100.0f;
    float uniformScale = min(xRatio_stat, yRatio_stat);
    bed_spawn.setScale(sf::Vector2f(scale * uniformScale, scale * uniformScale));

    float x = start_bedX;

    bed_spawn.setPosition(Vector2f(x, y));

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

    Menu menu(font, window);

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

        if (sf::Keyboard::isKeyPressed(leftBind)) {
            horizontalInput = -1.0f;
        }
        else if (sf::Keyboard::isKeyPressed(rightBind)) {
            horizontalInput = 1.0f;
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
        float spriteScale = uniformScale * screenMoveScale;




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

        sf::View defaultView = window.getDefaultView();
        window.setView(defaultView);
        window.draw(backButtonWithSetings);
        window.setView(gameView);

        window.display();
    }

    b2DestroyWorld(worldId);
    


    //for (int i = 0; i < newsCount; ++i) {
    //    sf::Sprite newspaper(newspaperTexture);
    //    float scale = 0.8f + static_cast<float>(rand() % 40) / 100.0f;
    //    float uniformScale = min(xRatio, yRatio);
    //    newspaper.setScale(sf::Vector2f(scale * uniformScale, scale * uniformScale));

    //    float rotation = static_cast<float>((rand() % 31) - 15); // [-15, 15]
    //    newspaper.setRotation(sf::degrees(rotation));

    //    float x = startX + i * spacing;
    //    newspaper.setPosition(sf::Vector2f(x, y));

    //    news.push_back(newspaper);
    //}


}
