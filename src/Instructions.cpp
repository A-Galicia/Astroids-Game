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

void Instructions::WriteText(std::string writtenText) {
	text.setString(writtenText);
}

void Instructions::Draw(sf::Vector2f pos, sf::RenderWindow &window){
	text.setPosition(pos);
	window.draw(text);
}

