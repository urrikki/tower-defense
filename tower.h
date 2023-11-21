#pragma once
#include "gameObject.h"

class tower : public gameObject
{
public:
    
    tower();

    void OnCollisionEnter(gameObject* objectTest) override;
    void OnCollisionExit(gameObject* objectTest) override;

    void lifeBrick();

};