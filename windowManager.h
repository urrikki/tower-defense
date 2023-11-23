#pragma once
#include "textManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

class GameObject;
class LevelManager;
class TextManager;

class WindowManager
{
private:
    const char* name;
    sf::RenderWindow* oWindow;
    sf::RenderWindow* oMenuWindow;
    sf::Vector2i windowSize;

    WindowManager(int _windowWidth = DEFAULT_WIDTH, int _windowHeight = DEFAULT_HEIGHT, const char* name = "Class Brick");

public:
    static WindowManager& getInstance()
    {
        static WindowManager instance;
        return instance;
    }

    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    ~WindowManager();

    sf::RenderWindow& getRenderWindow();
    sf::RenderWindow& getMenuWindow();

    const sf::Vector2i& getWindowSize();

    void draw(LevelManager myLevel, TextManager myText);
    void drawPause(LevelManager myLevel, TextManager myText);
    void drawMenu();
};
