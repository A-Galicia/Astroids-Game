#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

class Bullet {
	sf::CircleShape bulletShape;
	sf::Vector2f direction;
	float speed;

public:
	float timeToLive;
	Bullet();
	void Initilize(const sf::Vector2f &origin, const sf::Vector2f &mousePosition);
	void Update(double deltaTime);
	void Draw(sf::RenderWindow& window);
};

class Player
{
private:
	sf::Texture texture;
	sf::RectangleShape boundingRect;
	float movementSpeed;
	int health;
	std::deque<Bullet> bullets;
	float maxFireRate;
	double fireRateTimer;
	
public:
	sf::Sprite sprite;
	Player();
	void Initilize();
	void Load();
	void Update(sf::Vector2f &mousePosition, double deltaTime);
	void Draw(sf::RenderWindow &window);
};

