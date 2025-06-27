
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
#include "menu.h"
#include "logick.h"
#include "location.h"
#include "chapter1_house.h"
#include "chapters.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include "Ñhapter1General.h"

void createLevels1(RenderWindow& window, Sprite& background, Text& backButtonWithSetings, Player& pl, Font font, const optional<Event>& event, Menu& menu,float spriteScale);


using namespace std;