#include "monster.h"

#include <vector>
#include<iostream>

using namespace sf;

Monster::Monster() : gameObject(70, 20, -20, 360, Color::Cyan)
{
    type = 1;
    setOrientation(1, 0);
};

void Monster::OnCollisionEnter(gameObject* objectTest)
{
    setSpeed(0);
    performAttack(objectTest);
};

void Monster::OnCollisionStay(gameObject* object)
{
    performAttack(object);
}

void Monster::OnCollisionExit(gameObject* object)
{

}

void Monster::setFromType()
{
    if (type == 0)
    {
        isActive = false;
    }
    else if (type == 1) //troll assasin
    {
        setLife(1);
        setDamage(7);
        setSpeed(120);
        setSizeRec(20, 20);
        
    }
    else if (type == 2) //troll tank
    {
        setLife(5);
        setDamage(2);
        setSpeed(80);
        setSizeRec(40, 40);
       
    }
}

void Monster::setType(int type)
{
    this->type = type;
}

