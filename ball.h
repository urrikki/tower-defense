#pragma once
#include "gameObject.h"

class Ball : public gameObject
{
public:
    Ball();

    void OnCollisionEnter(gameObject* object) override;

    

};