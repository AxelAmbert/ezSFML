#ifndef CLASSICBUTTON
#define CLASSICBUTTON
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "ButtonClass.h"
namespace ez
{
	class ClassicButton : public Button
	{
	public:
		ClassicButton();
		ClassicButton(std::string texturePath, sf::Vector2f buttonSize, sf::Vector2f buttonPos, sf::Vector2f buttonPlaceOnSpritesheet);
		~ClassicButton();
		void GUIEffect(sf::Event &event, sf::RenderWindow &window) override;
		void Create(std::string texturePath, sf::Vector2f buttonSize, sf::Vector2f buttonPos, sf::Vector2f buttonPlaceOnSpritesheet);
	};
}
#endif
