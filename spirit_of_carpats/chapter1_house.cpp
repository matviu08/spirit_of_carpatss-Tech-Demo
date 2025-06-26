#include "chapter1_house.h"

const float SCALE = 50.0f;
const float CHARACTER_HALF_WIDTH = 0.5f;
const float CHARACTER_HALF_HEIGHT = 1.0f;
const float WORLD_WIDTH_METERS = 77.0f/2.0f;
const float WORLD_HEIGHT_METERS = 20.0f;
const float wallHalfWidth = 0.5f;

extern bool levelStarted;

void scene_home(sf::RenderWindow& window, sf::Sprite& background, sf::Text& backButtonWithSetings, Player& pl, sf::Font font, const std::optional<sf::Event>& event) {

    sf::Vector2u windowSize = window.getSize();

    const float REFERENCE_WIDTH = 1920.0f;
    const float REFERENCE_HEIGHT = 1080.0f;
    float scaleFactorX = (float)windowSize.x / REFERENCE_WIDTH;
    float scaleFactorY = (float)windowSize.y / REFERENCE_HEIGHT;
    float uniformScale = min(scaleFactorX, scaleFactorY);

    // Calculate screen-dependent positions
    float screenGroundY = -((float)windowSize.y * 0.42f) / SCALE; // Ground relative to screen bottom
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
    characterShape.setSize({ CHARACTER_HALF_WIDTH * 4 * SCALE * charVisualScale, CHARACTER_HALF_HEIGHT * 4 * SCALE * charVisualScale });
    characterShape.setOrigin({ CHARACTER_HALF_WIDTH * SCALE * charVisualScale * 2, CHARACTER_HALF_HEIGHT * SCALE * charVisualScale * 2 });
    characterShape.setFillColor(sf::Color::Red);

    //home_location
    sf::Texture background_home_texture;
    sf::Texture bed_texture;
    //sf::Texture axe_texture;

    
    //home_location
    background_home_texture.loadFromFile("assets/img/home_bg.png");
    /*bed_texture.loadFromFile("assets/img/bed_texture.png");*/
 /*   axe_texture.loadFromFile("assets/img/axe_2.png");*/

    //location_2_ountside
    std::vector<sf::Sprite> ground;
    std::vector<sf::Sprite> grass;
    std::vector<sf::Sprite> rock;
    std::vector<sf::Sprite> trees;
    std::vector<sf::Sprite> news;

    //location_1_home
    std::vector<sf::Sprite> tiledBackgrounds;
    std::vector<sf::Sprite>bed;
    //std::vector<sf::Sprite> axe;
    std::vector<sf::Sprite>background_home;

    generateHomeScene(
        window,
        background,
        backButtonWithSetings,
        pl,
        font,
        event,
        //axe,
        bed,
        background_home,
  /*      axe_texture,*/
        background_home_texture,
        bed_texture
    );

     for (auto& homeBg : background_home)
         window.draw(homeBg);

     //for (auto& spr : axe)
     //    window.draw(spr);

     for (auto& tile : tiledBackgrounds)
         window.draw(tile);

     for (auto& bedSprite : bed)
         window.draw(bedSprite);

    

    const float FIXED_TIMESTEP = 1.0f / 60.0f;
    const int SUB_STEP_COUNT = 4;

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {


            float doorX = WORLD_WIDTH_METERS - 6.0f;
            float tolerance = 6.0f;

            if (abs(pos.x - doorX) <= tolerance) {
                b2DestroyWorld(worldId);
                createLevels1(window, background, backButtonWithSetings, pl, font, event);
                return;
            }
        }

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

        /*bool jumpHeldThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
        if (jumpHeldThisFrame && !jumpHeldLastFrame && onGround) {
            velocity.y = JUMP_VELOCITY;
        }
        jumpHeldLastFrame = jumpHeldThisFrame;*/

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

        for (auto& homeBg : background_home)
            window.draw(homeBg);

        for (auto& tile : tiledBackgrounds)
            window.draw(tile);

        for (auto& bedSprite : bed)
            window.draw(bedSprite);

        float spriteScale = uniformScale * screenMoveScale;


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
}
    

