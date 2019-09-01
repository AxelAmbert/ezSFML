#ifndef SINGLESTATEBUTTON
#define SINGLESTATEBUTTON
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
	class SingleStateButton : public Button
	{
	public:
		SingleStateButton();
		SingleStateButton(std::string texturePath, sf::Vector2f buttonPos);
		~SingleStateButton();
		void Create(std::string texturepath, sf::Vector2f buttonPos, sf::IntRect placeOnSpriteSheet);
	};
}
#endif
