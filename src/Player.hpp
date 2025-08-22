#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
	sf::CircleShape bulletShape;
	sf::Vector2f direction;
	float speed;

public:
	Bullet();
	~Bullet();
	void Initilize(const sf::Vector2f &origin, const sf::Vector2f &mousePosition);
	void Update();
	void Draw(sf::RenderWindow& window);
};

class Player
{
private:
	sf::Texture texture;
	sf::RectangleShape boundingRect;
	int movementSpeed = 10;
	std::vector<Bullet> bullets;
	
public:
	sf::Sprite sprite;
	Player();
	void Initilize();
	void Load();
	void Update(sf::Vector2f &mousePosition);
	void Draw(sf::RenderWindow &window);
};

