#include "location.h"
#include <ctime>

// Функція генерації сцени лісу
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
    // Очищуємо всі попередні спрайти, щоб створити сцену заново
    trees.clear();
    rock.clear();
    news.clear();
    grass.clear();
    ground.clear();
    background.clear();

    const int backgroundRepeatCount = 10; // Кількість повторів фонового зображення для розширення сцени

    // Отримуємо розміри вікна та текстури фону (float для точності розрахунків)
    const float windowWidth = static_cast<float>(window.getSize().x);
    const float windowHeight = static_cast<float>(window.getSize().y);
    const float textureWidth = static_cast<float>(backgroundTexture.getSize().x);
    const float textureHeight = static_cast<float>(backgroundTexture.getSize().y);

    // Обчислюємо масштаб по осях X та Y, щоб текстура фону покривала вікно повністю
    // Масштаб по X = ширина вікна / ширина текстури
    float scaleX = windowWidth / textureWidth;
    // Масштаб по Y = висота вікна / висота текстури
    float scaleY = windowHeight / textureHeight;

    // Створюємо фон, розташовуючи копії текстури в ряд з масштабом
    for (int i = 0; i < backgroundRepeatCount; ++i) {
        sf::Sprite backgroundSprite(backgroundTexture);
        backgroundSprite.setScale(Vector2f(scaleX, scaleY)); // Застосовуємо обчислений масштаб
        backgroundSprite.setPosition(sf::Vector2f(i * windowWidth, 0.f)); // Зміщення по X для розміщення поруч
        background.push_back(backgroundSprite);
    }

    // ----------------------------------------------------
    // Генерація газет (news) — адаптивне позиціювання

    // Базові розміри екрану (орієнтовно Full HD)
    const float baseWidth = 1920.f;
    const float baseHeight = 1080.f;
    sf::Vector2u windowSize = window.getSize();

    // Обчислюємо коефіцієнти масштабування для ширини та висоти
    float xRatio = static_cast<float>(windowSize.x) / baseWidth;  // Співвідношення поточної ширини до базової
    float yRatio = static_cast<float>(windowSize.y) / baseHeight; // Аналогічно по висоті

    // Початкові позиції та відстань між газетами в базових пікселях
    const float baseStartX = 1000.f;
    const float baseY = 857.f;
    const float baseSpacing = 1200.f;

    // Обчислюємо масштабовані позиції на основі коефіцієнтів масштабування
    float startX = baseStartX * xRatio;  // Початкова позиція по X
    float y = baseY * yRatio;             // Фіксована позиція по Y
    float spacing = baseSpacing * xRatio; // Відстань між газетами

    int newsCount = 3; // Кількість газет

    srand(time(NULL)); // Ініціалізація генератора випадкових чисел

    for (int i = 0; i < newsCount; ++i) {
        sf::Sprite newspaper(newspaperTexture);

        // Випадковий масштаб газети у діапазоні [0.8, 1.2]
        float scale = 0.8f + static_cast<float>(rand() % 40) / 100.0f;
        // Вибираємо мінший коефіцієнт масштабу для збереження пропорцій
        float uniformScale = min(xRatio, yRatio);
        // Масштабуємо газету пропорційно
        newspaper.setScale(sf::Vector2f(scale * uniformScale, scale * uniformScale));

        // Випадковий кут обертання в межах [-15°, 15°]
        float rotation = static_cast<float>((rand() % 31) - 15);
        newspaper.setRotation(sf::degrees(rotation));

        // Позиція по X з урахуванням індексу та відступу
        float x = startX + i * spacing;
        newspaper.setPosition(sf::Vector2f(x, y));

        // Додаємо газету до списку спрайтів
        news.push_back(newspaper);
    }

    // ----------------------------------------------------
    // Генерація дерев — адаптивне розміщення і масштабування

    const int treeCount = 36;               // Кількість дерев
    const float baseTreeX = 290.f;          // Початкова X позиція в базових пікселях
    const float baseTreeY = 125.f;          // Початкова Y позиція в базових пікселях
    const float baseTreeSpacing = 250.f;    // Відстань між деревами

    // Розрахунок масштабу для позиції дерев (xRatio і yRatio знову ж)
    float treeX = baseTreeX * xRatio / 4;  // Зменшена початкова позиція X (для кращої композиції)
    float treeY = baseTreeY * yRatio;      // Масштабована позиція Y
    float treeSpacing = baseTreeSpacing * xRatio; // Масштабована відстань між деревами

    int tr = 2;       // Лічильник для коливань
    float trY = 20.0f; // Зсув по Y для ефекту хвилі

    // Перший шар дерев
    for (int i = 0; i < treeCount - 18; ++i) {
        sf::Sprite tree(treeTexture);

        // Змінюємо tr для коливального ефекту позиції по Y
        tr < 4 ? tr += 2 : tr--;

        // Позиція по X із врахуванням індексу
        float x = treeX + i * treeSpacing;

        // Коливання по Y (створення хвилястого ефекту)
        trY < 50.0f ? trY += 12.0f : trY -= 10.0f;

        // Остаточна позиція по Y з масштабуванням
        float y = (335.f + trY) * yRatio;

        tree.setPosition(sf::Vector2f(x, y));
        tree.setScale(sf::Vector2f(xRatio, yRatio)); // Масштабування дерева
        trees.push_back(tree);
    }

    // Другий шар дерев із зменшеним spacing для більшої густоти
    treeSpacing /= 2;
    for (int i = 0; i < treeCount; ++i) {
        sf::Sprite tree(treeTexture);

        tr < 4 ? tr += 2 : tr--;

        // Зміщення по X з урахуванням тр і індексу
        float x = treeX + i * treeSpacing - treeCount * tr;

        trY < 50.0f ? trY += 12.0f : trY -= 10.0f;
        float y = (435.f + trY) * yRatio;

        tree.setPosition(sf::Vector2f(x, y));
        tree.setScale(sf::Vector2f(xRatio, yRatio));
        trees.push_back(tree);
    }

    // Третій шар дерев із збільшеним spacing для рідкіснішого розташування
    treeSpacing *= 8;
    for (int i = 0; i < treeCount - 30; ++i) {
        sf::Sprite tree(treeTexture);

        tr < 4 ? tr += 2 : tr--;

        float x = treeX + i * treeSpacing;

        trY < 50.0f ? trY += 12.0f : trY -= 10.0f;
        float y = (465.f + trY) * yRatio;

        tree.setPosition(sf::Vector2f(x, y));
        tree.setScale(sf::Vector2f(xRatio, yRatio));
        trees.push_back(tree);
    }

    // ----------------------------------------------------
    // Генерація каменю — позиція і масштабування

    const int rockCount = 1;            // Кількість каменів
    const float baseRockX = -75.f;      // Базова позиція по X
    const float baseRockY = 975.f;      // Базова позиція по Y

    float rockX = baseRockX * xRatio;   // Масштабована позиція X
    float rockY = baseRockY * yRatio;   // Масштабована позиція Y

    for (int i = 0; i < rockCount; ++i) {
        sf::Sprite rockSprite(rockTexture);
        rockSprite.setPosition(sf::Vector2f(rockX, rockY));
        rockSprite.setScale(sf::Vector2f(xRatio, yRatio)); // Масштабування каменю
        rock.push_back(rockSprite);
    }
}

// ----------------------------------------------------
// Функція генерації сцени хати

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

) {
    // Отримуємо розміри вікна та текстури
    float windowWidth = float(window.getSize().x);
    float windowHeight = float(window.getSize().y);
    float texWidth = float(background_home_texture.getSize().x);
    float texHeight = float(background_home_texture.getSize().y);

    // Очищаємо вектори перед новою генерацією
    background_home.clear();
    axe.clear();

    // Створюємо спрайт фону хати та масштабуємо його пропорційно розміру вікна
    sf::Sprite bg(background_home_texture);
    float sx = windowWidth / texWidth;   // Масштаб по ширині
    float sy = windowHeight / texHeight; // Масштаб по висоті
    bg.setScale(Vector2f(sx, sy));
    bg.setPosition(Vector2f(0.f, 0.f));  // Встановлюємо позицію в лівому верхньому куті
    background_home.push_back(bg);

    // Створюємо спрайт сокири
    sf::Sprite axeSprite(axe_texture);

    // Базові розміри екрану (Full HD)
    const float baseW = 1920.f, baseH = 1080.f;

    // Вираховуємо коефіцієнти масштабування по осях
    float xRatio = windowWidth / baseW;
    float yRatio = windowHeight / baseH;

    // Вибираємо менший коефіцієнт, щоб зберегти пропорції об'єкта
    float uniform = min(xRatio, yRatio);

    // Випадковий коефіцієнт масштабу від 0.8 до 1.2
    float rnd = 0.8f + (std::rand() % 41) / 100.f;

    // Встановлюємо точку обертання спрайту по центру (щоб обертання відбувалося навколо центру)
    sf::Vector2u texSize = axe_texture.getSize();
    axeSprite.setOrigin(Vector2f(texSize.x / 2.f, texSize.y / 2.f));

    // Застосовуємо масштабування з урахуванням рандома і коефіцієнта uniform
    axeSprite.setScale(Vector2f(uniform * rnd, uniform * rnd));

    // Розміщуємо сокиру у відносних координатах відносно розміру вікна
    axeSprite.setPosition(Vector2f(
        windowWidth * 0.4f,   // 40% від ширини вікна
        windowHeight * 0.6f   // 60% від висоти вікна
    ));

    // Додаємо сокиру до відповідного вектора спрайтів
    axe.push_back(axeSprite);
}
