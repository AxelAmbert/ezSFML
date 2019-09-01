#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <thread>

namespace ez
{
	typedef enum Position
	{
		LEFT, RIGHT, CENTERED, BOTTOM_LEFT, BOTTOM_RIGHT, BOTTOM_CENTERED
	}Position;
}

namespace ez
{
	typedef enum GuiState
	{
		NONE, BLOCKED, HOVERED, PRESSED, PRESSED_OUT, RELEASED
	}GuiState;
}

typedef struct uhitbox_t
{
	double minX;
	double maxX;
	double minY;
	double maxY;
}uhitbox_t;

typedef struct hitbox_t
{
	sf::Vector2u initialSize = sf::Vector2u(0, 0);
	double minX;
	double maxX;
	double minY;
	double maxY;
} hitbox_t;
#endif
