#include "location.h"

void generateForestScene(
    sf::RenderWindow& window,
    std::vector<sf::Sprite>& ground,
    std::vector<sf::Sprite>& grass,
    std::vector<sf::Sprite>& rock,
    std::vector<sf::Sprite>& trees,
    std::vector<sf::Sprite>& news,
    std::vector<sf::Sprite>& background,
    const sf::Texture& grassTexture,
    const sf::Texture& rockTexture,
    const sf::Texture& treeTexture,
    const sf::Texture& backgroundTexture,
    const sf::Texture& newspaperTexture)
{
    // Очистка попередніх спрайтів
    trees.clear();
    rock.clear();
    news.clear();
    grass.clear();
    ground.clear();
    background.clear();

    const int backgroundRepeatCount = 10; // 🔹 Розширюємо фон для великої сцени

    // 🎨 Генерація повторюваного бекграунду
    const float windowWidth = static_cast<float>(window.getSize().x);
    const float windowHeight = static_cast<float>(window.getSize().y);
    const float textureWidth = static_cast<float>(backgroundTexture.getSize().x);
    const float textureHeight = static_cast<float>(backgroundTexture.getSize().y);

    float scaleX = windowWidth / textureWidth;
    float scaleY = windowHeight / textureHeight;

    for (int i = 0; i < backgroundRepeatCount; ++i) {
        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setScale(Vector2f(scaleX, scaleY)); 
        backgroundSprite.setPosition(sf::Vector2f(i * windowWidth, 0.f)); 
        background.push_back(backgroundSprite);
    }
   
    // 📰 Генерація газет
    const float baseWidth = 1920.f;
    const float baseHeight = 1080.f;
    sf::Vector2u windowSize = window.getSize();

    float xRatio = static_cast<float>(windowSize.x) / baseWidth;
    float yRatio = static_cast<float>(windowSize.y) / baseHeight;

    const float baseStartX = 1000.f;
    const float baseY = 857.f;
    const float baseSpacing = 1200.f;

    float startX = baseStartX * xRatio;
    float y = baseY * yRatio;
    float spacing = baseSpacing * xRatio;

    int newsCount = 3;

    srand(time(NULL));
    float agle = rand() % (100 - 0) + 0;

    for (int i = 0; i < newsCount; ++i) {
        sf::Sprite newspaper(newspaperTexture);
        float scale = 0.8f + static_cast<float>(rand() % 40) / 100.0f;
        float uniformScale = min(xRatio, yRatio);
        newspaper.setScale(sf::Vector2f(scale * uniformScale, scale * uniformScale));
        
        float rotation = static_cast<float>((rand() % 31) - 15); // [-15, 15]
        newspaper.setRotation(sf::degrees(rotation));

        float x = startX + i * spacing;
        newspaper.setPosition(sf::Vector2f(x, y));

        news.push_back(newspaper);
    }

    // базове розширення
    const float baseWidth_for_tree = 1920.f;
    const float baseHeight_for_tree = 1080.f;

    float xRatio_tree = static_cast<float>(windowSize.x) / baseWidth;
    float yRatio_tree = static_cast<float>(windowSize.y) / baseHeight;

    //adaprive generation of tree
    const int treeCount = 3;
    const float baseTreeX = 1400.f;
    const float baseTreeY = 425.f;
    const float baseTreeSpacing = 1200.f;

    float treeX = baseTreeX * xRatio;
    float treeY = baseTreeY * yRatio;
    float treeSpacing = baseTreeSpacing * xRatio;

    for (int i = 0; i < treeCount; ++i) {
        sf::Sprite tree(treeTexture);
        float x = treeX + i * treeSpacing;
        tree.setPosition(sf::Vector2f(x, treeY));
        tree.setScale(sf::Vector2f(xRatio, yRatio)); 
        trees.push_back(tree);
    }

    // adaprive generation of rock
    const int rockCount = 1;
    const float baseRockX = -75.f;
    const float baseRockY = 975.f;

    float rockX = baseRockX * xRatio;
    float rockY = baseRockY * yRatio;

    for (int i = 0; i < rockCount; ++i) {
        sf::Sprite rockSprite(rockTexture);
        rockSprite.setPosition(sf::Vector2f(rockX, rockY));
        rockSprite.setScale(sf::Vector2f(xRatio, yRatio));
        rock.push_back(rockSprite);
    }
}

//генерація хати

void generateHomeScene(
    sf::RenderWindow& window,
    sf::Sprite& background,
    sf::Text& backButtonWithSetings,
    Player& pl,
    sf::Font font,
    const std::optional<sf::Event>& event,
    vector<sf::Sprite>& bed,
    vector<sf::Sprite>& axe,
    vector<sf::Sprite>& background_home,
    const sf::Texture& axe_texture,
    const sf::Texture& background_home_texture,
    const sf::Texture& bed_texture
    
){
    float windowWidth = float(window.getSize().x);
    float windowHeight = float(window.getSize().y);
    float texWidth = float(background_home_texture.getSize().x);
    float texHeight = float(background_home_texture.getSize().y);

    background_home.clear();
    axe.clear();

    
	sf::Sprite bg(background_home_texture);
	float sx = windowWidth / texWidth;
	float sy = windowHeight / texHeight;
	bg.setScale(Vector2f(sx, sy));
	bg.setPosition(Vector2f(0.f, 0.f));
	background_home.push_back(bg);
    

    
	sf::Sprite axeSprite(axe_texture);

	axeSprite.setOrigin(Vector2f(
		axe_texture.getSize().x * 0.5f,
		axe_texture.getSize().y * 0.5f
	));

	const float baseW = 1920.f, baseH = 1080.f;
	float xRatio = windowWidth / baseW;
	float yRatio = windowHeight / baseH;
	float uniform = min(xRatio, yRatio);

	float rnd = 0.8f + (std::rand() % 41) / 100.f;
	axeSprite.setScale(Vector2f(uniform * rnd, uniform * rnd));

	axeSprite.setPosition(Vector2f(
		windowWidth * 0.5f,
		windowHeight * 0.6f
	));


	axe.push_back(axeSprite);
    

}
