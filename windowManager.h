#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

#define DEFAULT_WIDTH 1080
#define DEFAULT_HEIGHT 720

class GameObject;
class LevelManager;

class WindowManager
{
private:
    const char* name;
    sf::RenderWindow* oWindow;
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

    const sf::Vector2i& getWindowSize();

    void Draw(LevelManager myLevel);
};
