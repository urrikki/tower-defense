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

    void loadBall();

    std::vector<std::vector<Monster>> brickGrid;
    int numColBrick;
    int numLigneBrick;

    std::vector<tower> ballGrid;
    int numBall;

    int nbrLevel;
};