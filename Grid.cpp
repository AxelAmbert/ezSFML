#include "Grid.h"

sf::Vector2f ez::Grid::getCellSize(sf::RenderWindow &window, int nbCol, int nbRow)
{
	sf::Vector2u windowSize = window.getSize();

	return (sf::Vector2f((float)(windowSize.x / nbColumns) * nbCol, (float)(windowSize.y / nbRows) * nbRow));
}

float ez::Grid::getColumnSize(sf::RenderWindow &window)
{
	return (window.getSize().x / nbColumns);
}

float ez::Grid::getRowSize(sf::RenderWindow &window)
{
	return (window.getSize().y / nbRows);
}

void ez::Grid::Draw(sf::RenderWindow &window)
{
	sf::Vector2u windowSize = window.getSize();

	gridRect.setSize(sf::Vector2f(5, windowSize.y));
	for (unsigned int Columns = 1; Columns < nbColumns; Columns++) {
		gridRect.setPosition(this->toVector(Columns, 0, window));
		window.draw(gridRect);
	}
	gridRect.setSize(sf::Vector2f(5, windowSize.x));
	gridRect.rotate(-90);
	for (unsigned int Rows = 1; Rows < nbRows; Rows++) {
		gridRect.setPosition(this->toVector(0, Rows, window));
		window.draw(gridRect);
	}
	gridRect.rotate(90);
}

sf::Vector2f ez::Grid::getLeftPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size)
{
	(void)size;
	sf::Vector2u windowSize = window.getSize();
	float posX = (float)(((float)windowSize.x / (float)nbColumns) * ColRows.x);
	float posY = (float)(((float)windowSize.y / (float)nbRows) * ColRows.y);

	return (sf::Vector2f(posX, posY));
}

sf::Vector2f ez::Grid::getRightPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size)
{
	sf::Vector2u windowSize = window.getSize();
	sf::Vector2f CellSize = this->getCellSize(window);
	float posX = (float)(((float)windowSize.x / (float)nbColumns) * ColRows.x);
	float posY = (float)(((float)windowSize.y / (float)nbRows) * ColRows.y);

	if (size.x >= CellSize.x)
		return (sf::Vector2f(posX, posY));
	return (sf::Vector2f(posX + (CellSize.x - size.x), posY));
}

sf::Vector2f ez::Grid::getCenteredPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size)
{
	sf::Vector2u windowSize = window.getSize();
	sf::Vector2f CellSize = this->getCellSize(window);
	float posX = (float)(((float)windowSize.x / (float)nbColumns) * ColRows.x);
	float posY = (float)(((float)windowSize.y / (float)nbRows) * ColRows.y);

	if (size.x >= CellSize.x)
		return (sf::Vector2f(posX, posY));
	return (sf::Vector2f(posX + ((CellSize.x - size.x) / 2), posY + ((CellSize.y - size.y) / 2)));
}

sf::Vector2f ez::Grid::getBottomLeftPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size)
{
	sf::Vector2u windowSize = window.getSize();
	sf::Vector2f CellSize = this->getCellSize(window);
	float posX = (float)(((float)windowSize.x / (float)nbColumns) * ColRows.x);
	float posY = (float)(((float)windowSize.y / (float)nbRows) * ColRows.y);

	if (size.y >= CellSize.y)
		return (sf::Vector2f(posX, posY));
	return (sf::Vector2f(posX, posY + (CellSize.y - size.y)));
}

sf::Vector2f ez::Grid::getBottomRightPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size)
{
	sf::Vector2u windowSize = window.getSize();
	sf::Vector2f CellSize = this->getCellSize(window);
	float posX = (float)(((float)windowSize.x / (float)nbColumns) * ColRows.x);
	float posY = (float)(((float)windowSize.y / (float)nbRows) * ColRows.y);

	if (size.y >= CellSize.y && size.x >= CellSize.x)
		return (sf::Vector2f(posX, posY));
	if (CellSize.x > size.x)
		posX += (CellSize.x - size.x);
	if (CellSize.y > size.y)
		posY += (CellSize.y - size.y);
	return (sf::Vector2f(posX, posY));
}

sf::Vector2f ez::Grid::getBottomCenteredPosition(sf::Vector2f ColRows, sf::RenderWindow &window, sf::Vector2f size)
{
	sf::Vector2u windowSize = window.getSize();
	sf::Vector2f CellSize = this->getCellSize(window);
	float posX = (float)(((float)windowSize.x / (float)nbColumns) * ColRows.x);
	float posY = (float)(((float)windowSize.y / (float)nbRows) * ColRows.y);

	if (size.y >= CellSize.y && size.x >= CellSize.x)
		return (sf::Vector2f(posX, posY));
	if (CellSize.x > size.x)
		posX += ((CellSize.x - size.x) / 2);
	if (CellSize.y > size.y)
		posY += (CellSize.y - size.y);
	return (sf::Vector2f(posX, posY));
}

sf::Vector2f ez::Grid::toVector(sf::Vector2f ColRows, sf::RenderWindow &window, ez::Position pos, sf::Vector2f size)
{
	switch (pos)
	{
	case ez::Position::LEFT:
		return (this->getLeftPosition(ColRows, window, size));
	case ez::Position::RIGHT:
		return (this->getRightPosition(ColRows, window, size));
	case ez::Position::CENTERED:
		return (this->getCenteredPosition(ColRows, window, size));
	case ez::Position::BOTTOM_LEFT:
		return (this->getBottomLeftPosition(ColRows, window, size));
	case ez::Position::BOTTOM_RIGHT:
		return (this->getBottomRightPosition(ColRows, window, size));
	case ez::Position::BOTTOM_CENTERED:
		return (this->getBottomCenteredPosition(ColRows, window, size));
	}
	return (this->getBottomCenteredPosition(ColRows, window, size));
}

sf::Vector2f ez::Grid::toVector(unsigned int Columns, unsigned int Rows, sf::RenderWindow &window, sf::Vector2f margin)
{
	sf::Vector2u windowSize = window.getSize();
	float posX = (float)(((float)windowSize.x / (float)nbColumns) * Columns);
	float posY = (float)(((float)windowSize.y / (float)nbRows) * Rows);

	return (sf::Vector2f(posX + margin.x, posY + margin.y));
}

ez::Grid::Grid(unsigned int Columns, unsigned int Rows)
{
	nbColumns = Columns;
	nbRows = Rows;
	gridRect.setFillColor(sf::Color::White);
}

ez::Grid::Grid()
{
}

ez::Grid::~Grid()
{
}
