#define _USE_MATH_DEFINES

#include "gameObject.h"
#include "windowManager.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <iostream>
#include <vector>


using namespace sf;

gameObject::gameObject(int w, int h, float x, float y, sf::Color color)
{
    this->w = w;
    this->h = h;
    this->x = x;
    this->y = y;
    m_color = color;

    
    shapeType = NoShape;
    orientationX = 0;
    orientationY = 0;
    damage = 0;
    speed = (0);
    attackCooldown = 2.0f;
    attackTimer = 0.0f;
    maxlife = 0;
    attack = false;

    shape = new RectangleShape(sf::Vector2f(w, h));
    if (w == h)
    {
        shapeType = Square;
    }
    else
    {
        shapeType = Rectangle;
    }

    shape->setPosition(x, y);
    shape->setFillColor(m_color);

    Collide = NoCollide;
    sideForRebound = None;
    isActive = true;
}


gameObject::gameObject( float r, float x, float y, sf::Color color)
{
    this->x = x;
    this->y = y;
    this->r = r;
    m_color = color;

    orientationX = 0;
    orientationY = 0;
    shapeType = Circle;
    damage = 0;
    speed = (0);
    attackCooldown = 200.0f;
    attackTimer = 0.0f;
    maxlife = 0;
    attack = false;

    shape = new CircleShape(r);
    shape->setPosition(x, y);
    shape->setFillColor(m_color);

    Collide = NoCollide;
    isActive = true;
    sideForRebound = None;
}

gameObject::gameObject(int w, int h, float x, float y, const char* path)
{
    this->w = w;
    this->h = h;
    this->x = x;
    this->y = y;
    
    Texture texture;
    if (!texture.loadFromFile(path))
    {
        std::cout << "failed" << std::endl;

        system("pause");

    }

    sprite.setTexture(texture);
    
    sprite.setTextureRect(IntRect(0, 0, w, h));


    shapeType = NoShape;
    orientationX = 0;
    orientationY = 0;
    damage = 0;
    speed = (0);
    attackCooldown = 2.0f;
    attackTimer = 0.0f;
    maxlife = 0;
    attack = false;

    shape = new RectangleShape(sf::Vector2f(w, h));
    if (w == h)
    {
        shapeType = Square;
    }
    else
    {
        shapeType = Rectangle;
    }


    Collide = NoCollide;
    sideForRebound = None;
    isActive = true;
}



void gameObject::setSpeed(float speed)
{
    this->speed = speed;
}

float gameObject::getSpeed()
{
    return speed;
}

void gameObject::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
    shape->setPosition(x, y);
};

void gameObject::setSizeRec(int w, int h)
{
    this->w = w;
    this->h = h;
    dynamic_cast<sf::RectangleShape*>(shape)->setSize(sf::Vector2f(w, h));
}

void gameObject::setSizeCir(float r)
{
    this->r = r;
}

float gameObject::getX()
{
    return x;
}

float gameObject::getY()
{
    return y;
}

void gameObject::setColor(Color color)
{
    m_color = color;
    shape->setFillColor(color);
};

Color gameObject::getColor()
{
    return m_color;
}


int gameObject::getWidth()
{
    return w;
};

int gameObject::getHeight()
{
    return h;
};

float gameObject::getRadius()
{
    return r;
};


ShapeType gameObject::getShapeType()
{
    return shapeType;
}

struct distanceResult {
    std::string name;
    float value;

    distanceResult(const std::string& n, float v) : name(n), value(v) {}
};


void gameObject::setOrientation(float x, float y)
{
    this->orientationX = x;
    this->orientationY = y;
}

float gameObject::getOrientationX()
{
    return orientationX;
}

float gameObject::getOrientationY()
{
    return orientationY;
}

// --Move

void gameObject::move(float elapsedTimeF)
{
    float newX = x + (speed * (elapsedTimeF * orientationX));
    float newY = y + (speed * (elapsedTimeF * orientationY));
    setPosition(newX, newY);
}


// --Collision

bool gameObject::getCollide(gameObject* objectTest)
{
    if (isActive == true && objectTest->isActive == true)
    {
        if (getShapeType() == ShapeType::Circle)
        {
            this->w = r;
            this->h = r;
        }

        if (objectTest->getShapeType() == ShapeType::Circle)
        {
            objectTest->w = objectTest->r;
            objectTest->h = objectTest->r;
        }


        if (
            /*verif pour x*/(x >= objectTest->x && x <= (objectTest->x + objectTest->w) || (x + w) >= objectTest->x && (x + w) <= (objectTest->x + objectTest->w))
            &&
            /*verif pour y*/ (y >= objectTest->y && y <= (objectTest->y + objectTest->h) || (y + h) >= objectTest->y && (y + h) <= (objectTest->y + objectTest->h))
            ||
            /*verif pour x*/(objectTest->x >= x && objectTest->x <= (x + w) || objectTest->x + objectTest->w >= x && objectTest->x + objectTest->w <= (x + w))
            &&
            /*verif pour y*/ (objectTest->y >= y && objectTest->y <= (y + h) || objectTest->y + objectTest->h >= y && objectTest->y + objectTest->h <= (y + h))
            )
        {
            return true;
        }
    }
    return false;
}

CollideSide gameObject::getCollideSide(gameObject* objectTest) {
    if (!isActive || !objectTest->isActive) {
        return CollideSide::None;
    }

    float thisW = (getShapeType() == ShapeType::Circle) ? r : w;
    float thisH = (getShapeType() == ShapeType::Circle) ? r : h;

    float objTestW = (objectTest->getShapeType() == ShapeType::Circle) ? objectTest->r : objectTest->w;
    float objTestH = (objectTest->getShapeType() == ShapeType::Circle) ? objectTest->r : objectTest->h;

    // Stocker les r�sultats dans la structure
    distanceResult results[] = {
        distanceResult("rtol", x + thisW - objectTest->x),
        distanceResult("ltor", objectTest->x + objTestW - x),
        distanceResult("ttob", objectTest->y + objTestH - y),
        distanceResult("btot", y + thisH - objectTest->y)
    };

    // Petite distance
    float minDistance = results[0].value;
    std::string testDistance = results[0].name;

    for (int i = 1; i < 4; i++) {
        if (results[i].value < minDistance) {
            minDistance = results[i].value;
            testDistance = results[i].name;
        }
    }

    if (testDistance == "rtol" && minDistance >= 0 && minDistance <= objTestW) {
        return CollideSide::Right;
    }
    else if (testDistance == "ltor" && minDistance >= 0 && minDistance <= thisW) {
        return CollideSide::Left;
    }
    else if (testDistance == "ttob" && minDistance >= 0 && minDistance <= objTestH) {
        return CollideSide::Top;
    }
    else if (testDistance == "btot" && minDistance >= 0 && minDistance <= thisH) {
        return CollideSide::Bottom;
    }

    return CollideSide::None;
}

bool gameObject::operator==(gameObject& other) {
    return (x == other.x && y == other.y && w == other.w && h == other.h || r == other.r);
}


void gameObject::manageCollide(gameObject* objectTest)
{
    bool bHasCollision = getCollide(objectTest);
    if (bHasCollision)
    {
        if (bAlreadyHasCollision)
        {
            OnCollisionStay(objectTest);
        }
        else
        {
            beCollide.push_back(objectTest);
            OnCollisionEnter(objectTest);
            bAlreadyHasCollision = true;
        }
    }
    else
    {
        if (bAlreadyHasCollision)
        {
            auto it = std::remove_if(beCollide.begin(), beCollide.end(),
                [objectTest](gameObject* obj) { return obj == objectTest; });

            beCollide.erase(it, beCollide.end());
            beCollide.shrink_to_fit();

            OnCollisionExit(objectTest);
            bAlreadyHasCollision = false;
            die();
        }
    }
}

void gameObject::OnCollisionEnter(gameObject* object)
{

}

void gameObject::OnCollisionStay(gameObject* object)
{

}

void gameObject::OnCollisionExit(gameObject* object)
{

}

bool gameObject::isShapeOnScreen(sf::RenderWindow& window)
{
    // Obtenez les dimensions de la fen�tre
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    // Obtenez les coordonn�es de la shape
    float shapeLeft = shape->getPosition().x;
    float shapeTop = shape->getPosition().y;
    float shapeRight = shapeLeft + shape->getGlobalBounds().width;
    float shapeBottom = shapeTop + shape->getGlobalBounds().height;

    // V�rifiez si la shape est enti�rement � l'int�rieur de l'�cran
    if (shapeLeft >= 0 && shapeTop >= 0 && shapeRight <= windowWidth && shapeBottom <= windowHeight)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// --Rotation
void gameObject::rotateTowardOrigin(float x, float y)
{
    float newX = this->w * x;
    float newY = this->h * y;
    shape->setOrigin(newX, newY);
}

void gameObject::setRotation(float angle)
{
    this->angle = angle;
    shape->setRotation(angle);
};

// --Draw
void gameObject::drawShape()
{
    if (isActive == true)
    {
        WindowManager::getInstance().getRenderWindow().draw(*shape);
        if (maxlife != 0)
        {
            drawHealthBar(WindowManager::getInstance().getRenderWindow());
        }    
    }
};

void gameObject::setDamage(int damage)
{
    this->damage = damage;
}

void gameObject::setLife(int maxlife) {
    this->maxlife = maxlife;
}

void gameObject::performAttack(gameObject* objectTest)
{   
    if (attack == true)
    {
        objectTest->life = objectTest->life + damage;
        objectTest->getHit();
        attack = false;
    }    
}

void gameObject::getHit()
{
    Color initialColor = getColor();
    setColor(sf::Color::Red);
    setColor(initialColor);
    std::cout << life;
}

void gameObject::canAttack(float elapsedTime )
{
    // Mettez à jour le chronomètre d'attaque
    
    if (attackTimer > 0.0f) {
        attackTimer -= elapsedTime;
        if (attackTimer < 0.0f) {
            attackTimer = 0.0f;
        }
    }

    // Votre logique de mise à jour habituelle pour le monstre ici
    if (attackTimer == 0.0f ) {
        attack = true;
        attackTimer = attackCooldown;
    }
    
    
}

void gameObject::drawHealthBar(RenderWindow& window)
{
    // Dessine un fond blanc représentant la barre de vie totale
    RectangleShape backgroundBar(Vector2f(w + 2, 5));
    backgroundBar.setPosition(x - 1, y - 10); // Ajustez la position en conséquence
    backgroundBar.setFillColor(Color::White);
    window.draw(backgroundBar);

    // Calcule la longueur de la barre de vie en fonction de la vie actuelle
    float healthPercentage = ((maxlife - life) * 100 ) / maxlife;
    int healthBarWidth = ((w *healthPercentage) / 100);

    // Dessine la barre de vie rouge représentant la vie actuelle
    RectangleShape healthBar(Vector2f(healthBarWidth , 5));
    healthBar.setPosition(x, y - 10); // Ajustez la position en conséquence
    healthBar.setFillColor(Color::Red);
    window.draw(healthBar);
}


void gameObject::die()
{
    if (maxlife <= life)
    {
        isActive == false;
    }
}
