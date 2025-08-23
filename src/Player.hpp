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
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);
};

class Player
{
private:
	sf::Texture texture;
	sf::RectangleShape boundingRect;
	int movementSpeed = 1;
	std::vector<Bullet> bullets;
	
public:
	sf::Sprite sprite;
	Player();
	void Initilize();
	void Load();
	void Update(sf::Vector2f &mousePosition, double deltaTime);
	void Draw(sf::RenderWindow &window);
};

