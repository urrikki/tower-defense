#include "levelManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "windowManager.h"

LevelManager::LevelManager() {

    std::vector<std::vector<Monster>> monsterGrid;
    numColBrick = 0;
    numLigneBrick = 0;

    std::vector<tower> towerGrid;
    numBall = 0;

    nbrLevel = 1;
}

LevelManager::~LevelManager() {
    monsterGrid.clear();
    towerGrid.clear();
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

    monsterGrid.resize(numColBrick, std::vector<Monster>(numLigneBrick));

    // Lire les donn�es du fichier et initialiser la grille
    for (int j = 0; j < numLigneBrick; ++j) {
        std::getline(levelFile, line);

        for (int i = 0; i < numColBrick; ++i) {
            if (i < static_cast<int>(line.length())) {
                int type = line[i] - '0';  // Convertir le caract�re en entier
                monsterGrid[i][j] = Monster();
                monsterGrid[i][j].setPosition(-100 - (i * 90.0), monsterGrid[i][j].y);
                monsterGrid[i][j].setType(type);
                monsterGrid[i][j].setFromType();
            }
        }
    }

    levelFile.close();
}


void LevelManager::drawLevel() 
{
    for (int i = 0; i < numColBrick; ++i) 
    {
        for (int j = 0; j < numLigneBrick; ++j) 
        {
            monsterGrid[i][j].drawShape(WindowManager::getInstance().getRenderWindow());
        }
    }
    myBase.drawShape(WindowManager::getInstance().getRenderWindow());
}