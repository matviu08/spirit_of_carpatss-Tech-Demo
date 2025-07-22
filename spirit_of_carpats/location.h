#pragma once
#pragma comment (lib, "winmm.lib")
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <conio.h>
#include <cmath>
#include <algorithm>
#include <fstream>
#include "menu.h"
#include "logick.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include <random>
#include <ctime>
#include <vector>

using namespace sf;
using namespace std;




void generateForestScene(
    sf::RenderWindow& window,
    vector<sf::Sprite>& ground,
    vector<sf::Sprite>& grass,
    vector<sf::Sprite>& rock,
    vector<sf::Sprite>& trees,
    vector<sf::Sprite>& news,
    vector<sf::Sprite>& background,
    Music& Embient_Munsic,
    const sf::Texture& grassTexture,
    const sf::Texture& rockTexture,
    const sf::Texture& treeTexture,
    const sf::Texture& backgroundTexture,
    const sf::Texture& newspaperTexture);


void generateHomeScene(
    sf::RenderWindow& window,
    sf::Sprite& background,
    sf::Text& backButtonWithSetings,
    
    Player& pl,
    sf::Font font,
    
    const std::optional<sf::Event>& event,
    vector<sf::Sprite>& bed,
    vector<sf::Sprite>& axe,
    
    std::vector<sf::Sprite>& background_home,
    const sf::Texture& axe_texture,
    const sf::Texture& background_home_texture,
    const sf::Texture& bed_texture
    
);


void generate_Cave_map(
    sf::RenderWindow& window,
    const sf::Texture& Chest,
    const sf::Texture& spirit,
    const sf::Texture& Rock,
    const sf::Texture& background_caves,
    sf::Sprite& backgoudCaves,
    vector<sf::Sprite>& spirit_enemy,
    vector<sf::Sprite>& chest,
    vector<sf::Sprite>& rock
);