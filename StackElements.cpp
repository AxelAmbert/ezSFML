#include "StackElements.h"


void ez::StackPanel::clear()
{
	margin = sf::Vector2f{ 0, 0 };
	pos = sf::Vector2f{ 0, 0 };
	size = sf::Vector2f{ 0, 0 };
	hitbox.minX = 0;
	hitbox.minY = 0;
	hitbox.maxX = 0;
	hitbox.maxY = 0;
	StackPanelOrientation = Orientation::HORIZONTAL;
	DrawAs[0] = &ez::StackPanel::DrawAsEzGUI;
	DrawAs[1] = &ez::StackPanel::DrawAsSfText;
	DrawAs[2] = &ez::StackPanel::DrawAsSfShape;
	DrawAs[3] = &ez::StackPanel::DrawAsSfSprite;
	SetPosAs[0] = &ez::StackPanel::SetPosAsEzGUI;
	SetPosAs[1] = &ez::StackPanel::SetPosAsSfText;
	SetPosAs[2] = &ez::StackPanel::SetPosAsSfShape;
	SetPosAs[3] = &ez::StackPanel::SetPosAsSfSprite;
	staticSize = { 0, 0 };
	normalView = nullptr;
	StackPanelCropedView = nullptr;
	previousStaticPosition = {};
	actualMaxX = {};
	actualMaxY = {};
	elements.clear();
}

void ez::StackPanel::setOrientation(ez::Orientation orientation)
{
	StackPanelOrientation = orientation;
}

float spercent(float lol, float mdr)
{
	return (lol * 100 / mdr / 100);
}

void ez::StackPanel::resetToOldPosition(ez::GUI *object)
{
	hitbox_t hitbox = object->getHitbox();

	hitbox.minX -= previousStaticPosition.x;
	hitbox.maxX -= previousStaticPosition.x;
	hitbox.minY -= previousStaticPosition.y;
	hitbox.maxY -= previousStaticPosition.y;
	object->setHitbox(hitbox);
}

void ez::StackPanel::setViewPercent(float percentX, float percentY)
{
	float toGoX = percentX * actualMaxX.y / 100;
	float toGoY = percentY * actualMaxY.y / 100;

	StackPanelCropedView->move(sf::Vector2f{ (actualMaxX.x - toGoX) * -1, 0 });
	this->moveHitbox(sf::Vector2f{actualMaxX.x - toGoX, 0 });
	StackPanelCropedView->move(sf::Vector2f{ 0, (actualMaxY.x - toGoY) * -1 });
	this->moveHitbox(sf::Vector2f{ 0, actualMaxY.x - toGoY});
	actualMaxX.x = toGoX;
	actualMaxY.x = toGoY;
}

void ez::StackPanel::moveHitbox(sf::Vector2f pos)
{
	std::list<std::tuple<void *, ez::StackPanelObjectType, sf::Vector2f, sf::Vector2f, sf::Vector2f>>::iterator it = elements.begin();

	while (it != elements.end()) {
		if (std::get<ez::StackPanelTupleGet::TYPE>(*it) == ez::StackPanelObjectType::GUI_OBJ)
			static_cast<ez::GUI *>(std::get<ez::StackPanelTupleGet::OBJECT>(*it))->moveHitbox(pos);
		it++;
	}
}

void ez::StackPanel::setNoEffectZone(hitbox_t NewNoEffectZone)
{
	std::list<std::tuple<void *, ez::StackPanelObjectType, sf::Vector2f, sf::Vector2f, sf::Vector2f>>::iterator it = elements.begin();
	void *object = NULL;

	while (it != elements.end()) {
		if (std::get<ez::StackPanelTupleGet::TYPE>(*it) == ez::StackPanelObjectType::GUI_OBJ) {
			object = std::get<ez::StackPanelTupleGet::OBJECT>(*it);
			static_cast<ez::GUI *>(object)->setNoEffectZone(NewNoEffectZone);
		}
		it++;
	}
}
/*
void ez::StackPanel::staticIt(sf::Vector2f size, sf::Vector2f where,
		sf::RenderWindow &windowSize, sf::View inView)
{

}*/

void ez::StackPanel::staticIt(sf::Vector2f newSize, sf::Vector2f where,  sf::RenderWindow &window)
{
	std::list<std::tuple<void *, ez::StackPanelObjectType, sf::Vector2f, sf::Vector2f, sf::Vector2f>>::iterator it = elements.begin();
	sf::Vector2u windowSize = window.getSize();
	void *object = nullptr;
	hitbox_t LimitHitbox = { sf::Vector2u{(unsigned int)windowSize.x, (unsigned int)windowSize.y}, (double)where.x,  (double)where.x + newSize.x, (double)where.y, (double)where.y + newSize.y };
	staticSize = newSize;
	if (normalView == nullptr) {
		normalView = new sf::View{window.getView()};
		StackPanelCropedView = new sf::View{ sf::FloatRect(0.f, 0.f, newSize.x, newSize.y) };
	} else {
		*StackPanelCropedView = sf::View{ sf::FloatRect(0.f, 0.f, newSize.x, newSize.y) };
	}
	StackPanelCropedView->setViewport(
		sf::FloatRect{1.0f - spercent(windowSize.x - where.x, windowSize.x),
		1.0f - spercent(windowSize.y - where.y, windowSize.y),
		spercent(newSize.x, windowSize.x),
		spercent(newSize.y, windowSize.y)});
	actualMaxX = {0, this->size.x - staticSize.x};
	actualMaxY = { 0, this->size.y - staticSize.y };
	while (it != elements.end()) {
		if (std::get<ez::StackPanelTupleGet::TYPE>(*it) == ez::StackPanelObjectType::GUI_OBJ) {
			object = std::get<ez::StackPanelTupleGet::OBJECT>(*it);
			hitbox_t hit = static_cast<ez::GUI *>(object)->getHitbox();
			this->resetToOldPosition(static_cast<ez::GUI *>(object));
			static_cast<ez::GUI *>(object)->moveHitbox(where - this->pos);
			hit = static_cast<ez::GUI *>(object)->getHitbox();
			static_cast<ez::GUI *>(object)->setNoEffectZone(LimitHitbox);
		}
		it++;
	}
    this->pos = where;
    previousStaticPosition = where;
}

void ez::StackPanel::Actualize(sf::Event &event, sf::RenderWindow &window)
{
	std::list<std::tuple<void *, ez::StackPanelObjectType, sf::Vector2f, sf::Vector2f, sf::Vector2f>>::iterator it = elements.begin();

	while (it != elements.end()) {
		if (std::get<ez::StackPanelTupleGet::TYPE>(*it) == ez::StackPanelObjectType::GUI_OBJ)
			static_cast<ez::GUI *>(std::get<ez::StackPanelTupleGet::OBJECT>(*it))->Actualize(event, window);
		it++;
	}
}

void ez::StackPanel::SetPosAsEzGUI(void *object, sf::Vector2f &pos)
{
	static_cast<ez::GUI *>(object)->setPosition(pos);
}

void ez::StackPanel::SetPosAsSfText(void *object, sf::Vector2f &pos)
{
	static_cast<sf::Text *>(object)->setPosition(pos);
}

void ez::StackPanel::SetPosAsSfShape(void *object, sf::Vector2f &pos)
{
	static_cast<sf::Shape *>(object)->setPosition(pos);
}

void ez::StackPanel::SetPosAsSfSprite(void *object, sf::Vector2f &pos)
{
	static_cast<sf::Sprite *>(object)->setPosition(pos);
}

void ez::StackPanel::DrawAsEzGUI(void *object, sf::RenderWindow &window)
{
	static_cast<ez::GUI *>(object)->Draw(window);
}

void ez::StackPanel::DrawAsSfShape(void *object, sf::RenderWindow &window)
{
	window.draw(*static_cast<sf::RectangleShape *>(object));
}

void ez::StackPanel::DrawAsSfSprite(void *object, sf::RenderWindow &window)
{
	window.draw(*static_cast<sf::Sprite *>(object));
}

void ez::StackPanel::DrawAsSfText(void *object, sf::RenderWindow &window)
{
	window.draw(*static_cast<sf::Text *>(object));
}

void ez::StackPanel::Draw(sf::RenderWindow &window)
{
	std::list<std::tuple<void *, ez::StackPanelObjectType, sf::Vector2f, sf::Vector2f, sf::Vector2f>>::iterator it = elements.begin();

	if (StackPanelCropedView != nullptr) {
		window.setView(*StackPanelCropedView);
	}
	while (it != elements.end()) {
		((*this).*DrawAs[std::get<TYPE>(*it)])(std::get<OBJECT>(*it), window);
		it++;
	}
	if (normalView != nullptr) {
		window.setView(*normalView);
	}
}

sf::Vector2f ez::StackPanel::evaluateNewElementPosition(sf::Vector2f objectMargin) const
{
	sf::Vector2f lastElementPos = std::get<StackPanelTupleGet::POS>(*--elements.end());
	sf::Vector2f objectSize = std::get<StackPanelTupleGet::SIZE>(*--elements.end());

	if (StackPanelOrientation == Orientation::HORIZONTAL) {
		lastElementPos.x += objectSize.x + objectMargin.x;
		lastElementPos.y += objectMargin.y;
		return (lastElementPos);
	}
	lastElementPos.x += objectMargin.x;
	lastElementPos.y += objectSize.y + objectMargin.y;
	return (lastElementPos);
}

void ez::StackPanel::Add(sf::Sprite *object, sf::Vector2f objectMargin)
{
	sf::Vector2f newPos;
	sf::Vector2f sizeOfElement = sf::Vector2f{ object->getLocalBounds().width, object->getLocalBounds().height };
	if (elements.size() != 0)
		elements.push_back(std::make_tuple(object, SHAPE, sizeOfElement, evaluateNewElementPosition(objectMargin), objectMargin));
	else
		elements.push_back(std::make_tuple(object, SHAPE, sizeOfElement, this->getPosition(), objectMargin));
	object->setPosition(std::get<POS>(*--elements.end()));

	newPos = object->getPosition();
	if (newPos.x + sizeOfElement.x > pos.x + size.x)
		size.x += (newPos.x + sizeOfElement.x) - (pos.x + size.x);
	if (newPos.y + sizeOfElement.y > pos.y + size.y)
		size.y += (newPos.y + sizeOfElement.y) - (pos.y + size.y);
}

void ez::StackPanel::Add(sf::Text *object, sf::Vector2f objectMargin)
{
	sf::Vector2f newPos;
	sf::Vector2f sizeOfElement = sf::Vector2f{ object->getLocalBounds().width, object->getLocalBounds().height };
	if (elements.size() != 0)
		elements.push_back(std::make_tuple(object, SHAPE, sizeOfElement, evaluateNewElementPosition(objectMargin), objectMargin));
	else
		elements.push_back(std::make_tuple(object, SHAPE, sizeOfElement, this->getPosition(), objectMargin));
	object->setPosition(std::get<POS>(*--elements.end()));

	newPos = object->getPosition();
	if (newPos.x + sizeOfElement.x > pos.x + size.x)
		size.x += (newPos.x + sizeOfElement.x) - (pos.x + size.x);
	if (newPos.y + sizeOfElement.y > pos.y + size.y)
		size.y += (newPos.y + sizeOfElement.y) - (pos.y + size.y);
}

void ez::StackPanel::Add(sf::Shape *object, sf::Vector2f objectMargin)
{
	sf::Vector2f newPos;
	sf::Vector2f sizeOfElement = sf::Vector2f{ object->getLocalBounds().width, object->getLocalBounds().height };
	if (elements.size() != 0)
		elements.push_back(std::make_tuple(object, SHAPE, sizeOfElement, evaluateNewElementPosition(objectMargin), objectMargin));
	else 
		elements.push_back(std::make_tuple(object, SHAPE, sizeOfElement, this->getPosition(), objectMargin));

	object->setPosition(std::get<POS>(*--elements.end()));

	newPos = object->getPosition();
	if (newPos.x + sizeOfElement.x > pos.x + size.x)
		size.x += (newPos.x + sizeOfElement.x) - (pos.x + size.x);
	if (newPos.y + sizeOfElement.y > pos.y + size.y)
		size.y += (newPos.y + sizeOfElement.y) - (pos.y + size.y);
}

void ez::StackPanel::Add(ez::GUI *object, sf::Vector2f objectMargin)
{
	sf::Vector2f newPos;
	sf::Vector2f sizeOfElement = object->getSize();

	if (elements.size() != 0)
		elements.push_back(std::make_tuple(object, GUI_OBJ, object->getSize(), evaluateNewElementPosition(objectMargin), objectMargin));
	else
		elements.push_back(std::make_tuple(object, GUI_OBJ, object->getSize(), this->getPosition(), objectMargin));
	object->setPosition(std::get<POS>(*--elements.end()));
	newPos = object->getPosition();
	if (newPos.x + sizeOfElement.x > pos.x + size.x)
		size.x += (newPos.x + sizeOfElement.x) - (pos.x + size.x);
	if (newPos.y + sizeOfElement.y > pos.y + size.y)
		size.y += (newPos.y + sizeOfElement.y) - (pos.y + size.y);
}

void ez::StackPanel::setMargin(float width, float height)
{
	margin = sf::Vector2f{ width, height };
}

void ez::StackPanel::setMargin(sf::Vector2f newMargin)
{	
	margin = newMargin;
}

sf::Vector2f ez::StackPanel::getSize() const
{
	return (size);
}

sf::Vector2f ez::StackPanel::getMargin() const
{
	return (margin);
}

void ez::StackPanel::setPosition(sf::Vector2f newPos)
{
	std::list<std::tuple<void *, ez::StackPanelObjectType, sf::Vector2f, sf::Vector2f, sf::Vector2f>>::iterator it = elements.begin();
	sf::Vector2f beforePos;
	float differenceX = newPos.x - pos.x;
	float differenceY = newPos.y - pos.y;
	void *object = nullptr;
	StackPanelObjectType type = GUI_OBJ;

	this->setGUIPosition(newPos.x, newPos.y);
	while (it != elements.end()) {
		beforePos = std::get<StackPanelTupleGet::POS>(*it);
		beforePos += sf::Vector2f{ differenceX, differenceY };
		object = std::get<OBJECT>(*it);
		type = std::get<TYPE>(*it);
		*it = std::make_tuple(object, type, std::get<SIZE>(*it), beforePos, std::get<MARGIN>(*it));
		((*this).*SetPosAs[std::get<TYPE>(*it)])(std::get<OBJECT>(*it), beforePos);
		it++;
	}
    pos = newPos;
}

void ez::StackPanel::setPosition(int x, int y)
{
	std::list<std::tuple<void *, ez::StackPanelObjectType, sf::Vector2f, sf::Vector2f, sf::Vector2f>>::iterator it = elements.begin();
	sf::Vector2f beforePos;
	float differenceX = x - pos.x;
	float differenceY = y - pos.y;
	void *object = nullptr;
	StackPanelObjectType type = GUI_OBJ;

	this->setGUIPosition(x, y);
	while (it != elements.end()) {
		beforePos = std::get<StackPanelTupleGet::POS>(*it);
		beforePos += sf::Vector2f{ differenceX, differenceY };
		object = std::get<OBJECT>(*it);
		type = std::get<TYPE>(*it);
		*it = std::make_tuple(object, type, std::get<SIZE>(*it), beforePos, std::get<MARGIN>(*it));
		((*this).*SetPosAs[std::get<TYPE>(*it)])(std::get<OBJECT>(*it), beforePos);
		it++;
	}
	pos.x = x;
	pos.y = y;
}

sf::Vector2f ez::StackPanel::getPosition() const
{
	return (pos);
}

ez::StackPanel::StackPanel(StackPanelInit &&params)
{
	margin = params.margin;
	size = sf::Vector2f(0, 0);
	pos = sf::Vector2f(params.posX, params.posY);
	hitbox.minX = 0;
	hitbox.minY = 0;
	hitbox.maxX = 0;
	hitbox.maxY = 0;
	StackPanelOrientation = params.StackPanelOrientation;
	DrawAs[0] = &ez::StackPanel::DrawAsEzGUI;
	DrawAs[1] = &ez::StackPanel::DrawAsSfText;
	DrawAs[2] = &ez::StackPanel::DrawAsSfShape;
	DrawAs[3] = &ez::StackPanel::DrawAsSfSprite;
	SetPosAs[0] = &ez::StackPanel::SetPosAsEzGUI;
	SetPosAs[1] = &ez::StackPanel::SetPosAsSfText;
	SetPosAs[2] = &ez::StackPanel::SetPosAsSfShape;
	SetPosAs[3] = &ez::StackPanel::SetPosAsSfSprite;
	normalView = nullptr;
	StackPanelCropedView = nullptr;
	previousStaticPosition = {};
}

ez::StackPanel::StackPanel(StackPanelInit &params)
{
	margin = params.margin;
	size = sf::Vector2f(0, 0);
	pos = sf::Vector2f(params.posX, params.posY);
	hitbox.minX = params.posX;
	hitbox.minY = params.posY;
	hitbox.maxX = params.posX;
	hitbox.maxY = params.posY;
	StackPanelOrientation = params.StackPanelOrientation;
	DrawAs[0] = &ez::StackPanel::DrawAsEzGUI;
	DrawAs[1] = &ez::StackPanel::DrawAsSfText;
	DrawAs[2] = &ez::StackPanel::DrawAsSfShape;
	DrawAs[3] = &ez::StackPanel::DrawAsSfSprite;
	SetPosAs[0] = &ez::StackPanel::SetPosAsEzGUI;
	SetPosAs[1] = &ez::StackPanel::SetPosAsSfText;
	SetPosAs[2] = &ez::StackPanel::SetPosAsSfShape;
	SetPosAs[3] = &ez::StackPanel::SetPosAsSfSprite;
	normalView = nullptr;
	StackPanelCropedView = nullptr;
	previousStaticPosition = {};
}

ez::StackPanel::StackPanel()
{
	margin = sf::Vector2f{ 0, 0 };
	pos = sf::Vector2f{ 0, 0 };
	size = sf::Vector2f{ 0, 0 };
	hitbox.minX = 0;
	hitbox.minY = 0;
	hitbox.maxX = 0;
	hitbox.maxY = 0;
	StackPanelOrientation = Orientation::HORIZONTAL;
	DrawAs[0] = &ez::StackPanel::DrawAsEzGUI;
	DrawAs[1] = &ez::StackPanel::DrawAsSfText;
	DrawAs[2] = &ez::StackPanel::DrawAsSfShape;
	DrawAs[3] = &ez::StackPanel::DrawAsSfSprite;
	SetPosAs[0] = &ez::StackPanel::SetPosAsEzGUI;
	SetPosAs[1] = &ez::StackPanel::SetPosAsSfText;
	SetPosAs[2] = &ez::StackPanel::SetPosAsSfShape;
	SetPosAs[3] = &ez::StackPanel::SetPosAsSfSprite;
	staticSize = { 0, 0 };
	normalView = nullptr;
	StackPanelCropedView = nullptr;
	previousStaticPosition = {};
}

/*bool ez::StackElements::Released(sf::Event &event, sf::RenderWindow &window)
{
	hitbox_t hitbox = elementsHitbox;
	double saveSizeY = (hitbox.maxY - hitbox.minY) / elementsToShow;
	unsigned int showed = 0;
	bool tmpHitboxBool = false;

	hitbox.maxY = hitbox.minY + saveSizeY;
	for (unsigned int i = elementToIgnore; showed < elementsToShow && i < size; i++, showed++) {
		tmpHitboxBool = isMouseInHitbox(hitbox, window);
		if (tmpHitboxBool == true && selectedElement != i) {
			selectedElement = i;
			return (true);
		} else if (tmpHitboxBool == true) {
			selectedElement = 0;
			return (true);
		}
		hitbox.minY += saveSizeY;
		hitbox.maxY += saveSizeY;
	}
	return (false);
}

void ez::StackElements::Actualize(sf::Event &event, sf::RenderWindow &window)
{
	up.Actualize(event, window);
	down.Actualize(event, window);
	//std::cout << "Size ? " << size << std::endl;
	if (down.getState() == ez::RELEASED) {
		if (elementToIgnore + elementsToShow < size)
			elementToIgnore += elementsToShow;
	} else if (up.getState() == ez::RELEASED) {
		if (elementsToShow <= elementToIgnore)
			elementToIgnore -= elementsToShow;
	}
	if (event.type == sf::Event::MouseButtonReleased) {
		this->Released(event, window);
	}

}


void DrawElement(const sf::Drawable &shape, sf::RenderWindow &window)
{
	window.draw(shape);
}

void ez::StackElements::Draw(sf::RenderWindow &window)
{
	sf::RectangleShape coucou;
	
	unsigned int elementNbPosY = 0;
	unsigned int elementNbPosX = 0;
	unsigned int i = elementToIgnore;
	unsigned int onSameLine = 0;
	float tmpSize = (elementsHitbox.maxY - elementsHitbox.minY) / elementsToShow;
	coucou.setSize(sf::Vector2f(width, height / elementsToShow));
	
	coucou.setFillColor(sf::Color::White);
	std::list<void *>::iterator it = stack.begin();
	size = stack.size();
	//std::cout << elementToIgnore << std::endl;
	std::advance(it, elementToIgnore);
	for ( ; i < size && i < (elementToIgnore + elementsToShow) ; i++) {
		it->setPosition(sf::Vector2f(posX + (width / elementsToShow * elementNbPosX), posY + (height / elementsToShow * elementNbPosY) + (height / elementsToShow / 2)));
		if (i == selectedElement) {
			coucou.setPosition(sf::Vector2f(elementsHitbox.minX, elementsHitbox.minY + tmpSize * elementNbPosY));
			window.draw(coucou);
		}
		//DrawElement(static_cast<const sf::Re *>(*it));
		DrawElement(static_cast<ez::GUI *>(*it), window);

		onSameLine++;
		elementNbPosX++;
		if (onSameLine >= untilNewLine || untilNewLine == -1) {
			elementNbPosY++;
			elementNbPosX = 0;
			onSameLine = 0;
		}
		it++;
	}
	up.Draw(window);
	down.Draw(window);
}

void ez::StackElements::addToStack(void *element, unsigned int position)
{
	unsigned int place = 0;
	//std::list<sf::Text *>::iterator it = (stack.begin() + position - 1);
	if (position == 0) {
		stack.insert(stack.begin(), element);
	}
	else if (position > stack.size()) {
		stack.push_back(element);
	}
	else {
		stack.insert(stack.begin(), element);
	}
	size =+ 1;
}

void ez::StackElements::Create(StackElementInitStruct initStruct)
{
	elementsHitbox = hitbox_t{ sf::Vector2u{ initStruct.windowSizeX, initStruct.windowSizeY },
		initStruct.posX, initStruct.posX + initStruct.width, initStruct.posY, initStruct.posY + initStruct.height };
	width = initStruct.width;
	height = initStruct.height;
	posX = initStruct.posX;
	posY = initStruct.posY;
	elementsToShow = initStruct.elementsToShow;
	elementToIgnore = 1;
	selectedElement = -1;
	size = 0;
	untilNewLine = initStruct.untilNewLine;
	up.Create("Resources/up.png", sf::Vector2f(elementsHitbox.maxX, elementsHitbox.minY));
	down.Create("Resources/down.png", sf::Vector2f(elementsHitbox.maxX, elementsHitbox.maxY - 100));
}

ez::StackElements::StackElements(StackElementInitStruct initStruct)
{
	elementsHitbox = hitbox_t{ sf::Vector2u{ initStruct.windowSizeX, initStruct.windowSizeY },
	initStruct.posX, initStruct.posX + initStruct.width, initStruct.posY, initStruct.posY + initStruct.height };
	width = initStruct.width;
	height = initStruct.height;
	posX = initStruct.posX;
	posY = initStruct.posY;
	elementsToShow = initStruct.elementsToShow;
	elementToIgnore = 1;
	selectedElement = -1;
	size = 0;
	untilNewLine = initStruct.untilNewLine;
	up.Create("Resources/up.png", sf::Vector2f(elementsHitbox.maxX, elementsHitbox.minY));
	down.Create("Resources/down.png", sf::Vector2f(elementsHitbox.maxX, elementsHitbox.maxY - 100));
}

ez::StackElements::~StackElements()
{
}

ez::StackElements::StackElements()
{
}
*/
