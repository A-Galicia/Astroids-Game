#include <SFML/Graphics.hpp>
#include "Player.hpp"
 
int main()
{
	// initilization
	
	sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Astroids");
	window.setFramerateLimit(60);
	sf::CircleShape shape(100.0f);
	shape.setFillColor(sf::Color::Green);
	Player player;
	player.Initilize();
	player.Load();
	

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

			// Update -----------------------------------------------
			
			player.Update();

			// Update -----------------------------------------------
			
			// Draw -------------------------------------------------

			window.clear();
			//window.draw(shape);
			player.Draw(window);
			window.display();
		}
	}

	return 0;

}
