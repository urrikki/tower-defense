#pragma once

#include <SFML/Graphics.hpp>
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
    class Sprite;
}


class gameObject
{
private:
    float dx;
    float dy;
    std::vector<gameObject*> beCollide;
    bool bAlreadyHasCollision = false; //

public:
    gameObject(int w, int h, float x, float y, sf::Color color);
    gameObject(float r, float x, float y, sf::Color color);
    gameObject(int w, int h, float x, float y, const char* path);

    float w;
    float h;
    float r;
    float x;
    float y;
    float angle;
    bool isActive;
    float damage;
    float attackCooldown ;
    float attackTimer;
    float maxlife;
    float life;

    CollideType Collide;

    sf::Shape* shape;
    ShapeType shapeType;
    sf::Color m_color;
    sf::Sprite sprite;

    void setPosition(float x, float y);
    float getX();
    float getY();

    int getWidth();
    int getHeight();
    float getRadius();

    float speed;
    void setSpeed(float speed);
    float getSpeed();


    void setColor(sf::Color color);
    sf::Color getColor();

    void drawShape();

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

    bool operator==(gameObject& other) ;

    void manageCollide(gameObject* objectTest);

    void setDamage(int damage);

    void setLife(int life);

    void performAttack(gameObject* objectTest);
    void canAttack(float elapsedTime);
    bool attack;

    void getHit();

    void drawHealthBar(sf::RenderWindow& window);

    void die();
};