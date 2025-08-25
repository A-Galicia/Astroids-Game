#include "Instructions.hpp"
#include <iostream>

Instructions::Instructions(){
	if (!font.loadFromFile("assets/arial.ttf")) {
		std::cout << "Failed to load Font" << std::endl;
	}
	else {
		text.setFont(font);
	}
}

void Instructions::Update(int level){
	text.setString("Level: " + std::to_string(level));
}

void Instructions::Draw(sf::RenderWindow &window){
	window.draw(text);
}
