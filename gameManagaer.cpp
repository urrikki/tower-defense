#define _USE_MATH_DEFINES

#include "gameManager.h"

#include<iostream>
#include <cmath>
#include <string>

GameManager::GameManager() : window(sf::VideoMode(1280, 720), "SFML works!")
{
    score = 0;
    nbrShoot = 0;
    myCanon.rotateTowardOrigin(0.5, 0.5);
    myLevel.loadLevel();
    myText.addText(" Score : " + std::to_string(score), 1150, 630, sf::Color::White, 25);
    myText.addText(" Shoot " + std::to_string(nbrShoot) + "/" + std::to_string(myLevel.numBall), 1150, 660, sf::Color::White, 25);
    myLevel.loadBall();
    loadBorder();
    if (!buffer.loadFromFile("audio/background.mp3"))
    {
        std::cout << "Erreur lors du chargement du son." << std::endl;
    }


}


void GameManager::runGame()
{
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

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
            nbrShoot = 0;
            myText.setContent(1, " Shoot " + std::to_string(nbrShoot) + "/" + std::to_string(myLevel.numBall));
        }
    }
    myLevel.~LevelManager();
}

bool GameManager::levelFinish()
{
    if (nbrShoot == myLevel.numBall)
    {
        for (int k = 0; k < myLevel.numBall; ++k)
        {
            if (myLevel.ballGrid[k].isActive)
            {
                return false;
            }
        }
        return true;
    }
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
                if (myCanon.angle <= 0)
                {
                    if (nbrShoot < myLevel.numBall)
                    {
                        if (shot)
                        {
                            click = true;
                            myLevel.ballGrid[nbrShoot].isActive = true;
                        }
                    }
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {
                print = true;
            }
        }
    }
}

void GameManager::update(float elapsedTime)
{
    myText.setContent(0, " Score : " + std::to_string(score));
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

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
    }


    if (click == true)
    {
        if (shot)
        {
            ++nbrShoot;
            myText.setContent(1, " Shoot " + std::to_string(nbrShoot) + "/" + std::to_string(myLevel.numBall));


            myLevel.ballGrid[nbrShoot - 1].setPosition(myCanon.x, myCanon.y);
            myLevel.ballGrid[nbrShoot - 1].setOrientation(dx, dy);

            // Normalisation de l'orientation
            float orientationDistance = std::sqrt(myLevel.ballGrid[nbrShoot - 1].orientationX * myLevel.ballGrid[nbrShoot - 1].orientationX + myLevel.ballGrid[nbrShoot - 1].orientationY * myLevel.ballGrid[nbrShoot - 1].orientationY);
            if (orientationDistance != 0)
            {
                myLevel.ballGrid[nbrShoot - 1].orientationX /= orientationDistance;
                myLevel.ballGrid[nbrShoot - 1].orientationY /= orientationDistance;
            }
            click = false;
            if (myLevel.nbrLevel == 2)
            {
                shot = false;
            }
        }
    }

    for (int k = 0; k < myLevel.numBall; ++k)
    {
        if (myLevel.ballGrid[k].isActive)
        {
            myLevel.ballGrid[k].move(elapsedTime);


            for (int i = 0; i < myLevel.numColBrick; ++i)
            {
                for (int j = 0; j < myLevel.numLigneBrick; ++j) {

                    if (myLevel.ballGrid[k].getCollide(&myLevel.brickGrid[i][j]) != false)
                    {

                        score = score + (nbrShoot + 5 / nbrShoot);
                        if (myLevel.brickGrid[i][j].life == 0)
                        {
                            score = score + (100 / nbrShoot);
                        }
                    }

                    myLevel.brickGrid[i][j].manageCollide(&myLevel.ballGrid[k]);
                    myLevel.ballGrid[k].manageCollide(&myLevel.brickGrid[i][j]);
                }
            }



            for (int i = 0; i < numBorder; ++i)
            {
                myLevel.ballGrid[k].manageCollide(&borderGrid[i]);
            }


            if (myLevel.ballGrid[k].isShapeOnScreen(window) == false)
            {
                click = false;
                myLevel.ballGrid[k].isActive = false;
                if (myLevel.nbrLevel == 2)
                {
                    shot = true;
                }
            }
        }
    }
}

void GameManager::draw()
{
    window.clear();
    drawBorder(window);
    myLevel.drawLevel(window);
    for (int i = 0; i < myLevel.numBall; ++i)
    {
        myLevel.ballGrid[i].drawShape(window);
    }
    myCanon.drawShape(window);
    myText.draw(window);

    window.display();
}

void GameManager::drawBorder(sf::RenderWindow& window)
{
    for (int i = 0; i < numBorder; ++i) {
        borderGrid[i].drawShape(window);
    }
}

void GameManager::loadBorder()
{
    borderGrid.resize(numBorder);

    //Repopulez les borders
    borderGrid[0] = Border();
    borderGrid[0].setPosition(145, 0);
    borderGrid[0].setSizeRec(995, 15);
    borderGrid[0].setColor(sf::Color(180, 180, 200));

    borderGrid[1] = Border();
    borderGrid[1].setPosition(145, 15);
    borderGrid[1].setSizeRec(20, 700);
    borderGrid[1].setColor(sf::Color(180, 180, 200));

    borderGrid[2] = Border();
    borderGrid[2].setPosition(1120, 15);
    borderGrid[2].setSizeRec(20, 700);
    borderGrid[2].setColor(sf::Color(180, 180, 200));

}