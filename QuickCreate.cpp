#include "QuickCreate.h"
sf::Text createAText(std::string text, unsigned int size,
	sf::Vector2f pos, std::string FontPlace)
{
	sf::Text newText;
	sf::Font *newFont = new sf::Font;

	newFont->loadFromFile(FontPlace);
	newText.setCharacterSize(size);
	newText.setPosition(pos);
	newText.setFont(*newFont);
	newText.setString(text);
	return (newText);
}

template <typename UnknowData>
void createAnImage(UnknowData *data,
	std::string texturePath, sf::Vector2f imageSize, sf::Vector2f imagePos)
{
	sf::Texture *tmpTex = new sf::Texture();

	tmpTex->loadFromFile(texturePath);
	if (imageSize.x == 0) {
		static_cast<sf::Sprite *>(data)->setPosition(imagePos);
		static_cast<sf::Sprite *>(data)->setTexture(*tmpTex);
	}
	else {
		static_cast<sf::RectangleShape *>(data)->setSize(imageSize);
		static_cast<sf::RectangleShape *>(data)->setPosition(imagePos);
		static_cast<sf::RectangleShape *>(data)->setTexture(tmpTex);
	}
}

void SetOpacityOnTexture(sf::Texture *texture, unsigned char opacity)
{
	sf::Image image = texture->copyToImage();
	sf::Vector2u textureSize = image.getSize();
	sf::Color tmpColor;

	for (size_t y = 0; y < textureSize.y; y++) {
		for (size_t x = 0; x < textureSize.x; x++) {
			tmpColor = image.getPixel(x, y);
			tmpColor.a = opacity;
			image.setPixel(x, y, tmpColor);
		}
	}
	texture->loadFromImage(image);
}

void FixBrokenMatrix(sf::Vector2f &brokenMatrix, sf::RenderWindow &window)
{
	sf::Vector2u actualWidowSize = window.getSize();
	float resultX;
	float resultY;

	if (actualWidowSize.x == 0 || actualWidowSize.y == 0)
		return;
	resultX = WINDOW_WIDTH / (float)actualWidowSize.x;
	resultY = WINDOW_HEIGHT / (float)actualWidowSize.y;
	brokenMatrix.x /= resultX;
	brokenMatrix.y /= resultY;
}

void ActualizeHitbox(hitbox_t &hitbox, sf::RenderWindow &window)
{
	sf::Vector2u temp = window.getSize();
	float differenceX = 0;
	float differenceY = 0;

	if (hitbox.initialSize.x != temp.x ||
		hitbox.initialSize.y != temp.y) {
		differenceX = (float)temp.x / (float)hitbox.initialSize.x;
		differenceY = (float)temp.y / (float)hitbox.initialSize.y;
		hitbox.initialSize = temp;
	}
	else {
		return;
	}
	if (differenceX > 0) {
		hitbox.minX *= differenceX;
		hitbox.maxX *= differenceX;
	}
	if (differenceY > 0) {
		hitbox.minY *= differenceY;
		hitbox.maxY *= differenceY;
	}
}

bool isMouseInHitbox(hitbox_t &hitbox, sf::RenderWindow &window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if (mousePos.x >= hitbox.minX &&
		mousePos.x <= hitbox.maxX &&
		mousePos.y >= hitbox.minY &&
		mousePos.y <= hitbox.maxY) {
		return (true);
	}
	return (false);
}
