#include "levelManager.h"
#include "windowManager.h"

#include <fstream>
#include <sstream>
#include <iostream>


LevelManager::LevelManager() {

    std::vector<std::vector<Monster>> monsterGrid;
    numColBrick = 0;
    numLigneBrick = 0;

    std::vector<tower> towerGrid;
    numTower = 0;

    nbrLevel = 1;

    round = 0;
    finish = false;
}

LevelManager::~LevelManager() {
    monsterGrid.clear();
    towerGrid.clear();
}

void LevelManager::loadTower(int type)
{
    this->numTower++;
    towerGrid.resize(numTower);
    towerGrid[numTower - 1] = tower();
    towerGrid[numTower - 1].setPosition(300 + (numTower * 100), 20);
    towerGrid[numTower - 1].setType(type);
    towerGrid[numTower - 1].setFromType();

}

void LevelManager::drawTower()
{
    for (int i = 0; i < numTower; i++)
    {
        towerGrid[i].drawShape();
    }
}

void LevelManager::loadLevel() {

    std::string levelFolderPath = "level/";
    std::string levelFileName = levelFolderPath + "level" + std::to_string(nbrLevel) + ".txt";

    // Ouvrir le fichier texte du niveau
    std::ifstream levelFile(levelFileName);
    if (!levelFile.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier du niveau : " << levelFileName << std::endl;
        return;
    }

    // D�terminer le nombre de colonnes et de lignes en fonction du fichier
    numColBrick = 0;
    numLigneBrick = 0;
    std::string line;
    while (std::getline(levelFile, line)) {
        ++numLigneBrick;
        if (line.length() > static_cast<size_t>(numColBrick)) {
            numColBrick = static_cast<int>(line.length());
        }
    }

    // R�initialiser la position du curseur de fichier pour lire � partir du d�but
    levelFile.clear();
    levelFile.seekg(0, std::ios::beg);

    monsterGrid.resize(numLigneBrick, std::vector<Monster>(numColBrick));

    // Lire les donn�es du fichier et initialiser la grille
    for (int j = 0; j < numLigneBrick; ++j) {
        std::getline(levelFile, line);

        for (int i = 0; i < numColBrick; ++i) {
            if (i < static_cast<int>(line.length())) {
                int type = line[i] - '0';  // Convertir le caract�re en entier
                monsterGrid[j][i] = Monster();
                monsterGrid[j][i].setPosition(-600 - (i * 90.0), monsterGrid[j][i].y);
                monsterGrid[j][i].setType(type);
                monsterGrid[j][i].setFromType();
                monsterGrid[j][i].isActive = false;
            }
        }
    }

    levelFile.close();
}

void LevelManager::startRound()
{
    if (!roundFinish())
    {
        ++round;
        if (round > numLigneBrick)
        {
            finish = true;
        }
        else
        {
            for (int j = 0; j < numColBrick; ++j)
            {
                if (monsterGrid[round - 1][j].type != 0)
                {
                    monsterGrid[round - 1][j].isActive = true;
                    monsterGrid[round - 1][j].state = Move;
                }
            }
        }
    }
}

bool LevelManager::roundFinish()
{
    if (!finish)
    {
        if (round != 0)
        {
            for (int j = 0; j < numColBrick; ++j)
            {
                if (monsterGrid[round - 1][j].isActive)
                {
                    return true;
                }
            }
        }
        return false;
    }
}

void LevelManager::drawLevel()
{
    // Dessiner le carré blanc
    sf::RectangleShape whiteSquare(sf::Vector2f(50.0f, 50.0f));
    whiteSquare.setFillColor(sf::Color::White);
    whiteSquare.setPosition(600.0f, 500.0f);
    WindowManager::getInstance().getRenderWindow().draw(whiteSquare);

    // Dessiner les monstres

    if (!finish)
    {
        for (int j = 0; j < numColBrick; ++j)
        {
            monsterGrid[round - 1][j].drawShape();
        }
    }

    // Dessiner les ball des tours
    for (int j = 0; j < numTower; j++)
    {
        for (int z = 0; z < towerGrid[j].numBall; z++)
        {
            towerGrid[j].drawBall();
        }
    }

    // Dessiner les tours
    drawTower();

    // Dessiner la base
    myBase.drawShape();
}

std::pair<int, int> LevelManager::closestToo()
{
    float minDistance = std::numeric_limits<float>::max();
    int closestI = -1;
    int closestJ = -1;

    for (int i = 0; i < numLigneBrick; ++i) {
        for (int j = 0; j < numColBrick; ++j) {
            if (monsterGrid[i][j].isActive)
            {
                float distance = calculateDistance(&monsterGrid[i][j], &myBase);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestI = i;
                    closestJ = j;
                }
            }
        }
    }

    return std::make_pair(closestI, closestJ);
}

float LevelManager::calculateDistance(gameObject* obj1, gameObject* obj2)
{
    float dx = obj1->getX() - obj2->getX();
    float dy = obj1->getY() - obj2->getY();
    return std::sqrt(dx * dx + dy * dy);
}

