//
// Created by axel on 5/3/19.
//

#include "Checkbox.hpp"

ez::Checkbox::Checkbox(std::string texturePath, sf::Vector2f buttonSize, sf::Vector2f buttonPos, sf::Vector2f buttonPlaceOnSpritesheet)
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
    spritesheet.width = spritesheet.width * 6;
    texture->loadFromFile(texturePath, spritesheet);
    spritesheet.width /= 6;
    blocked->loadFromFile(texturePath, spritesheet);
    //	std::thread opacity(SetOpacityOnTexture, blocked, 150);
    //	opacity.detach();
    sprite.setTexture(*texture, true);
    sprite.setTextureRect(spritesheet);
    checked = false;
}

void ez::Checkbox::GUIEffectChecked()
{
    int difference = lenghtOfAPart * 3;

    if (state == ez::PRESSED) {
        if (spritesheet.left != lenghtOfAPart * 2 + difference) {
            spritesheet.left = lenghtOfAPart * 2 + difference;
            sprite.setTextureRect(spritesheet);
        }
    } else if (state == ez::HOVERED) {
        if (spritesheet.left != lenghtOfAPart + difference) {
            spritesheet.left = lenghtOfAPart + difference;
            sprite.setTextureRect(spritesheet);
        }
    } else {
        if (spritesheet.left != 0 + difference) {
            spritesheet.left = 0 + difference;
            sprite.setTextureRect(spritesheet);
        }
    }
}

void ez::Checkbox::GUIEffectUnchecked()
{
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
}

bool ez::Checkbox::getChecked()
{
    return checked;
}

void ez::Checkbox::GUIEffect(sf::Event &event, sf::RenderWindow &window)
{
    (void)event;
    (void)window;
    if (state == ez::GuiState::RELEASED)
        checked = checked == true ? false : true;
    if (checked == true)
        this->GUIEffectChecked();
    else
        this->GUIEffectUnchecked();
    this->execEventList();
}