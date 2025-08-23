#include "Player.hpp"
#include <iostream>
#include <cmath>

sf::Vector2f NormalizeVector(sf::Vector2f vector) {
	float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	sf::Vector2f normalizedVec;
	normalizedVec.x = vector.x / m;
	normalizedVec.y = vector.y / m;

	return normalizedVec;
}

Bullet::Bullet()
{
	speed = 4.0f;
	bulletShape = sf::CircleShape (10.0f);
}

Bullet::~Bullet(){}

void Bullet::Initilize(const sf::Vector2f &origin, const sf::Vector2f &mousePosition){
	bulletShape.setRadius(5);
	bulletShape.setPosition(origin);
	bulletShape.setFillColor(sf::Color::Red);
	direction = NormalizeVector(mousePosition - origin);
}

void Bullet::Update(double deltaTime){
	bulletShape.setPosition(bulletShape.getPosition() + direction * (speed * (float)deltaTime));
}

void Bullet::Draw(sf::RenderWindow& window){
	window.draw(bulletShape);
}

Player::Player() {
	int health = 0;
}

void Player::Initilize() {
	boundingRect.setFillColor(sf::Color::Transparent);
	boundingRect.setOutlineColor(sf::Color::Red);
	boundingRect.setOutlineThickness(1.0);
	boundingRect.setSize(sf::Vector2f(100, 128));
}

void Player::Load() {
	if (texture.loadFromFile("assets/CartoonShip.png")) {
		sprite.setTexture(texture);
		sprite.setPosition({50, 50});
		sprite.scale(sf::Vector2f(0.2, 0.2));	 	
	}
	else {
		std::cout << "Player Failed to load" << std::endl;
	}
}

void Player::Update(sf::Vector2f &mousePosition, double deltaTime) {
	// handle movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		sprite.move({0, -1.0f * movementSpeed * (float)deltaTime});

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		sprite.move({0, 1.0f * movementSpeed * (float)deltaTime});

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		sprite.move({-1.0f * movementSpeed * (float)deltaTime, 0});

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		sprite.move({1.0f * movementSpeed * (float)deltaTime, 0});

	boundingRect.setPosition(sprite.getPosition());

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		bullets.push_back(Bullet());
		int i = bullets.size() - 1;
		bullets[i].Initilize(sprite.getPosition(), mousePosition);
	}

	for (size_t i = 0; i < bullets.size(); i++){
		bullets[i].Update(deltaTime);
	}
}

void Player::Draw(sf::RenderWindow &window) {
	window.draw(sprite);
	window.draw(boundingRect);

	for (int i = 0; i < bullets.size(); i++){
		bullets[i].Draw(window);
	}
}
