#include "SingleStateButton.h"

void ez::SingleStateButton::Create(std::string texturePath, sf::Vector2f buttonPos, sf::IntRect placeOnSpritesheet)
{
	state = ez::GuiState::NONE;
	sprite.setPosition(buttonPos);
	hitbox.minX = buttonPos.x;
	hitbox.minY = buttonPos.y;
	hitbox.initialSize.x = WINDOW_WIDTH;
	hitbox.initialSize.y = WINDOW_HEIGHT;
	texture = new sf::Texture;
	blocked = new sf::Texture;
	texture->loadFromFile(texturePath, placeOnSpritesheet);
	sprite.setTexture(*texture, true);
	blocked->loadFromFile(texturePath, placeOnSpritesheet);
	hitbox.maxX = texture->getSize().x + hitbox.minX;
	hitbox.maxY = texture->getSize().y + hitbox.minY;
	//	std::thread opacity(SetOpacityOnTexture, blocked, 150);
	//opacity.detach();

}
ez::SingleStateButton::SingleStateButton(std::string texturePath, sf::Vector2f buttonPos)
{
	state = ez::GuiState::NONE;
	sprite.setPosition(buttonPos);
	hitbox.minX = buttonPos.x;
	hitbox.minY = buttonPos.y;
	hitbox.initialSize.x = WINDOW_WIDTH;
	hitbox.initialSize.y = WINDOW_HEIGHT;
	texture = new sf::Texture;
	texture->loadFromFile(texturePath);
	sprite.setTexture(*texture, true);
	hitbox.maxX = texture->getSize().x + hitbox.minX;
	hitbox.maxY = texture->getSize().y + hitbox.minY;
	//	std::thread opacity(SetOpacityOnTexture, blocked, 150);
	//opacity.detach();
}

ez::SingleStateButton::SingleStateButton()
{
}


ez::SingleStateButton::~SingleStateButton()
{
}
