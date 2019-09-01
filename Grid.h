#ifndef GRID
#define GRID
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "structs.h"
#include "QuickCreate.h"
namespace ez {
	class Grid
	{
	public:
		Grid();
		Grid(unsigned int Collumns, unsigned int Rows);
		~Grid();
		sf::Vector2f toVector(unsigned int Columns, unsigned int Rows, sf::RenderWindow &window, sf::Vector2f margin = sf::Vector2f(0, 0));
		sf::Vector2f toVector(sf::Vector2f ColRows, sf::RenderWindow &window, ez::Position pos, sf::Vector2f size);
		float getRowSize(sf::RenderWindow &window);
		float getColumnSize(sf::RenderWindow &window);
		sf::Vector2f getCellSize(sf::RenderWindow &window, int nbCol = 1, int nbRow = 1);
		void Draw(sf::RenderWindow &window);
	private:
		unsigned int nbColumns;
		unsigned int nbRows;
		sf::RectangleShape gridRect;
		sf::Vector2f getLeftPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size);
		sf::Vector2f getRightPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size);
		sf::Vector2f getCenteredPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size);
		sf::Vector2f getBottomLeftPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size);
		sf::Vector2f getBottomRightPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size);
		sf::Vector2f getBottomCenteredPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size);
	};
}
#endif
