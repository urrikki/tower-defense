#include "tower.h"

#include <vector>
#include<iostream>

using namespace sf;

tower::tower() : gameObject(70, 20, 640, 360, Color::Cyan)
{
    life = 4;
};

void tower::OnCollisionEnter(gameObject* objectTest)
{

    this->life = life - objectTest.;
    Collide = Stay;

}

void tower::OnCollisionExit(gameObject* objectTest)
{

    setColor(sf::Color::Cyan);

}

void tower::lifeBrick()
{
    if (life == 4)
    {
        setColor(sf::Color::Cyan); // Cyan
    }
    else if (life == 3) {
        setColor(sf::Color(60, 250, 0)); // Green
    }
    else if (life == 2) {
        setColor(sf::Color(120, 90, 210)); //Purple
    }
    else if (life == 1) {
        setColor(sf::Color::Yellow); // Yellow
    }
    else if (life <= 0)
    {
        isActive = false;
        setPosition(3000, 0);
    }
}

void tower::setLife(int life) {
    this->life = life;
}