#pragma once
#include "gameObject.h"

class base : public gameObject
{
public:
    int life;

    base();

    void OnCollisionEnter(gameObject* objectTest) override;
    void OnCollisionExit(gameObject* objectTest) override;

    void lifeBrick();
    void setLife(int life);

};
