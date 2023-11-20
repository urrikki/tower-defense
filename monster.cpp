#include "monster.h"

#include <vector>
#include<iostream>

using namespace sf;

Monster::Monster() : gameObject(70, 20, 640, 360, Color::Cyan)
{
    type = 1;
    speed = (100);
};

void Monster::OnCollisionEnter(gameObject* objectTest)
{
    this->life = life - 1;
    Collide = Stay;
}

void Monster::OnCollisionExit(gameObject* objectTest)
{

    lifeBrick();
    Collide = NoCollide;

}

void Monster::lifeBrick()
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

void Monster::setLife(int life) {
    this->life = life;
}