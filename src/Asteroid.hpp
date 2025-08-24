#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>
#include <cmath>

inline float lenSqr(sf::Vector2f v){ return v.x*v.x + v.y*v.y; }

inline sf::Vector2f normalize(sf::Vector2f v){
    float l2 = lenSqr(v);
    if (l2 == 0.f) return {1.f, 0.f};
    float inv = 1.f / std::sqrt(l2);
    return {v.x * inv, v.y * inv};
}

struct RNG {
	std::mt19937 rng {std::random_device{}()};
	float frand(float a, float b);
	int irand(int a, int b);
	/* inline static float lenSqr(sf::Vector2f v);
	inline static sf::Vector2f normalize(sf::Vector2f v); */
};

enum class AstSize {Large, Medium, Small};

class Asteroid {
	sf::Texture texture;
	sf::CircleShape boundingCircle;
public:
	sf::Sprite sprite;
	sf::Vector2f vel;
	float radius{};
	AstSize size{AstSize::Large};
	Asteroid(sf::Vector2f pos, sf::Vector2f v, AstSize s, float scale);
	void Update(double deltaTime, sf::Vector2u win);
	void Draw(sf::RenderWindow &window);
	void Wrap(sf::Vector2u ws);

	
};
