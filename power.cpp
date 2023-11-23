#include "power.h"

Power::Power() : type(0), active(false) 
{
    // Initialisation
}

void Power::setType(int type) {
    this->type = type;
}

bool Power::isActive() const {
    return active;
}

void Power::activatePower() {
    active = true;
}

void Power::deactivatePower() {
    active = false;
}
