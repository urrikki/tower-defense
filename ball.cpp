#include "ball.h"

#include <iostream>
#include <vector>

using namespace sf;

Ball::Ball() : gameObject(4, 1300, 600, Color(220, 150, 30))
{
    setSpeed(500);
};

void Ball::OnCollisionEnter(gameObject* object)
{  
    isActive = false;
    object->life = object->life + damage;
}

