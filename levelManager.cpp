#include "levelManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

LevelManager::LevelManager() {

    std::vector<std::vector<Brick>> brickGrid;
    numColBrick = 0;
    numLigneBrick = 0;

    std::vector<Ball> ballGrid;
    numBall = 15;

    nbrLevel = 1;
}

LevelManager::~LevelManager() {
    brickGrid.clear();
    ballGrid.clear();
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

    // Déterminer le nombre de colonnes et de lignes en fonction du fichier
    numColBrick = 0;
    numLigneBrick = 0;
    std::string line;
    while (std::getline(levelFile, line)) {
        ++numLigneBrick;
        if (line.length() > static_cast<size_t>(numColBrick)) {
            numColBrick = static_cast<int>(line.length());
        }
    }

    // Réinitialiser la position du curseur de fichier pour lire à partir du début
    levelFile.clear();
    levelFile.seekg(0, std::ios::beg);

    brickGrid.resize(numColBrick, std::vector<Brick>(numLigneBrick));

    // Lire les données du fichier et initialiser la grille
    for (int j = 0; j < numLigneBrick; ++j) {
        std::getline(levelFile, line);

        for (int i = 0; i < numColBrick; ++i) {
            if (i < static_cast<int>(line.length())) {
                int life = line[i] - '0';  // Convertir le caractère en entier
                brickGrid[i][j] = Brick();
                brickGrid[i][j].setPosition(200.0 + (i * 90.0), 60.0 + (j * 40.0));
                brickGrid[i][j].setLife(life);
                brickGrid[i][j].lifeBrick();
            }
        }
    }

    levelFile.close();
}

void LevelManager::loadBall()
{
    ballGrid.resize(numBall);
    for (int i = 0; i < numBall; ++i) {
        ballGrid[i] = Ball();
        ballGrid[i].isActive = false;
        ballGrid[i].initBall();
    }
}

void LevelManager::drawLevel(sf::RenderWindow& window) {
    for (int i = 0; i < numColBrick; ++i) {
        for (int j = 0; j < numLigneBrick; ++j) {
            brickGrid[i][j].drawShape(window);
        }
    }

}