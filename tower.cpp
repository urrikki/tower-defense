#include "tower.h"

#include <vector>
#include<iostream>

using namespace sf;

tower::tower() : gameObject(70, 20, 300, 10, Color::Cyan)
{
    type = 0;
    setRotation(90);
};


void tower::setFromType()
{
    if (type == 1) //tower damage
    {
        setDamage(2);
        setColor(sf::Color::Red);
        
    }
    else if (type == 2) //tower electric
    {
        setDamage(0.5);
        setColor(sf::Color(204, 0, 255));
    }
}

void tower::setType(int type)
{
    this->type = type;
}

void tower::focusOn(gameObject* obj)
{
    if (focusOnList.empty())
    {
        focusOnList.push_back(obj);
    }
    else if (focusOnList[0]->maxlife <= life)
    {
        focusOnList.clear();
    }   
}
