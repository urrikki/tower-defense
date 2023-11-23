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
    oMenuWindow = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "Menu");
}

// Destructeur
WindowManager::~WindowManager()
{
    oWindow->close();
}

// Methods
sf::RenderWindow& WindowManager::getRenderWindow()
{
    return *oWindow;
}

sf::RenderWindow& WindowManager::getMenuWindow()
{
    return *oMenuWindow;
}

const sf::Vector2i& WindowManager::getWindowSize()
{
    return windowSize;
}

void WindowManager::draw(LevelManager myLevel, TextManager myText)
{
    WindowManager::getInstance().getRenderWindow().clear();
    myLevel.drawLevel();
    myText.drawText();
    WindowManager::getInstance().getRenderWindow().display();

}

void WindowManager::drawPause(LevelManager myLevel, TextManager myText)
{
    WindowManager::getInstance().getRenderWindow().clear();
    myLevel.drawLevel();
    myText.drawText();
 
    sf::RectangleShape rect(sf::Vector2f(200, 100));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(8);
    rect.setOutlineColor(sf::Color::White);
    rect.setPosition((WindowManager::getInstance().getRenderWindow().getSize().x - rect.getGlobalBounds().width) / 2, (WindowManager::getInstance().getRenderWindow().getSize().y - rect.getGlobalBounds().height) / 2);
    
    TextManager pause;
    pause.addText("PAUSE", (windowSize.x - 130) / 2, (windowSize.y - 90) / 2, sf::Color::White, 50);
    
    WindowManager::getInstance().getRenderWindow().draw(rect);
    for (auto& text : pause.texts)
    {
        WindowManager::getInstance().getRenderWindow().draw(text);
    }

    WindowManager::getInstance().getRenderWindow().display();
}

void WindowManager::drawMenu()
{
    WindowManager::getInstance().getMenuWindow().clear(sf::Color(210, 140, 180));
    TextManager title;
    TextManager play;

    sf::RectangleShape rect(sf::Vector2f(100, 50));
    rect.setPosition((windowSize.x - rect.getGlobalBounds().width) / 2, (windowSize.y - rect.getGlobalBounds().height) / 2 + 50);
    /*std::cout << (windowSize.x - rect.getGlobalBounds().width) / 2 << std::endl;
    std::cout << (windowSize.y - rect.getGlobalBounds().height) / 2 + 50 << std::endl;*/

    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(8);
    rect.setOutlineColor(sf::Color::Black);
    WindowManager::getInstance().getMenuWindow().draw(rect);

    title.addText("Unicorn Defense", (windowSize.x - 270) / 2, (windowSize.y - 50) / 2 - 100, sf::Color::Black,50);
    play.addText("PLAY", (windowSize.x - 50) / 2, (windowSize.y - 30) / 2 +45, sf::Color::Black,30);

    for (auto& text : title.texts)
    {
        WindowManager::getInstance().getMenuWindow().draw(text);
    }
    for (auto& text : play.texts)
    {
        WindowManager::getInstance().getMenuWindow().draw(text);
    }
    WindowManager::getInstance().getMenuWindow().display();
}