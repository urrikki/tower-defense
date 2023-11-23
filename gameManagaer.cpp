#define _USE_MATH_DEFINES

#include "gameManager.h"
#include "windowManager.h"
#include<iostream>
#include <cmath>
#include <string>


GameManager::GameManager() 
{
    wave = 0;
    sf::RenderWindow& window = WindowManager::getInstance().getRenderWindow();

    
    myText.addText(" Wave n" + std::to_string(wave), 1150, 630, sf::Color::White, 25);
 
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
    myLevel.loadLevel();

    myLevel.loadLevel();
    while (WindowManager::getInstance().getRenderWindow().isOpen())
    {
       
        processEvents();
        elapsedTime = clock.restart().asSeconds();
        update(elapsedTime);
        WindowManager::getInstance().draw(myLevel, myText);
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
    while (WindowManager::getInstance().getRenderWindow().pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            WindowManager::getInstance().getRenderWindow().close();
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(WindowManager::getInstance().getRenderWindow());

                if (event.mouseButton.x >= 600 && event.mouseButton.y >= 500 && event.mouseButton.x <= 650 && event.mouseButton.y <= 550)
                {
                    myPower.activatePower();
                }
                else 
                {
                    myLevel.loadTower(1);
                }

            }
        }
    }

    if (myPower.isActive())
    {
        for (int j = 0; j < myLevel.numLigneBrick; ++j)
        {
            for (int i = 0; i < myLevel.numColBrick; ++i)
            {
                myLevel.monsterGrid[i][j].setLife(0);
                myLevel.monsterGrid[i][j].die();

            }
        }
        myPower.deactivatePower();
    }
}


void GameManager::update(float elapsedTime)
{
    // Traitement des monstres
    for (int j = 0; j < myLevel.numLigneBrick; ++j)
    {
        for (int i = 0; i < myLevel.numColBrick; ++i)
        {
            myLevel.monsterGrid[i][j].move(elapsedTime);
            myLevel.monsterGrid[i][j].canAttack(elapsedTime);
            myLevel.monsterGrid[i][j].manageCollide(&myLevel.myBase);
            myLevel.monsterGrid[i][j].die();

            std::pair<int, int>closestMonster = myLevel.closestToo();

            for (int k = 0; k < myLevel.numTower; k++)
            {
                myLevel.towerGrid[k].focusOn(&myLevel.monsterGrid[closestMonster.first][closestMonster.second]);

                if (!myLevel.towerGrid[k].focusOnList.empty())
                {
                    float dx = myLevel.towerGrid[k].focusOnList[0]->getX() - myLevel.towerGrid[k].getX();
                    float dy = myLevel.towerGrid[k].focusOnList[0]->getY() - myLevel.towerGrid[k].getY();

                    myLevel.towerGrid[k].angle = std::atan2(dy, dx) * 180 / M_PI;
                    myLevel.towerGrid[k].setRotation(myLevel.towerGrid[k].angle);
                    myLevel.towerGrid[k].canAttack(elapsedTime);
                    myLevel.towerGrid[k].shoot(elapsedTime, dx, dy);
                }

                for (int z = 0; z < myLevel.towerGrid[k].numBall; z++)
                {
                    myLevel.towerGrid[k].ballGrid[z].move(elapsedTime);
                    myLevel.towerGrid[k].ballGrid[z].manageCollide(&myLevel.monsterGrid[i][j]);
                }
            }
        }
    }


}