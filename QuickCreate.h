#ifndef QUICK
#define QUICK
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "structs.h"

const unsigned int WINDOW_HEIGHT = 1080;
const unsigned int WINDOW_WIDTH = 1920;

sf::Text createAText(std::string text = "No Text", unsigned int size = 10,
	sf::Vector2f pos = sf::Vector2f(0, 0), std::string FontPlace = "Resources/BEBAS.ttf");
void createAnImage(void *data,
	std::string texturePath, sf::Vector2f imageSize, sf::Vector2f imagePos);
bool isMouseInHitbox(hitbox_t &hitbox, sf::RenderWindow &window);
void ActualizeHitbox(hitbox_t *&hitbox, sf::RenderWindow &window);
void FixBrokenMatrix(sf::Vector2f &brokenMatrix, sf::RenderWindow &window);
void SetOpacityOnTexture(sf::Texture *texture, unsigned char opacity);
#endif
