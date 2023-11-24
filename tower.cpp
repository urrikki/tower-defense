// tower.cpp
#define _USE_MATH_DEFINES

#include <cmath>

#include <iostream>
#include "tower.h"

#include <cmath>

using namespace sf;

tower::tower() : gameObject(70, 20, 300, 10, "asset/tower.png", 0.4f)
{
    type = 0;
    //sprite.setRotation(90);
    rotateTowardOrigin(0.5, 0.5);
    numBall = 0;
    attackCooldown = 1.0f;
}

void tower::setFromType()
{
    if (type == 1) // tower damage
    {
        setDamage(1.25);
        setColor(sf::Color::Red);
    }
    else if (type == 2) // tower electric
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
    if (focusOnList.empty() && obj->isActive)
    {
        focusOnList.push_back(obj);
    }
    else
    {
        if (!focusOnList.empty() && !focusOnList[0]->isActive)
        {

            focusOnList.erase(focusOnList.begin());

        }
    }

}


float distance(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

void tower::shoot()
{
    if (!focusOnList.empty())
    {
        if (attack == true)
        {

            numBall++;
            ballGrid.resize(numBall);
            ballGrid[numBall - 1] = Ball();

            // Calculate the time of flight for the projectile
            float timeOfFlight = distance(getX(), getY(), focusOnList[0]->getX(), focusOnList[0]->getY()) / ballGrid[numBall - 1].getSpeed();

            // Predict the future position of the target when the projectile reaches it
            float predictedTargetX = focusOnList[0]->getX() + focusOnList[0]->getOrientationX() * focusOnList[0]->getSpeed() * timeOfFlight;
            float predictedTargetY = focusOnList[0]->getY() + focusOnList[0]->getOrientationY() * focusOnList[0]->getSpeed() * timeOfFlight;

            // Calculate the displacement between the tower and the predicted future position of the target
            float targetDx = predictedTargetX - getX();
            float targetDy = predictedTargetY - getY();

            // Update the orientation of the projectile towards the predicted future position of the target
            float targetAngle = std::atan2(targetDy, targetDx) * 180 / M_PI;

            ballGrid[numBall - 1].setDamage(damage);
            ballGrid[numBall - 1].setRotation(targetAngle);
            ballGrid[numBall - 1].setSpeed(500);
            ballGrid[numBall - 1].setOrientation(targetDx, targetDy);
            ballGrid[numBall - 1].setPosition(getX(), getY());

            float orientationDistance = std::sqrt(targetDx * targetDx + targetDy * targetDy);
            if (orientationDistance != 0)
            {
                ballGrid[numBall - 1].orientationX /= orientationDistance;
                ballGrid[numBall - 1].orientationY /= orientationDistance;
            }

            attack = false;
        }
    }
}

void tower::drawBall()
{
    for (int i = 0; i < numBall; i++)
    {
        ballGrid[i].drawShape();
    }
}
