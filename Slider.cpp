#include "Slider.h"

void ez::Slider::Create(ez::SliderCreation properties)
{
	button.Create(properties.path, sf::Vector2f(0, 0), properties.buttonPlaceOnSpritesheet);
	sliderTexture.loadFromFile(properties.path, properties.sliderPlaceOnSpritesheet);
	slider.setSize(sf::Vector2f((float)sliderTexture.getSize().x,
			(float)sliderTexture.getSize().y));
	slider.setTexture(&sliderTexture);
	slider.setPosition(properties.sliderPos);
	limits = properties.limits;
	this->setValue(0);
	size.x = slider.getSize().x > button.getSize().x / 2 ? slider.getSize().x : button.getSize().x;
	size.y = slider.getSize().y > button.getSize().y / 2 ? slider.getSize().y : button.getSize().y;
	hitbox = button.getHitbox();
}

float GetPercentageFromValue(float min, float max, float value)
{
	max -= min;
	return (value * max / 100);
}

void ez::Slider::setValue(float value)
{
	sf::Vector2f size = slider.getSize();
	sf::Vector2f pos = slider.getPosition();

	if (size.x > size.y) {
		button.setPosition(
			sf::Vector2f(
				pos.x +
				GetPercentageFromValue(pos.x, pos.x + size.x, value) -
				button.getSize().x / 2,
				pos.y +
				size.y / 2 -
				button.getSize().y / 2
			));
	} else {
		button.setPosition(
			sf::Vector2f(
				pos.x + size.x / 2 -
				button.getSize().x / 2,
				pos.y +
				GetPercentageFromValue(pos.y,
					pos.y + size.y, value) -
				button.getSize().y / 2
			));
	}
	this->value = value;
	hitbox = button.getHitbox();
}

void ez::Slider::setPosition(sf::Vector2f pos)
{
	slider.setPosition(pos);
	setValue(value);
	/*if (limits == ez::SliderLimit::ABSOLUTEE) {
		if (slider.getSize().x > slider.getSize().y) {

			////button.setPosition(, pos.y)
		}

	}*/
}

sf::Vector2f ez::Slider::getPosition() const
{
	return (slider.getPosition());
}

sf::Vector2f ez::Slider::getSize() const 
{
	return (size);
}

void ez::Slider::Deblock()
{
	button.Deblock();
	state = ez::GuiState::NONE;
}

void ez::Slider::Block()
{
	button.Block();
	state = ez::GuiState::BLOCKED;
}

float ez::Slider::GetPercentageValue(float min, float max, float value)
{
	float toReturn = (value - min) * 100 / (max - min);

	if (toReturn < 0) {
		if (valueMargin < toReturn * -1)
			valueMargin = toReturn * -1;
	}
	else if (toReturn > 100) {
		if (valueMargin > toReturn - 100)
			valueMargin = (toReturn - 100) * -1;
	}
	return (toReturn + valueMargin);
}

float ez::Slider::getValue() const
{
	return (value);
}

void ez::Slider::VerifyHorizontalLimits(sf::Vector2f sliderPos, sf::Vector2f sliderSize, sf::Vector2f buttonPos, sf::Vector2f buttonSize)
{
	if (limits == ez::SliderLimit::ABSOLUTEE) {
		if (buttonPos.x < sliderPos.x)
			button.setPosition(sliderPos.x, buttonPos.y);
		else if (buttonPos.x + buttonSize.x > sliderPos.x + sliderSize.x)
			button.setPosition(sliderPos.x + sliderSize.x - buttonSize.x, buttonPos.y);
		buttonPos = button.getPosition();
		value = GetPercentageValue(sliderPos.x, sliderPos.x + sliderSize.x - buttonSize.x, buttonPos.x);
	} else if (limits == ez::SliderLimit::RELATIVEE) {
		if (buttonPos.x + buttonSize.x / 2 < sliderPos.x)
			button.setPosition(sliderPos.x - buttonSize.x / 2, buttonPos.y);
		else if (buttonPos.x + buttonSize.x / 2 > sliderPos.x + sliderSize.x)
			button.setPosition(sliderPos.x + sliderSize.x - buttonSize.x / 2, buttonPos.y);
		buttonPos = button.getPosition();
		value = GetPercentageValue(sliderPos.x, sliderPos.x + sliderSize.x, buttonPos.x + buttonSize.x / 2);
	}
}

void ez::Slider::MoveHorizontaly(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &sliderSize)
{
	(void)event;
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f sliderPos = slider.getPosition();
	sf::Vector2f buttonPos = button.getPosition();
	sf::Vector2f buttonSize = button.getSize();

	button.setPosition(mousePos.x - buttonSize.x / 2, (int)buttonPos.y);
	buttonPos = button.getPosition();
	this->VerifyHorizontalLimits(sliderPos, sliderSize, buttonPos, buttonSize);
	hitbox = button.getHitbox();
}

void ez::Slider::VerifyVerticalLimits(sf::Vector2f sliderPos, sf::Vector2f sliderSize, sf::Vector2f buttonPos, sf::Vector2f buttonSize)
{
	if (limits == ez::SliderLimit::ABSOLUTEE) {
		if (buttonPos.y < sliderPos.y)
			button.setPosition(buttonPos.x, sliderPos.y);
		else if (buttonPos.y + buttonSize.y > sliderPos.y + sliderSize.y)
			button.setPosition(buttonPos.x, sliderPos.y + sliderSize.y - buttonSize.y);
		buttonPos = button.getPosition();
		value = GetPercentageValue(sliderPos.y, sliderPos.y + sliderSize.y - buttonSize.y, buttonPos.y);
	}
	else if (limits == ez::SliderLimit::RELATIVEE) {
		if (buttonPos.y + buttonSize.y / 2 < sliderPos.y)
			button.setPosition(buttonPos.x, sliderPos.y - buttonSize.y / 2);
		else if (buttonPos.y + buttonSize.y / 2 > sliderPos.y + sliderSize.y)
			button.setPosition(buttonPos.x,  sliderPos.y + sliderSize.y - buttonSize.y / 2);
		buttonPos = button.getPosition();
		value = GetPercentageValue(sliderPos.y, sliderPos.y + sliderSize.y, buttonPos.y + buttonSize.y / 2);
	}
}

void ez::Slider::MoveVerticaly(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &sliderSize)
{
	(void)event;
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f sliderPos = slider.getPosition();
	sf::Vector2f buttonPos = button.getPosition();
	sf::Vector2f buttonSize = button.getSize();

	button.setPosition((int)buttonPos.x, mousePos.y - buttonSize.y / 2);
	buttonPos = button.getPosition();
	this->VerifyVerticalLimits(sliderPos, sliderSize, buttonPos, buttonSize);
	hitbox = button.getHitbox();
}

void ez::Slider::GUIEffect(sf::Event &event, sf::RenderWindow &window)
{
	sf::Vector2f sliderSize;

	if (state == ez::GuiState::PRESSED || state == ez::GuiState::PRESSED_OUT) {
		sliderSize = slider.getSize();
		if (sliderSize.x > sliderSize.y)
			MoveHorizontaly(event, window, sliderSize);
		else
			MoveVerticaly(event, window, sliderSize);
	}
}

void ez::Slider::Draw(sf::RenderWindow &window)
{
	window.draw(slider);
	button.Draw(window);
}

ez::Slider::Slider(SliderCreation properties)
{
	button.Create(properties.path, sf::Vector2f(0, 0), properties.buttonPlaceOnSpritesheet);
	sliderTexture.loadFromFile(properties.path, properties.sliderPlaceOnSpritesheet);
	slider.setSize(sf::Vector2f((float)sliderTexture.getSize().x,
			(float)sliderTexture.getSize().y));
	slider.setTexture(&sliderTexture);
	slider.setPosition(properties.sliderPos);
	limits = properties.limits;
	this->setValue(0);
	size.x = slider.getSize().x > button.getSize().x / 2 ? slider.getSize().x : button.getSize().x;
	size.y = slider.getSize().y > button.getSize().y / 2 ? slider.getSize().y : button.getSize().y;
	hitbox = button.getHitbox();
	valueMargin = 0;
}

ez::Slider::Slider()
{
	valueMargin = 0;
}


ez::Slider::~Slider()
{
	valueMargin = 0;
}
