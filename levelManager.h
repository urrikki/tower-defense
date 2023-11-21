#pragma once

#include "tower.h"
#include "monster.h"

#include <SFML/Graphics.hpp>
#include <vector>
class LevelManager {
public:
    LevelManager();
    ~LevelManager();

    void loadLevel();
    void drawLevel(sf::RenderWindow& window);

    std::vector<std::vector<Monster>> monsterGrid;
    int numColBrick;
    int numLigneBrick;

    std::vector<tower> towerGrid;
    int numBall;

    int nbrLevel;
};