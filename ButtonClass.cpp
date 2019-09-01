#include "ButtonClass.h"

void ez::Button::setPosition(sf::Vector2u pos)
{
	this->setGUIPosition((int)pos.x, (int)pos.y);
	sprite.setPosition(sf::Vector2f((float)pos.x, (float)pos.y));
}

void ez::Button::setPosition(sf::Vector2i pos)
{
	this->setGUIPosition(pos.x, pos.y);
	sprite.setPosition(sf::Vector2f((float)pos.x, (float)pos.y));
}

void ez::Button::setPosition(sf::Vector2f pos)
{
	this->setGUIPosition((int)pos.x, (int)pos.y);
	sprite.setPosition(pos);
}

void ez::Button::setPosition(int x, int y)
{
	this->setGUIPosition(x, y);
	sprite.setPosition(sf::Vector2f(x, y));
}

void ez::Button::Deblock(void)
{
	state = ez::GuiState::NONE;
	sprite.setTexture(*texture);
}

void ez::Button::Block(void)
{
	state = ez::GuiState::BLOCKED;
	sprite.setTexture(*blocked);
}

ez::Button::Button()
{
}

ez::Button::~Button()
{
}

void ez::Button::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}
