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


