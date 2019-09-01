#include "GUI.h"
/*
void ez::GUI::addOneElementInEventList(ez::GuiState eventKind, std::function<void(ez::GUI *)> func)
{
	std::cout << "alle" << std::endl;
	this->eventFuncs[eventKind].push_back(func);
}*/

void ez::GUI::setSize(int x, int y)
{
    (void)x;
    (void)y;
}

void ez::GUI::resetHitbox()
{
	hitbox.minX = 0;
	hitbox.minY = 0;
	hitbox.maxX = 0;
	hitbox.maxY = 0;
}

void ez::GUI::setHitbox(hitbox_t hitbox)
{
    this->hitbox = hitbox;
}

void ez::GUI::execEventList()
{
/*	std::cout << "{";
	for (int i = 0; i < 6; i++) {
		std::cout << this->eventFuncs[i].size();
	}
	std::cout << "}" << std::endl;*/
	for (auto &func : eventFuncs[state])
		func();
}

void ez::GUI::verifyIfObjectIsNotInZone()
{
	if (NoEffectZone == nullptr)
		return;
	if (hitbox.minX >= NoEffectZone->maxX ||
		hitbox.maxX <= NoEffectZone->minX ||
		hitbox.minY >= NoEffectZone->maxY ||
		hitbox.maxY <= NoEffectZone->minY) {
	}
	else if (state == ez::GuiState::BLOCKED) {
		state = ez::GuiState::NONE;
	}
}

void ez::GUI::setNoEffectZone(hitbox_t NewNoEffectZone)
{
	if (NoEffectZone != nullptr)
		delete NoEffectZone;
	NoEffectZone = new hitbox_t;
	*NoEffectZone = NewNoEffectZone;
	this->verifyIfObjectIsNotInZone();
}

void ez::GUI::moveHitbox(sf::Vector2f pos)
{
	hitbox.minX += pos.x;
	hitbox.minY += pos.y;
	hitbox.maxX += pos.x;
	hitbox.maxY += pos.y;
	//this->verifyIfObjectIsNotInZone();
}

hitbox_t ez::GUI::getHitbox(void)
{
	return (hitbox);
}

void ez::GUI::Draw(sf::RenderWindow &window)
{
	(void)window;
	return;
}

void ez::GUI::setGUIPosition(int posX, int posY)
{
	double sizeX = hitbox.maxX - hitbox.minX;
	double sizeY = hitbox.maxY - hitbox.minY;

	hitbox.minX = (double)posX;
	hitbox.minY = (double)posY;
	hitbox.maxX = posX + sizeX;
	hitbox.maxY = posY + sizeY;
}

void ez::GUI::setPosition(sf::Vector2f pos)
{
	this->setGUIPosition(pos.x, pos.y);
	this->verifyIfObjectIsNotInZone();
}

void ez::GUI::setPosition(int posX, int posY)
{
	this->setGUIPosition(posX, posY);
	this->verifyIfObjectIsNotInZone();
}

sf::Vector2f ez::GUI::getSize() const
{
	return (sf::Vector2f((float)(hitbox.maxX - hitbox.minX), (float)(hitbox.maxY - hitbox.minY)));
}

sf::Vector2f ez::GUI::getPosition() const
{
	return (sf::Vector2f((float)(hitbox.minX), (float)(hitbox.minY)));
}

 void ez::GUI::GUIEffect([[maybe_unused]] sf::Event &event, [[maybe_unused]] sf::RenderWindow &window)
{
	this->execEventList();
}

bool ez::GUI::Selected(void)
{
	return (selected);
}

ez::GuiState ez::GUI::getState(void)
{
    return (state);
}

void ez::GUI::ChangeWindowValue(sf::RenderWindow &window)
{
	sf::Vector2u windowSize = window.getSize();

	hitbox.initialSize.x = windowSize.x;
	hitbox.initialSize.y = windowSize.y;
}

void ez::GUI::ActualizeHitbox(sf::RenderWindow &window)
{
	sf::Vector2u windowSize = window.getSize();
	float differenceX = 0;
	float differenceY = 0;


	if (hitbox.initialSize.x != windowSize.x ||
		hitbox.initialSize.y != windowSize.y) {
		differenceX = (float)windowSize.x / (float)hitbox.initialSize.x;
		differenceY = (float)windowSize.y / (float)hitbox.initialSize.y;
		hitbox.initialSize = windowSize;
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

bool ez::GUI::Hovered(sf::Event event, sf::RenderWindow &window)
{
	if (state == ez::GuiState::BLOCKED ||
	event.type == sf::Event::MouseButtonPressed ||
	event.type == sf::Event::MouseButtonReleased || state == ez::GuiState::PRESSED || 
	state == ez::GuiState::PRESSED_OUT) {
		return (false);
	}
	if (isMouseInHitbox(hitbox, window)) {
		state = ez::GuiState::HOVERED;
		return (true);
	}
	if (state == ez::GuiState::HOVERED)
		state = ez::GuiState::NONE;
	return (false);
}

bool ez::GUI::Pressed(sf::Event event, sf::RenderWindow &window)
{
	if (state == ez::GuiState::BLOCKED ||
		(event.type != sf::Event::MouseButtonPressed && 
		state != ez::GuiState::PRESSED && state != ez::GuiState::PRESSED_OUT)) {
		if (state == ez::GuiState::PRESSED || state == ez::GuiState::PRESSED_OUT)
			state = GuiState::NONE;
		return (false);
	}
	if (isMouseInHitbox(hitbox, window)) {
		state = ez::GuiState::PRESSED;
		return (true);
	}
	else if (state == ez::GuiState::PRESSED || state == ez::GuiState::PRESSED_OUT) {
		state = ez::GuiState::PRESSED_OUT;
		return (false);
	}
	return (false);
}

bool ez::GUI::Released(sf::Event event, sf::RenderWindow &window)
{
	if (state == ez::GuiState::BLOCKED || event.type != sf::Event::MouseButtonReleased) {
		if (state == ez::GuiState::RELEASED)
			state = ez::GuiState::NONE;
		return (false);
	}
	if (state != ez::GuiState::PRESSED && selected == false) {
		if (state != ez::GuiState::HOVERED)
			state = ez::GuiState::NONE;
		return (false);
	}
	if (isMouseInHitbox(hitbox, window) == true) {
		selected = true;
		state = ez::GuiState::RELEASED;
		return (true);
	} else {
		if (state == ez::GuiState::RELEASED)
			state = ez::GuiState::NONE;
		selected = false;
	}
	return (false);
}

void ez::GUI::Actualize(sf::Event &event, sf::RenderWindow &window)
{
	if (ignoreActualisation == true) {
		ignoreActualisation = false;
	} else {
		this->ActualizeHitbox(window);
		this->Hovered(event, window);
		this->Pressed(event, window);
		this->Released(event, window);
		this->GUIEffect(event, window);
	}
}

ez::GUI::GUI()
{
    std::list<std::function<void(void)>> tmpList;

	state = ez::GuiState::NONE;
	hitbox = { sf::Vector2u{0, 0}, 0, 0, 0, 0 };
	NoEffectZone = nullptr;
	selected = false;
	ignoreActualisation = false;
	eventFuncs.reserve(6);
	for (unsigned int i = 0; i < 6; i++) {
	    eventFuncs.emplace_back(tmpList);
	}
}


ez::GUI::~GUI()
{
	if (NoEffectZone != NULL)
		delete NoEffectZone;
}
