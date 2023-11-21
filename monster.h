#pragma once
#include "gameObject.h"

class Monster : public gameObject
{
public:
    
    int type;
    int speed;
    int life;
    int damage;
    float attackCooldown ; 
    float attackTimer;

    Monster();

    void OnCollisionEnter(gameObject* objectTest) override;

    void setFromType();
    void setDamage(int damage);

    void setLife(int life);
    void setType(int type);

};