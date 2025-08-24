#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Player.hpp"
#include "AsteroidsSystem.hpp"

void handleBulletAsteroidHits(std::deque<Bullet>& bullets, AsteroidsSystem& sys, float bulletRadius) {
	for (int i = bullets.size() - 1; i >= 0; i--) {
		const sf::Vector2f bp = bullets[i].bulletShape.getPosition();
		bool hit = false;

		for (int j = sys.asts.size() - 1; j >= 0; j--) {
			const sf::Vector2f ap = sys.asts[j].sprite.getPosition();
			float rr = (bulletRadius + sys.asts[j].radius);

			if(lenSqr(ap - bp) <= rr * rr) {
				hit == true;
				sys.Split((size_t)j);
				break;
			}
		}

		if (hit) {
			bullets.erase(bullets.begin() + i);
		}

	}
}

int main()
{
	//adds asteroids per level clear;
	int level = 1;

	// initilization
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Astroids", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	AsteroidsSystem asts;
	Player player;
	player.Initilize();
	player.Load();
	
	sf::Clock clock;

	asts.SpawnWave(level, window.getSize(), player.sprite.getPosition(), 200.f);
	float bulletRadius = 3.0f;

	// Main Game Loop ---------------------------------------------

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		

			// Update -----------------------------------------------

			sf::Time elapsed = clock.restart();
			double deltaTime = elapsed.asMilliseconds();
			// std::cout << (1000 / deltaTime) << std::endl;
			
			sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
			player.Update(mousePosition, deltaTime, window);

			for (auto& a : asts.asts) {
				a.Update(deltaTime, window.getSize());
			}

			// level cleared, add 1 asteroid to next level
			if (asts.asts.empty()) {
				asts.SpawnWave(level + 1, window.getSize(), player.sprite.getPosition(), 200.f);
			}

			handleBulletAsteroidHits(player.bullets, asts, bulletRadius);

			// Update -----------------------------------------------
			
			// Draw -------------------------------------------------

			window.clear();
			player.Draw(window);
			for (auto& a : asts.asts) {
				a.Draw(window);
			}
			window.display();
		
	}

	return 0;
}
