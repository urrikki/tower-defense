#include "textManager.h"
#include "windowManager.h"

#include <vector>
#include<iostream>

TextManager::TextManager()
{
    if (!font.loadFromFile("pixellettersfull.ttf")) {
        std::cout << "Erreur lors du chargement de la police." << std::endl;
    }
}

void TextManager::addText(std::string content, float x, float y, sf::Color color, int size)
{
    text.setString(content);
    text.setPosition(x, y);
    text.setFillColor(color);
    text.setCharacterSize(size);
    text.setFont(font);
    texts.push_back(text);
}

void TextManager::setContent(size_t index, std::string newContent)
{
    texts[index].setString(newContent);
}

void TextManager::drawText()
{
    for (auto& text : texts) {
        WindowManager::getInstance().getRenderWindow().draw(text);
    }
}