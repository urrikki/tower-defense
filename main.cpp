#include "gameManager.h"
#include "windowManager.h"

int main()
{
    bool launchGame = false;
    while (WindowManager::getInstance().getMenuWindow().isOpen())
    {

        WindowManager::getInstance().drawMenu();
        sf::Event event;
        while (WindowManager::getInstance().getMenuWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WindowManager::getInstance().getMenuWindow().close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(WindowManager::getInstance().getMenuWindow());

                    if (mousePosition.x >= 590 && mousePosition.x <= 690 && mousePosition.y >= 385 && mousePosition.y <= 435)
                    {
                        launchGame = true;
                        WindowManager::getInstance().getMenuWindow().close();
                    }
                }
            }
        }


    }
    if (launchGame)
    {
        GameManager myGame;
        myGame.runGame();
    }
    return 0;
}