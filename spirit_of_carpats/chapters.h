#pragma once
#pragma comment (lib, "winmm.lib")
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include "menu.h"
#include "logick.h"
#include "location.h"
#include "Chapter1.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include <optional>

using namespace std;

void createHomeLocation(sf::RenderWindow&, sf::Sprite&, const std::optional<sf::Event>&);
void createLevel1(sf::RenderWindow&, sf::Sprite&, const std::optional<sf::Event>&);