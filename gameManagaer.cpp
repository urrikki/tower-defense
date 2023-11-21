#define _USE_MATH_DEFINES

#include "gameManager.h"

#include<iostream>
#include <cmath>
#include <string>

GameManager::GameManager() : window(sf::VideoMode(1280, 720), "SFML works!")
{
    
    myLevel.loadLevel();
    
   /* if (!buffer.loadFromFile("audio/background.mp3"))
    {
        std::cout << "Erreur lors du chargement du son." << std::endl;
    }*/


}


void GameManager::runGame()
{
    /*sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();*/

    while (window.isOpen())
    {

        processEvents();
        elapsedTime = clock.restart().asSeconds();
        update(elapsedTime);
        draw();
        if (levelFinish())
        {
            ++myLevel.nbrLevel;
            myLevel.loadLevel();
        }
    }
    myLevel.~LevelManager();
}

bool GameManager::levelFinish()
{
    return false;
}

void GameManager::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
            }
        }
    }
}

void GameManager::update(float elapsedTime)
{
    
   /* sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    float dx = mousePosition.x - myCanon.x;
    float dy = mousePosition.y - myCanon.y;

    myCanon.angle = std::atan2(dy, dx) * 180 / M_PI;

    if (print == true)
    {
        std::cout << myLevel.ballGrid[nbrShoot - 1].x + myLevel.ballGrid[nbrShoot - 1].r << std::endl;
        std::cout << myLevel.ballGrid[nbrShoot - 1].y << std::endl;
        print = false;
    }

    if (myCanon.angle <= 0)
    {
        myCanon.setRotation(myCanon.angle);
    }*/

    for (int j = 0; j < myLevel.numLigneBrick; ++j) 
    {

        for (int i = 0; i < myLevel.numColBrick; ++i)
        {
            myLevel.monsterGrid[i][j].move(elapsedTime);
            myLevel.monsterGrid[i][j].getCollide(&myLevel.myBase);
        }
    }
    
}

void GameManager::draw()
{
    window.clear();
    myLevel.drawLevel(window);
    window.display();
}
