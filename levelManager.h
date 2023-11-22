#pragma once

#include "tower.h"
#include "monster.h"
#include "base.h"

#include <SFML/Graphics.hpp>
#include <vector>

class LevelManager {
public:
    LevelManager();
    ~LevelManager();

    void loadLevel();
    void drawLevel();

    std::vector<std::vector<Monster>> monsterGrid;
    int numColBrick;
    int numLigneBrick;

    std::vector<tower> towerGrid;
    int numTower;

    void loadTower(int type);
    void drawTower();

    int nbrLevel;

    std::pair<int, int> closestToo() ;
    float calculateDistance(gameObject* obj1, gameObject* obj2) ;

    base myBase;
};