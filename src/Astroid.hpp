#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>
#include <cmath>

struct RNG {
	std::mt19937 rng {std::random_device{}()};
	float frand(float a, float b);
	int irand(int a, int b);
};

enum class AstSize {Large, Medium, Small};

class Astroid {
	sf::Texture texture;
	sf::CircleShape boundingCircle;
public:
	sf::Sprite sprite;
	sf::Vector2f vel;
	float radius{};
	AstSize size{AstSize::Large};
	Astroid(sf::Vector2f pos, sf::Vector2f v, AstSize s, float scale);
	void Update(double deltaTime, sf::Vector2u win);
	void Draw(sf::RenderWindow &window);
	void Wrap(sf::Vector2u ws);

	
};
