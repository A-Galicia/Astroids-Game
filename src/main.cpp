#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Player.hpp"

int main()
{
	// initilization
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Astroids", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	
	Player player;
	player.Initilize();
	player.Load();
	
	sf::Clock clock;

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
			player.Update(mousePosition, deltaTime);

			// Update -----------------------------------------------
			
			// Draw -------------------------------------------------

			window.clear();
			player.Draw(window);
			window.display();
		
	}

	return 0;

}
