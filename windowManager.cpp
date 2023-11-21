#include "windowmanager.h"
#include <iostream>
#include "gamemanager.h"
#include "gameobject.h"

// Constructeur
WindowManager::WindowManager(int _windowWidth, int _windowHeight, const char* _name)
{
    windowSize.x = _windowWidth, windowSize.y = _windowHeight;
    name = _name;

    oWindow = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), name);
}

// Destructeur
WindowManager::~WindowManager()
{
    oWindow->close();
}


// Methods

sf::RenderWindow& WindowManager::GetRenderWindow()
{
    return *oWindow;
}

const sf::Vector2i& WindowManager::GetWindowSize()
{
    return windowSize;
}

void WindowManager::Draw(LevelManager myLevel)
{
    WindowManager::getInstance().GetRenderWindow().clear();
    myLevel.drawLevel();
    WindowManager::getInstance().GetRenderWindow().display();
}