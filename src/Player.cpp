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
	//direction = NormalizeVector(mousePosition - origin);
	direction = mousePosition;
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
	rotSpeed = 0.3f;
	thrust = 0.007f;
	damping = 0.005f;
}

void Player::Initilize() {
	boundingCircle.setFillColor(sf::Color::Transparent);
	boundingCircle.setOutlineColor(sf::Color::Red);
	boundingCircle.setOutlineThickness(1.0);
	boundingCircle.setRadius(45);
	boundingCircle.setOrigin(45, 45);
}

void Player::Load() {
	if (texture.loadFromFile("assets/CartoonShip.png")) {
		sprite.setTexture(texture);
		sprite.setPosition({960, 540});
		sprite.scale(sf::Vector2f(0.2, 0.2));	 	
		sprite.setOrigin(245, 250);
		velocity = {0.f, 0.f};
	}
	else {
		std::cout << "Player Failed to load" << std::endl;
	}
}

void Player::Update(sf::Vector2f &mousePosition, double deltaTime) {
	// handle movement
	
	float ang = (sprite.getRotation() - 90.f) * (3.1415f / 180.0f);
	sf::Vector2f forward(std::cos(ang), std::sin(ang));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		sprite.rotate(-rotSpeed * (float)deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		sprite.rotate(rotSpeed * (float)deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		velocity += forward * (thrust * (float)deltaTime);
	}
	
	velocity -= velocity * (damping * (float)deltaTime);
	sprite.move(velocity * (float)deltaTime);

	sf::Vector2f pos = sprite.getPosition();

	boundingCircle.setPosition(pos.x, pos.y);
	fireRateTimer += deltaTime;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fireRateTimer >= maxFireRate) {
		
		bullets.emplace_back();
		bullets.back().Initilize(sprite.getPosition(), forward);
		//bullets.back().Initilize(forward);
		fireRateTimer = 0;
	}

	for (size_t i = 0; i < bullets.size(); i++){
		bullets[i].Update(deltaTime);
	}
}

void Player::Draw(sf::RenderWindow &window) {
	window.draw(sprite);
	window.draw(boundingCircle);

	while (!bullets.empty() && bullets.front().timeToLive <= 0.f){
		bullets.pop_front();
	}	

	for (int i = 0; i < bullets.size(); i++){
		bullets[i].Draw(window);
	}
}
