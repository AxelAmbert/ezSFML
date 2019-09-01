#pragma once
#ifndef BUTTONCLASS
#define BUTTONCLASS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "GUI.h"
#include <functional>
namespace ez
{
	class Button : public GUI
	{
	public:
		Button();
		virtual ~Button() = 0;
		void Draw(sf::RenderWindow &window) override;
		void Block(void);
		void Deblock(void);
		void setPosition(int x, int y);
		void setPosition(sf::Vector2f pos);
		void setPosition(sf::Vector2i pos);
		void setPosition(sf::Vector2u pos);
	protected:
		sf::Texture *texture;
		sf::Texture *blocked;
		sf::Sprite sprite;
		sf::RectangleShape button;
		sf::IntRect spritesheet;
		int lenghtOfAPart;
		sf::Clock cooldown;
	};
}
#endif
