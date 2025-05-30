#pragma once
#ifndef _LOGICK
#define _LOGICK
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
#include "menu.h"
#include "logick.h"
#include "location.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>

class Player {
	int maxHp;
	int hp;
	int velocity;
	int damage;
public:
	Player();
	void addDamage(int);
	void heal(int);
	void hpIncrease(int);
	void damageTaken(int);
	void playerSpeed(int);

	int characterHp()const;
	int characterSpeed()const;
	int characterDamage()const;
	int characterMaxHp()const;

	void characterMovement(sf::RenderWindow&);
};


#endif
