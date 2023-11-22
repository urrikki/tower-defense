#pragma once
#include "gameObject.h"

class tower : public gameObject
{
public:
    
    tower();

    int type;
    void setFromType();

    void setType(int type);
    std::vector<gameObject*> focusOnList;

    void focusOn(gameObject* obj);
};