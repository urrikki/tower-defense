#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class TextManager
{
public:
	std::vector<sf::Text> texts;

	TextManager();

	void addText(std::string content, float x, float y, sf::Color color, int size);
	void setContent(size_t index, std::string newContent);
	void draw(sf::RenderWindow& window);


private:
	sf::Font font;
	sf::Text text;
};
