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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include <random>
#include <vector>

using namespace sf;
using namespace std;

class loot_box {};
class object {};
class bg {};
class for_bg {};
class ground {};
class weather {};  
class news_peper {};

void generateForestScene(RenderWindow& window,
    vector<Sprite>& trees,
    vector<Sprite>& bushes,
    vector<Sprite>& rocks,
    vector<Sprite>& grassSprites,
    vector<Sprite>& groundTiles,
    const vector<Texture>& treeTextures,
    const Texture& bushTexture,
    const Texture& rockTexture,
    const Texture& grassTexture,
    const Texture& groundTexture);