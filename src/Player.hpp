#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

struct Bullet {
	sf::CircleShape bulletShape;
	sf::Vector2f direction;
	float speed;
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
	sf::CircleShape boundingCircle;
	float movementSpeed;
	int health;
	float maxFireRate;
	double fireRateTimer;
	sf::Vector2f velocity;
	float rotSpeed;
	float thrust;
	float damping;
	float maxSpeed;
	
public:
	std::deque<Bullet> bullets;
	sf::Sprite sprite;
	Player();
	void Initilize();
	void Load();
	void Update(sf::Vector2f &mousePosition, double deltaTime, sf::RenderWindow &window);
	void KeepInsideWindow(const sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
};

