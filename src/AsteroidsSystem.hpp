#pragma once
#include "Asteroid.hpp"
#include <vector>

struct AsteroidsSystem {
	std::vector<Asteroid> asts;
	sf::Texture asteroidTex;
	RNG rng;

	AsteroidsSystem();
	bool loadTexture(const std::string &path);
	void SpawnWave(int count, sf::Vector2u ws, sf::Vector2f avoidPos, float avoidRadius);
	void Split(size_t idx);
};
