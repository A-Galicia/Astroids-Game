#include "Player.hpp"
#include <iostream>

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

void Player::Update() {
	// handle movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		sprite.move({0, -1.0f * movementSpeed});

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		sprite.move({0, 1.0f * movementSpeed});

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		sprite.move({-1.0f * movementSpeed, 0});

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		sprite.move({1.0f * movementSpeed, 0});

	boundingRect.setPosition(sprite.getPosition());
}

void Player::Draw(sf::RenderWindow &window) {
	window.draw(sprite);
	window.draw(boundingRect);
}
