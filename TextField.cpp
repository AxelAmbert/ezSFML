#include "TextField.h"

void ez::TextField::link(ez::TextField *toLink)
{
	linked = toLink;
}

void ez::TextField::setPosition(sf::Vector2f pos)
{
	this->setGUIPosition((int)pos.x, (int)pos.y);
	this->pos = pos;
	emptyTextToPrint.setPosition(sf::Vector2f(pos.x + 20, pos.y + (sizeY / 2 - emptyTextToPrint.getCharacterSize() / 2)));
	toPrint.setPosition(sf::Vector2f(pos.x + 20, pos.y + (sizeY / 2 - emptyTextToPrint.getCharacterSize() / 2)));
	this->DeplaceBlinkingBar();
}

void ez::TextField::setPosition(int x, int y)
{
	this->setGUIPosition(x, y);
	this->pos = pos;
	emptyTextToPrint.setPosition(sf::Vector2f(x + 20, y + (sizeY / 2 - emptyTextToPrint.getCharacterSize() / 2)));
	toPrint.setPosition(sf::Vector2f(x + 20, y + (sizeY / 2 - emptyTextToPrint.getCharacterSize() / 2)));
	this->DeplaceBlinkingBar();
}

sf::Vector2f ez::TextField::getSize() const
{
	return (sf::Vector2f{ sizeX, sizeY });
}

sf::Vector2f ez::TextField::getPosition() const
{
	return (pos);
}

std::string ez::TextField::GetKeyboardText(void)
{
	return (realText);
}

unsigned int ez::TextField::length(void)
{
	return ((unsigned int)realText.length());
}

std::string passwordIt(std::string toPassword)
{
	std::string tmp = toPassword;
	size_t size = toPassword.size();

	for (size_t i = 0; i < size; i++)
		tmp[i] = '*';
	return (tmp);
}

void ez::TextField::isTextFieldAPassword(bool Password)
{
	isAPassword = Password;
}

void ez::TextField::DecideHowMuchTextToShow(sf::RenderWindow &window)
{
	sf::Vector2f characterPos = toPrint.findCharacterPos(realText.length());

	FixBrokenMatrix(characterPos, window);
	if (characterPos.x >= pos.x + sizeX) {
		realText.pop_back();
		if (isAPassword == true) {
			toPrint.setString(passwordIt(realText));
		} else {
			toPrint.setString(realText);
		}
		textLength -= 1;
		blinkingBarPosition -= 1;
		this->DeplaceBlinkingBar();
	}
}

void ez::TextField::Draw(sf::RenderWindow &window)
{
	sf::RectangleShape mdr;
	sf::Time tmpTime;

	mdr.setSize(sf::Vector2f(sizeX, sizeY));
	mdr.setPosition(sf::Vector2f(pos.x, pos.y));
	mdr.setFillColor(sf::Color::Red);
	window.draw(mdr);
	if (selected == false && textLength == 0)
		window.draw(emptyTextToPrint);
	else {
		window.draw(toPrint);
		tmpTime = blinkClock.getElapsedTime();
		if (isVisible == true && selected == true)
			window.draw(blinkingBar);
		if (tmpTime.asMilliseconds() > 500 && isVisible == true) {
			isVisible = false;
			blinkClock.restart();
		}
		else if (tmpTime.asMilliseconds() > 500 && isVisible == false) {
			isVisible = true;
			blinkClock.restart();
		}
	}
}

void ez::TextField::Create(TextFieldInitStruct initStruct)
{
	hitbox.initialSize = sf::Vector2u{ WINDOW_WIDTH, WINDOW_HEIGHT };
	hitbox.minX = initStruct.pos.x;
	hitbox.minY = initStruct.pos.y;
	hitbox.maxX = initStruct.pos.x + initStruct.size.x;
	hitbox.maxY = initStruct.pos.y + initStruct.size.y;
	sizeX = initStruct.size.x;
	sizeY = initStruct.size.y;
	pos = { initStruct.pos.x, initStruct.pos.y };
	emptyTextToPrint = createAText(initStruct.emptyText, 30, sf::Vector2f((float)(initStruct.size.x + 20), (float)(initStruct.pos.y + (initStruct.size.y / 2))), "Client/Graphical/Assets/bebas.otf");
	emptyTextToPrint.setPosition(sf::Vector2f(initStruct.pos.x + 20, initStruct.pos.y + (initStruct.size.y / 2 - emptyTextToPrint.getCharacterSize() / 2)));
	blinkingBar.setSize(sf::Vector2f(2, 25));
	blinkingBar.setFillColor(sf::Color::White);
	selected = false;
	textLength = 0;
	toPrint = createAText("", 30, sf::Vector2f(initStruct.size.x + 20, initStruct.pos.y + (initStruct.size.y / 2)), "Client/Graphical/Assets/bebas.otf");
	toPrint.setPosition(sf::Vector2f(initStruct.pos.x + 20, initStruct.pos.y + (initStruct.size.y / 2 - toPrint.getCharacterSize() / 2)));
	isVisible = false;
	isAPassword = false;
	this->textIsEntered = NULL;
	this->textHasChanged = NULL;
}

void ez::TextField::setBarToEnd(sf::RenderWindow &window)
{
	sf::Vector2f tmpCharacterPos;

	if (textLength == 0) {
		blinkingBar.setPosition(sf::Vector2f(pos.x + 20,
			pos.y + ((pos.x + sizeX - pos.y) / 2)));
		blinkingBarPosition = 1;
		return;
	} else {
		tmpCharacterPos + toPrint.findCharacterPos(this->realText.length());
		FixBrokenMatrix(tmpCharacterPos, window);
		blinkingBarPosition = this->realText.length() + 1;
	}
}

void ez::TextField::EnableBlinkingBar(sf::RenderWindow &window)
{
	sf::Vector2f tmpCharacterPos;
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	unsigned int i = 0;
	int differenceX = hitbox.minX - pos.x;

	if (textLength == 0) {
		blinkingBar.setPosition(sf::Vector2f(pos.x + 20,
			pos.y + ((pos.x + sizeX - pos.y) / 2)));
		blinkingBarPosition = 1;
		return;
	}	
	for ( ; i <= textLength; i++) {
		tmpCharacterPos = toPrint.findCharacterPos(i);
		FixBrokenMatrix(tmpCharacterPos, window);
		if (mousePos.x < (int)tmpCharacterPos.x + differenceX) {
			blinkingBarPosition = i;
			return;
		}
	}
	blinkingBarPosition = i;
}

void ez::TextField::GetKeyboardData(sf::Event &event, sf::RenderWindow &window)
{
	std::string::iterator it = realText.begin();

	if (event.type == sf::Event::TextEntered) {
		if (event.text.unicode > 31 && event.text.unicode < 127) {
			std::advance(it, blinkingBarPosition - 1);
			realText.insert(it, static_cast<char>(event.text.unicode));
			toPrint.setString(realText);
			blinkingBarPosition += 1;
			textLength++;
		}
		else if (event.text.unicode == 9) {
			if (linked != nullptr) {
				selected = false;
				state = ez::GuiState::NONE;
				linked->selected = true;
				linked->state = ez::GuiState::RELEASED;
				linked->ignoreActualisation = true;
				linked->setBarToEnd(window);
				linked->DeplaceBlinkingBar();
			}
		}
	} else if (event.type == sf::Event::KeyPressed) {
		if (event.text.unicode == 72 && blinkingBarPosition <= realText.length())
			blinkingBarPosition++;
		else if (event.text.unicode == 71 && blinkingBarPosition > 1)
			blinkingBarPosition--;
		if (event.text.unicode == 59 && blinkingBarPosition > 1) {
			std::advance(it, blinkingBarPosition - 2);
			realText.erase(it);
			toPrint.setString(realText);
			blinkingBarPosition -= 1;
			textLength--;
		}
	}
/*	if (realText.length() != len)
		textHasChanged(this, event, window);*/
}

void ez::TextField::GUIEffect(sf::Event &event, sf::RenderWindow &window)
{
	if (selected == false || state == ez::GuiState::BLOCKED)
		return;
	GetKeyboardData(event, window);
	if (isAPassword == true) {
		toPrint.setString(passwordIt(realText));
	}
	if (state == ez::GuiState::RELEASED) {
		this->EnableBlinkingBar(window);
	}
	this->DeplaceBlinkingBar();
	this->DecideHowMuchTextToShow(window);
}

void ez::TextField::DeplaceBlinkingBar()
{
	sf::Vector2f tmpCharacterPos = toPrint.findCharacterPos(blinkingBarPosition - 1);

	blinkingBar.setSize(sf::Vector2f(2, toPrint.getCharacterSize()));
	blinkingBar.setPosition(sf::Vector2f(tmpCharacterPos.x, tmpCharacterPos.y));
}

ez::TextField::TextField(TextFieldInitStruct initStruct)
{
	hitbox.initialSize = sf::Vector2u{ WINDOW_WIDTH, WINDOW_HEIGHT };
	hitbox.minX = initStruct.pos.x;
	hitbox.minY = initStruct.pos.y;
	hitbox.maxX = initStruct.pos.x + initStruct.size.x;
	hitbox.maxY = initStruct.pos.y + initStruct.size.y;
	sizeX = initStruct.size.x;
	sizeY = initStruct.size.y;
	emptyTextToPrint = createAText(initStruct.emptyText, 30, sf::Vector2f(initStruct.size.x + 20, initStruct.pos.y + (initStruct.size.y / 2)), "Client/Graphical/Assets/bebas.otf");
	emptyTextToPrint.setPosition(sf::Vector2f(initStruct.pos.x + 20, initStruct.pos.y + (initStruct.size.y / 2 - emptyTextToPrint.getCharacterSize() / 2)));
	blinkingBar.setSize(sf::Vector2f(2, 25));
	blinkingBar.setFillColor(sf::Color::White);
	selected = false;
	textLength = 0;
	toPrint = createAText("", 30, sf::Vector2f(initStruct.size.x + 20, initStruct.pos.y + (initStruct.size.y / 2)), "Client/Graphical/Assets/bebas.otf");
	toPrint.setPosition(sf::Vector2f(initStruct.pos.x + 20, initStruct.pos.y + (initStruct.size.y / 2 - toPrint.getCharacterSize() / 2)));
	isVisible = false;
	isAPassword = false;
	pos = sf::Vector2f{ initStruct.pos.x, initStruct.pos.y };
	linked = nullptr;
}

ez::TextField::TextField()
{
}


ez::TextField::~TextField()
{
}

void ez::TextField::clear(sf::RenderWindow &window)
{
	realText.clear();
	toPrint.setString(" ");
	this->blinkingBarPosition = -1;
	EnableBlinkingBar(window);
	textLength = 0;
}
