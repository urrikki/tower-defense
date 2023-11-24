#pragma once

class Power {
public:
    Power();

    void setType(int type);
    bool isActive() const;
    void activatePower();
    void deactivatePower();

private:
    int type;
    bool active;
};