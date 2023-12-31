#include "monster.h"

#include <vector>
#include<iostream>

using namespace sf;

Monster::Monster() : gameObject(70, 20, 50, 360, "asset/monster.png", .6f)
{
    type = 1;
    setOrientation(1, 0);
};

void Monster::OnCollisionEnter(gameObject* objectTest)
{
    this->state = Hitting;
    performAttack(objectTest);
    if (type == 3)
    {
        this->life = this->life - 2;
    }

};

void Monster::OnCollisionStay(gameObject* object)
{
    this->state = Hitting;
    if (attack)
    {
        if (type == 3)
        {
            this->life = this->life - 2;
        }
    }
    performAttack(object);
     
}

void Monster::OnCollisionExit(gameObject* object)
{
    this->state = Move;
}

void Monster::setFromType()
{
    if (type == 0)
    {
        isActive = false;
    }
    else if (type == 1) //troll assasin
    {
        setLife(2.5);
        setDamage(7);
        setSpeed(105);
        setSizeRec(20, 20);

    }
    else if (type == 2) //troll tank
    {
        setLife(5);
        setDamage(2);
        setSpeed(80);
        setSizeRec(40, 40);

    }
    else if (type == 3) //troll boss
    {
        setLife(30);
        setDamage(10);
        setSpeed(90);
        setSizeRec(60, 60);
        setColor(sf::Color::Red);
    }
}

void Monster::setType(int type)
{
    this->type = type;
}

