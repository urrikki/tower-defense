#define _USE_MATH_DEFINES

#include "gameManager.h"
#include "windowManager.h"
#include<iostream>
#include <cmath>
#include <string>


GameManager::GameManager()
{
    wave = myLevel.round;
    sf::RenderWindow& window = WindowManager::getInstance().getRenderWindow();


    myText.addText(" Wave n" + std::to_string(wave), 1150, 630, sf::Color::White, 25);
    isPaused = false;
    myAudio.loadAudio("audio/background.mp3");

}


void GameManager::runGame()
{
    myAudio.playAudio(0);

    myLevel.loadLevel();
    while (WindowManager::getInstance().getRenderWindow().isOpen())
    {

        processEvents();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            isPaused = !isPaused; // Inverse l'état de la pause
            sf::sleep(sf::milliseconds(500));
        }

        elapsedTime = clock.restart().asSeconds();

        if (!isPaused)
        {
            update(elapsedTime);
            WindowManager::getInstance().draw(myLevel, myText);
            if (levelFinish())
            {
                ++myLevel.nbrLevel;
                myLevel.loadLevel();
            }
        }
        else
        {
            if (myLevel.finish == true)
            {
                WindowManager::getInstance().drawWin(myLevel, myText);
            }
            else if (!myLevel.myBase.isActive)
            {
                WindowManager::getInstance().drawLoose(myLevel, myText);
            }
            else
            {
                WindowManager::getInstance().drawPause(myLevel, myText);
            }
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
    myText.addText("Buy", 300 + (myLevel.numTower + 1 * 100), 20, sf::Color::White, 20);
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
                    if (mousePosition.x >= 300 + (myLevel.numTower + 1 * 100) && mousePosition.y >= 20 && mousePosition.x <= 300 + (myLevel.numTower + 1 * 100) + 20 && mousePosition.y <= 40)
                    {
                        myText.addText("dm", 300 + (myLevel.numTower + 1 * 100) - 30, 50, sf::Color::White, 20);
                        myText.addText("gl", 300 + (myLevel.numTower + 1 * 100), 50, sf::Color::White, 20);
                        myText.addText("bk", 300 + (myLevel.numTower + 1 * 100) + 30, 50, sf::Color::White, 20);
                    }
                    else
                    {
                        // Si le clic est en dehors de la zone "Buy", vérifiez les choix "dm gl bk"
                        // Si l'un de ces choix est cliqué, effectuez l'achat approprié
                        if (mousePosition.x >= 300 + (myLevel.numTower + 1 * 100) - 30 && mousePosition.x <= (300 + (myLevel.numTower + 1 * 100) - 30 + 20) &&
                            mousePosition.y >= 50 && mousePosition.y <= 70)
                        {
                            myLevel.loadTower(1);  // Choix "dm"
                        }
                        else if (mousePosition.x >= 300 + (myLevel.numTower + 1 * 100) && mousePosition.x <= 300 + (myLevel.numTower + 1 * 100) + 20 &&
                            mousePosition.y >= 50 && mousePosition.y <= 70)
                        {
                            myLevel.loadTower(2);  // Choix "gl"
                        }
                        else if (mousePosition.x >= 300 + (myLevel.numTower + 1 * 100) + 30 && mousePosition.x <= 300 + (myLevel.numTower + 1 * 100) + 50 &&
                            mousePosition.y >= 50 && mousePosition.y <= 70)
                        {
                            myLevel.loadTower(3);  // Choix "bk"
                        }

                        // Effacez les choix après l'achat
                        myText.texts.clear();
                    }
                }


            }
        }
    }

    if (myPower.isActive())
    {
        for (int j = 0; j < myLevel.numColBrick; ++j)
        {
            for (int i = 0; i < myLevel.numLigneBrick; ++i)
            {
                if (myLevel.monsterGrid[i][j].isShapeOnScreen())
                {
                    myLevel.monsterGrid[i][j].setLife(0);
                    myLevel.monsterGrid[i][j].die();
                }
            }
        }
        myPower.deactivatePower();
    }
}

bool shoot = false;
void GameManager::update(float elapsedTime)
{
    winORloose();
    myLevel.startRound();
    //myText.setContent(0 , " Wave n" + std::to_string(wave));
    std::pair<int, int>closestMonster = myLevel.closestToo();

    for (int k = 0; k < myLevel.numTower; k++)
    {
        if (closestMonster.first != -1 && closestMonster.second != -1)
        {
            myLevel.towerGrid[k].focusOn(&myLevel.monsterGrid[closestMonster.first][closestMonster.second]);
        }
        if (!myLevel.towerGrid[k].focusOnList.empty())
        {
            float dx = myLevel.towerGrid[k].focusOnList[0]->getX() - myLevel.towerGrid[k].getX();
            float dy = myLevel.towerGrid[k].focusOnList[0]->getY() - myLevel.towerGrid[k].getY();

            myLevel.towerGrid[k].angle = std::atan2(dy, dx) * 180 / M_PI;
            if (myLevel.towerGrid[k].focusOnList[0]->isShapeOnScreen())
            {
                shoot = true;
            }
        }
        else
        {
            shoot = false;
        }
        if (shoot)
        {
            myLevel.towerGrid[k].setRotation(myLevel.towerGrid[k].angle);
            myLevel.towerGrid[k].canAttack(elapsedTime);
            myLevel.towerGrid[k].shoot();
        }
        for (int z = 0; z < myLevel.towerGrid[k].numBall; z++)
        {
            myLevel.towerGrid[k].ballGrid[z].move(elapsedTime);
            if (!myLevel.towerGrid[k].focusOnList.empty())
            {
                myLevel.towerGrid[k].ballGrid[z].manageCollide(myLevel.towerGrid[k].focusOnList[0]);
            }
        }
    }

    for (int i = 0; i < myLevel.numLigneBrick; ++i)
    {
        for (int j = 0; j < myLevel.numColBrick; ++j)
        {

            myLevel.monsterGrid[i][j].move(elapsedTime);
            myLevel.monsterGrid[i][j].canAttack(elapsedTime);
            myLevel.monsterGrid[i][j].manageCollide(&myLevel.myBase);
            myLevel.monsterGrid[i][j].die();
        }
    }

    myLevel.myBase.die();
}

void GameManager::winORloose()
{
    if (myLevel.finish == true || !myLevel.myBase.isActive)
    {
        isPaused = !isPaused;
    }

}