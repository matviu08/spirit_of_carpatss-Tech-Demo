#include "logick.h"

Player::Player()
{
    hp = 100;
    damage = 0;
    velocity = 0.4f;
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

void Player::playerSpeed(float speed)
{
    this->velocity = speed;
}

int Player::characterHp() const
{
    return hp;
}

float Player::characterSpeed() const
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

//CharacterAnimation::CharacterAnimation() {
//    currentFrame = 0;
//    totalFrames = 1;
//    frameTime = 0.1f;
//    currentFrameTime = 0.0f;
//    currentState = IDLE;
//    previousState = IDLE;
//}
//
//bool CharacterAnimation::loadTextures() {
//
//    if (!idleTexture.loadFromFile("assets/animations/character_idle.png")) {
//        std::cout << "Failed to load idle animation" << std::endl;
//        return false;
//    }
//    if (!walkTexture.loadFromFile("assets/animations/character_walk.png")) {
//        std::cout << "Failed to load walk animation" << std::endl;
//        return false;
//    }
//    if (!jumpTexture.loadFromFile("assets/animations/character_jump.png")) {
//        std::cout << "Failed to load jump animation" << std::endl;
//        return false;
//    }
//
//    characterSprite.setTexture(idleTexture);
//    return true;
//}
//
//void CharacterAnimation::setAnimationParameters(AnimationState state, int frames, float time) {
//    if (currentState != state) {
//        currentState = state;
//        currentFrame = 0;
//        currentFrameTime = 0.0f;
//        totalFrames = frames;
//        frameTime = time;
//
//        switch (state) {
//        case IDLE:
//            characterSprite.setTexture(idleTexture);
//            break;
//        case WALKING:
//            characterSprite.setTexture(walkTexture);
//            break;
//        case JUMPING:
//        case FALLING:
//            characterSprite.setTexture(jumpTexture);
//            break;
//        }
//    }
//}
//
//void CharacterAnimation::update(float deltaTime, bool isMoving, bool onGround, float velocityY) {
//    AnimationState newState = IDLE;
//
//    if (!onGround) {
//        newState = (velocityY > 0.1f) ? JUMPING : FALLING;
//    }
//    else if (isMoving) {
//        newState = WALKING;
//    }
//    else {
//        newState = IDLE;
//    }
//
//    switch (newState) {
//    case IDLE:
//        setAnimationParameters(IDLE, 4, 0.2f);
//        break;
//    case WALKING:
//        setAnimationParameters(WALKING, 8, 0.1f);
//        break;
//    case JUMPING:
//        setAnimationParameters(JUMPING, 3, 0.15f);
//        break;
//    case FALLING:
//        setAnimationParameters(FALLING, 2, 0.2f);
//        break;
//    }
//
//    currentFrameTime += deltaTime;
//    if (currentFrameTime >= frameTime) {
//        currentFrame = (currentFrame + 1) % totalFrames;
//        currentFrameTime = 0.0f;
//    }
//
//    int frameWidth = static_cast<int>(characterSprite.getTexture()->getSize().x) / totalFrames;
//    int frameHeight = static_cast<int>(characterSprite.getTexture()->getSize().y);
//    frameRect = sf::IntRect(sf::Vector2i(currentFrame * frameWidth, 0), sf::Vector2i(frameWidth, frameHeight));
//    characterSprite.setTextureRect(frameRect);
//}
//
//void CharacterAnimation::setPosition(const sf::Vector2f& position) {
//    characterSprite.setPosition(position);
//}
//
//void CharacterAnimation::setScale(const sf::Vector2f& scale) {
//    characterSprite.setScale(scale);
//}
//
//void CharacterAnimation::setOrigin(const sf::Vector2f& origin) {
//    characterSprite.setOrigin(origin);
//}
//
//void CharacterAnimation::flipHorizontally(bool flip) {
//    sf::Vector2f scale = characterSprite.getScale();
//    scale.x = flip ? -std::abs(scale.x) : std::abs(scale.x);
//    characterSprite.setScale(scale);
//}
//
//sf::Sprite& CharacterAnimation::getSprite() {
//    return characterSprite;
//}
//
//void CharacterAnimation::draw(sf::RenderWindow& window) {
//    window.draw(characterSprite);
//}
