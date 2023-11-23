#pragma once
#include "levelManager.h"
#include "textManager.h"
#include "tower.h" 
#include "monster.h"

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>



class GameManager
{
public:
    GameManager();
    void runGame();

private:
    void processEvents();
    void update(float elapsedTime);
    std::string gameScore();
    //void draw();

private:

    sf::Clock clock;
    //sf::SoundBuffer buffer;

    int wave;
    float elapsedTime = 0.0;

    bool levelFinish();

    tower myTower;
    Monster myMonster;
    LevelManager myLevel;
    TextManager myText;
    Power myPower;
};
