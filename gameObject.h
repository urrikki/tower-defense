#pragma once

#include <SFML/Graphics/Color.hpp>
#include <vector>

typedef enum CollideType
{
    NoCollide,
    Enter,
    Stay,
    Exit,
};

typedef enum CollideSide
{
    None,
    Right,
    Left,
    Top,
    Bottom,
};

typedef enum ShapeType
{
    NoShape,
    Rectangle,
    Square,
    Circle,
};

namespace sf
{
    class Shape;
    class RenderWindow;
}


class gameObject
{
private:
    float dx;
    float dy;
    std::vector<gameObject> beCollide;
    bool bAlreadyHasCollision = false; //

public:
    gameObject(int w, int h, float x, float y, sf::Color color);
    gameObject(float r, float x, float y, sf::Color color);

    float w;
    float h;
    float r;
    float x;
    float y;
    float angle;
    bool isActive;

    CollideType Collide;

    sf::Shape* shape;
    ShapeType shapeType;
    sf::Color m_color;

    void setPosition(float x, float y);
    float getX();
    float getY();

    int getWidth();
    int getHeight();
    float getRadius();

    float speed;
    void setSpeed(float speed);


    void setColor(sf::Color color);
    sf::Color getColor();

    void drawShape(sf::RenderWindow& window);

    bool getCollide(gameObject* objectTest);
    CollideSide getCollideSide(gameObject* objectTest);

    ShapeType getShapeType();


    float orientationX;
    float orientationY;

    void setOrientation(float x, float y);
    float getOrientationX();
    float getOrientationY();

    void move(float elapsedTimeF);

    void rotateTowardOrigin(float x, float y);
    void setRotation(float angle);

    virtual void OnCollisionEnter(gameObject* object);
    virtual void OnCollisionStay(gameObject* object);
    virtual void OnCollisionExit(gameObject* object);

    bool isShapeOnScreen(sf::RenderWindow& window);

    void setSizeRec(int w, int h);

    void setSizeCir(float r);

    CollideSide sideForRebound;

    bool operator==(const gameObject& other) const;

    void manageCollide(gameObject* objectTest);

};