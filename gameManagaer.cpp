#define _USE_MATH_DEFINES

#include "gameManager.h"

#include<iostream>
#include <cmath>
#include <string>

#include "windowManager.h"

GameManager::GameManager() 
{
    wave = 0;
    sf::RenderWindow& window = WindowManager::getInstance().getRenderWindow();

    myLevel.loadLevel();
    myText.addText(" Wave n" + std::to_string(wave), 1150, 630, sf::Color::White, 25);
    myAudio.loadAudio("audio/background.mp3");
    //myAudio.loadAudio("audio/shoot.wav");
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
    myAudio.playAudio(0);

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
                myLevel.loadTower(1);
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
            myLevel.monsterGrid[i][j].canAttack(elapsedTime, &myLevel.myBase);
            myLevel.monsterGrid[i][j].manageCollide(&myLevel.myBase);
            for (int k = 0; k < myLevel.numTower; k++)
            {
                std::pair<int, int> closestMonster = myLevel.closestToo();
                myLevel.towerGrid[k].focusOn(&myLevel.monsterGrid[closestMonster.first][closestMonster.second]);
                
            }
            
        }
    }

    
    
}