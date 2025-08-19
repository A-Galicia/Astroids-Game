#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	sf::Texture texture;
	sf::RectangleShape boundingRect;
	int movementSpeed = 5;
	
public:
	sf::Sprite sprite;
	Player();
	void Initilize();
	void Load();
	void Update();
	void Draw(sf::RenderWindow &window);
};


