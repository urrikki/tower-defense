#pragma once
#include "gameObject.h"

class Monster : public gameObject
{
public:
    
    int type;

    Monster();

    void OnCollisionEnter(gameObject* objectTest) override;
    void OnCollisionStay(gameObject* object) override;
    void OnCollisionExit(gameObject* object) override;

    void setFromType();

    void setType(int type);

};