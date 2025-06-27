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

//void Player::walking(sf::Sprite& sprite, sf::Texture walk, sf::Texture stay)
//{
//    bool isFrozen = false;
//    sf::Clock freezeClock;
//    float freezeDuration = 0.0005f; 
//
//    if (someCondition && !isFrozen) {
//        isFrozen = true;
//        freezeClock.restart();
//    }
//
//    if (isFrozen) {
//        if (freezeClock.getElapsedTime().asSeconds() >= freezeDuration) {
//            isFrozen = false;
//        }
//    }
//
//    if (!isFrozen) {
//        
//    }
//    sprite.setTexture(walk);
//    sf::sleep(sf::milliseconds(0.005f));
//    sprite.setTexture(stay);
//    sf::sleep(sf::milliseconds(0.005f));
//    sprite.setTexture(walk);
//}
