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
	speed = 1.0f;
	//bulletShape = sf::CircleShape (10.0f);
	timeToLive = 2000; // miliseconds -> 2 seconds
}

void Bullet::Initilize(const sf::Vector2f &origin, const sf::Vector2f &mousePosition){
	bulletShape.setRadius(5);
	bulletShape.setPosition(origin);
	bulletShape.setFillColor(sf::Color::Red);
	direction = NormalizeVector(mousePosition - origin);
}

void Bullet::Update(double deltaTime){
	bulletShape.setPosition(bulletShape.getPosition() + direction * (speed * (float)deltaTime));
	timeToLive -= deltaTime;
}

void Bullet::Draw(sf::RenderWindow& window){
	window.draw(bulletShape);
}

Player::Player() {
	health = 5;
	movementSpeed = .1;
	maxFireRate = 500;
	fireRateTimer = 0;
}

void Player::Initilize() {
	/*
	boundingRect.setFillColor(sf::Color::Transparent);
	boundingRect.setOutlineColor(sf::Color::Red);
	boundingRect.setOutlineThickness(1.0);
	boundingRect.setSize(sf::Vector2f(95, 120));
	*/
	boundingCircle.setFillColor(sf::Color::Transparent);
	boundingCircle.setOutlineColor(sf::Color::Red);
	boundingCircle.setOutlineThickness(1.0);
	boundingCircle.setRadius(45);
	boundingCircle.setOrigin(45, 45);
}

void Player::Load() {
	if (texture.loadFromFile("assets/CartoonShip.png")) {
		sprite.setTexture(texture);
		sprite.setPosition({50, 50});
		sprite.scale(sf::Vector2f(0.2, 0.2));	 	
		sprite.setOrigin(245, 250);
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

	//boundingRect.setPosition(sprite.getPosition());
	boundingCircle.setPosition(sprite.getPosition());
	fireRateTimer += deltaTime;
	//std::cout << fireRateTimer << std::endl;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && fireRateTimer >= maxFireRate) {
		/*bullets.push_back(Bullet());
		int i = bullets.size() - 1;
		bullets[i].Initilize(sprite.getPosition(), mousePosition);

		fireRateTimer = 0;*/
		bullets.emplace_back();
		bullets.back().Initilize(sprite.getPosition(), mousePosition);
		fireRateTimer = 0;
	}

	for (size_t i = 0; i < bullets.size(); i++){
		bullets[i].Update(deltaTime);
	}
}

void Player::Draw(sf::RenderWindow &window) {
	window.draw(sprite);
	//window.draw(boundingRect);
	window.draw(boundingCircle);

	while (!bullets.empty() && bullets.front().timeToLive <= 0.f){
		bullets.pop_front();
	}	

	for (int i = 0; i < bullets.size(); i++){
		bullets[i].Draw(window);
	}
}
