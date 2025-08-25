#pragma once
#include <SFML/Graphics.hpp>

class Instructions {
	sf::Font font;
	sf::Text text;
public:
	Instructions();
	void Update(int level);
	void WriteText(std::string writtenText);
	void Draw(sf::Vector2f pos, sf::RenderWindow &window);
};
