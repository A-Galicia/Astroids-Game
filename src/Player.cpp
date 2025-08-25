#include "Player.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

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
	timeToLive = 2000; // miliseconds -> 2 seconds
}

void Bullet::Initilize(const sf::Vector2f &origin, const sf::Vector2f &mousePosition){
	bulletShape.setRadius(3);
	bulletShape.setPosition(origin);
	bulletShape.setFillColor(sf::Color::White);
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
	maxFireRate = 200;
	fireRateTimer = 0;
	rotSpeed = 0.3f;
	thrust = 0.003f;
	damping = 0.001f;
	maxSpeed = 0.5f;
	radius = 22;
}

void Player::Initilize() {
	boundingCircle.setFillColor(sf::Color::Transparent);
	boundingCircle.setOutlineColor(sf::Color::Red);
	boundingCircle.setOutlineThickness(1.0);
	boundingCircle.setRadius(radius);
	boundingCircle.setOrigin(22, 22);
}

void Player::Load() {
	if (texture.loadFromFile("assets/CartoonShip.png")) {
		sprite.setTexture(texture);
		sprite.setPosition({960, 540});
		sprite.scale(sf::Vector2f(0.1, 0.1));	 	
		auto spriteBounds = sprite.getLocalBounds();
		sprite.setOrigin(spriteBounds.width * 0.5f, spriteBounds.height * 0.5f);
		velocity = {0.f, 0.f};
	}
	else {
		std::cout << "Player Failed to load" << std::endl;
	}
}
void Player::KeepInsideWindow(const sf::RenderWindow &window){
	const float r = boundingCircle.getRadius();
	sf::Vector2f pos = sprite.getPosition();
	const sf::Vector2u ws = window.getSize();

	const float minX = r;
	const float maxX = static_cast<float>(ws.x) - r;
	const float minY = r;
	const float maxY = static_cast<float>(ws.y) - r;

	const float clampedX = std::clamp(pos.x, minX, maxX);
	const float clampedY = std::clamp(pos.y, minY, maxY);

	if (clampedX != pos.x) velocity.x = 0.f;
	if (clampedY != pos.y) velocity.y = 0.f;

	sprite.setPosition(clampedX, clampedY);
}

void Player::Update(sf::Vector2f &mousePosition, double deltaTime, sf::RenderWindow &window) {
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
	const float speedSqr = velocity.x * velocity.x + velocity.y * velocity.y;
	const float maxSqr = maxSpeed * maxSpeed;

	if (speedSqr > maxSqr) {
		const float invSpeed = 1.0f / std::sqrt(speedSqr);
		velocity *= maxSpeed * invSpeed;
	}

	sprite.move(velocity * (float)deltaTime);
	KeepInsideWindow(window);

	boundingCircle.setPosition(sprite.getPosition());
	fireRateTimer += deltaTime;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fireRateTimer >= maxFireRate) {
		
		bullets.emplace_back();
		bullets.back().Initilize(sprite.getPosition(), forward);
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
