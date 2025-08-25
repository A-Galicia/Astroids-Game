#pragma once
#include <SFML/Graphics.hpp>

class Instructions {
	sf::Font font;
	sf::Text text;
public:
	Instructions();
	void Update(int level);
	void Draw(sf::RenderWindow &window);
};
