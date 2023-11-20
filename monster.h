#pragma once
#include "gameObject.h"

class Monster : public gameObject
{
public:
    
    int type;
    int speed;
    int life;

    Monster();

    void OnCollisionEnter(gameObject* objectTest) override;
    void OnCollisionExit(gameObject* objectTest) override;

    void lifeBrick();
    void setLife(int life);

};