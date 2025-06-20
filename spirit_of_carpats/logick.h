#pragma once
#pragma comment (lib, "winmm.lib")
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>

class Player {
	int maxHp;
	int hp;
	float velocity;
	int damage;
public:
	Player();
	void addDamage(int);
	void heal(int);
	void hpIncrease(int);
	void damageTaken(int);
	void playerSpeed(float);

	int characterHp()const;
	float characterSpeed()const;
	int characterDamage()const;
	int characterMaxHp()const;

};

//class CharacterAnimation {
//private:
//    sf::Texture idleTexture;
//    sf::Texture walkTexture;
//    sf::Texture jumpTexture;
//    sf::Sprite characterSprite;
//
//    int currentFrame;
//    int totalFrames;
//    float frameTime;
//    float currentFrameTime;
//    sf::IntRect frameRect;
//
//    enum AnimationState {
//        IDLE,
//        WALKING,
//        JUMPING,
//        FALLING
//    };
//    AnimationState currentState;
//    AnimationState previousState;
//
//public:
//    CharacterAnimation();
//
//    bool loadTextures();
//
//    void setAnimationParameters(AnimationState state, int frames, float time);
//
//    void update(float deltaTime, bool isMoving, bool onGround, float velocityY);
//    void setPosition(const sf::Vector2f& position);
//
//    void setScale(const sf::Vector2f& scale);
//
//    void setOrigin(const sf::Vector2f& origin);
//
//    void flipHorizontally(bool flip);
//
//    sf::Sprite& getSprite();
//
//    void draw(sf::RenderWindow& window);
//};
//
