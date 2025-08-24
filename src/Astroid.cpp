#include "Astroid.hpp"
#include <iostream>

inline float lenSqr(sf::Vector2f v) { return v.x * v.x + v.y * v.y;}

inline sf::Vector2f normalize(sf::Vector2f v) {
	float lSqr = lenSqr(v);
	if (lSqr == 0.f) {
		return {1.f, 0.f};
	}

	float inv = 1.f / std::sqrt(lSqr);
	return {v.x * inv, v.y * inv};
}

float RNG::frand(float a, float b) {
	std::uniform_real_distribution<float> d(a, b);
	return d(rng);
}

int RNG::irand(int a, int b) {
	std::uniform_int_distribution<int> d(a, b);
	return d(rng);
}

Astroid::Astroid (sf::Vector2f pos, sf::Vector2f v, AstSize s, float scale = 1.0f){
	if (!texture.loadFromFile("assets/Astroid.png")){
		std::cout << "Astroid failed to load texture" << std::endl;
		return;
	}
	sprite.setTexture(texture);
	auto bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
	sprite.setPosition(pos);
	sprite.setScale(scale, scale);
	radius = 0.5f * bounds.height * scale;
}

void Astroid::Update(double deltaTime, sf::Vector2u win) {
	sprite.move(vel * (float)deltaTime);
	Wrap(win);
}

void Astroid::Draw (sf::RenderWindow &window) {
	window.draw(sprite);
}

void Astroid::Wrap(sf::Vector2u ws) {
	sf::Vector2f p = sprite.getPosition();
	if (p.x < -radius) p.x = ws.x + radius;
	if (p.x > ws.x + radius) p.x = -radius;
	if (p.y < -radius) p.y = ws.y + radius;
	if (p.y > ws.y + radius) p.y = -radius;
	sprite.setPosition(p);
}
