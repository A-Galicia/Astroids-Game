
#include "AsteroidsSystem.hpp"
#include <iostream>
#include <algorithm>

AsteroidsSystem::AsteroidsSystem(){
}

bool AsteroidsSystem::loadTexture(const std::string &path) {
	return asteroidTex.loadFromFile(path);
}

void AsteroidsSystem::SpawnWave(int count, sf::Vector2u ws, sf::Vector2f avoidPos = {-1.f, -1.f}, float avoidRadius = 150.f) {
	for (int i = 0; i < count; i++) {
		int edge = rng.irand(0, 3); // 0 = left, 1 = right, 2 = top, 3 = bottom
		sf::Vector2f pos;
		switch (edge) {
			case 0: pos = {-40.f, rng.frand(0.f, (float)ws.y)};
				break;
			case 1: pos = {(float)ws.x + 40.f, rng.frand(0.f, (float)ws.y)};
				break;
			case 2: pos = {rng.frand(0.f, (float)ws.x), -40.f};
				break;
			default: pos = {rng.frand(0.f, (float)ws.x), (float)ws.y + 40.f};
				 break;
		}

		// keep away from player spawn
		if (avoidPos.x >= 0.f) {
			sf::Vector2f d = pos - avoidPos;
			if (lenSqr(d) < avoidRadius * avoidRadius) {
				i--; //try again
				continue;
			}
		}

		//random direction & speed
		sf::Vector2f dir = normalize({rng.frand(-1.f, 1.f), rng.frand(-1.f, 1.f)});
		float speed = rng.frand(0.001f, 0.6f);
		asts.emplace_back(asteroidTex ,pos, dir * speed, AstSize::Large, 1.0f);
	}
}

void AsteroidsSystem::Split(size_t idx) {
	Asteroid a = asts[idx];
	asts.erase(asts.begin() + (long)idx);

	if (a.size == AstSize::Small) return;

	AstSize childSize = (a.size == AstSize::Large) ? AstSize::Medium : AstSize::Small;
	float childScale = (a.size == AstSize::Large) ? 0.6f: 0.4f;
	float baseSpeed = std::max(1.f, std::sqrt(lenSqr(a.vel)) * 1.2f);

	for (int i = 0; i < 2; i++) {
		float ang = rng.frand(0.f, 10.f);
		sf::Vector2f dir (std::cos(ang), std::sin(ang));
		float speed = std::min(1.f, baseSpeed * rng.frand(0.01f, 1.1f));
		asts.emplace_back(asteroidTex ,a.sprite.getPosition(), dir * speed, childSize, childScale);
	}
}
