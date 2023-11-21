#include "base.h"

#include <vector>
#include<iostream>

using namespace sf;

base::base() : gameObject(80, 80, 640, 660, Color::Cyan)
{
    setLife(70);
};

void base::OnCollisionEnter(gameObject* objectTest)
{
    this->life = life - objectTest->damage;
    setColor(sf::Color::Red);
}

void base::OnCollisionExit(gameObject* objectTest)
{
    setColor(sf::Color::Cyan);
}
