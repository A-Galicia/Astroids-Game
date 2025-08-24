#include "Asteroid.hpp"
#include <iostream>

float RNG::frand(float a, float b) {
	std::uniform_real_distribution<float> d(a, b);
	return d(rng);
}

int RNG::irand(int a, int b) {
	std::uniform_int_distribution<int> d(a, b);
	return d(rng);
}

Asteroid::Asteroid (sf::Vector2f pos, sf::Vector2f v, AstSize s, float scale = 1.0f){
	vel = v;
	size = s;

	if (!texture.loadFromFile("assets/Asteroid.png")){
		std::cout << "Astroid failed to load texture" << std::endl;
		return;
	}
	sprite.setTexture(texture);
	auto bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
	sprite.setPosition(pos);
	sprite.setScale(scale, scale);
	radius = 0.5f * std::max(bounds.width, bounds.height) * sprite.getScale().x;
}

void Asteroid::Update(double deltaTime, sf::Vector2u win) {
	sprite.move(vel * (float)deltaTime);
	Wrap(win);
}

void Asteroid::Draw (sf::RenderWindow &window) {
	window.draw(sprite);
}

void Asteroid::Wrap(sf::Vector2u ws) {
	const float r = radius;
    sf::Vector2f p = sprite.getPosition();

    if (p.x < -r){
		p.x = ws.x + r;
	}
    else if (p.x > ws.x + r) {
		p.x = -r;
	}

    if (p.y < -r){
		p.y = ws.y + r;
	}
    else if (p.y > ws.y + r) {
		p.y = -r;
	}

    sprite.setPosition(p);
}
