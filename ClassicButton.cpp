#include "ClassicButton.h"

void ez::ClassicButton::GUIEffect([[maybe_unused]] sf::Event &event, [[maybe_unused]] sf::RenderWindow &window)
{
	//(void)event;
	//(void)window;
	if (state == ez::PRESSED) {
		if (spritesheet.left != lenghtOfAPart * 2) {
			spritesheet.left = lenghtOfAPart * 2;
			sprite.setTextureRect(spritesheet);
		}
	} else if (state == ez::HOVERED) {
		if (spritesheet.left != lenghtOfAPart) {
			spritesheet.left = lenghtOfAPart;
			sprite.setTextureRect(spritesheet);
		}
	} else {
		if (spritesheet.left != 0) {
			spritesheet.left = 0;
			sprite.setTextureRect(spritesheet);
		}
	}
	this->execEventList();
}

ez::ClassicButton::ClassicButton(std::string texturePath,
		sf::Vector2f buttonSize, sf::Vector2f buttonPos,
		sf::Vector2f buttonPlaceOnSpritesheet) : ClassicButton()
{
	this->Create(texturePath, buttonSize, buttonPos, buttonPlaceOnSpritesheet);
}



void ez::ClassicButton::Create(std::string texturePath, sf::Vector2f buttonSize, sf::Vector2f buttonPos, sf::Vector2f buttonPlaceOnSpritesheet)
{
spritesheet = { (int)buttonPlaceOnSpritesheet.x,
	(int)buttonPlaceOnSpritesheet.y, (int)buttonSize.x, (int)buttonSize.y };
	lenghtOfAPart = (int)buttonSize.x;
	state = ez::GuiState::NONE;
	sprite.setPosition(buttonPos);
	hitbox.minX = (int)buttonPos.x;
	hitbox.minY = (int)buttonPos.y;
	hitbox.maxX = lenghtOfAPart + (int)hitbox.minX;
	hitbox.maxY = spritesheet.height + (int)hitbox.minY;
	hitbox.initialSize.x = WINDOW_WIDTH;
	hitbox.initialSize.y = WINDOW_HEIGHT;
	texture = new sf::Texture;
	blocked = new sf::Texture;
	spritesheet.width = spritesheet.width * 3;
	texture->loadFromFile(texturePath, spritesheet);
	spritesheet.width /= 3;
	blocked->loadFromFile(texturePath, spritesheet);
	//	std::thread opacity(SetOpacityOnTexture, blocked, 150);
	//	opacity.detach();
	sprite.setTexture(*texture, true);
	sprite.setTextureRect(spritesheet);
}

ez::ClassicButton::ClassicButton()
{
}


ez::ClassicButton::~ClassicButton()
{
}
