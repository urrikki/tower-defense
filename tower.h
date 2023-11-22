#pragma once
#include "gameObject.h"
#include "ball.h"

class tower : public gameObject
{
public:
    
    tower();

    int type;
    void setFromType();

    void setType(int type);
    std::vector<gameObject*> focusOnList;

    void focusOn(gameObject* obj);

    int numBall;
    void shoot(float elapsedTime, float dx, float dy);
    std::vector<Ball> ballGrid;

    void drawBall();
};