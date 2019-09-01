#ifndef STACKELEMENTS
#define STACKELEMENTS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "structs.h"
#include <tuple>
#include "FillableObject.hpp"
#include "GUI.h"

namespace ez {

	typedef enum Orientation
	{
		HORIZONTAL, VERTICAL
	}Orientation;

	typedef struct StackElementInitStruct
	{
		unsigned int elementsToShow;
		unsigned int width;
		unsigned int height;
		double posX;
		double posY;
		int untilNewLine = -1;
		std::string upbuttonpath = "Resources/up.png";
		std::string downbuttonpath = "Resources/down.png";
		unsigned int windowSizeX = 1920;
		unsigned int windowSizeY = 1080;
	}StackElementInitStruct;

	typedef struct StackPanelInit
	{
		float posX = 0;
		float posY = 0;
		sf::Vector2f margin{ 0, 0 };
		Orientation StackPanelOrientation = Orientation::HORIZONTAL;
		unsigned int windowSizeX = 1920;
		unsigned int windowSizeY = 1080;
	}StackPanelInit;

	typedef enum StackPanelObjectType
	{
		GUI_OBJ, TEXT, SHAPE, SPRITE
	}StackPanelObjectType;

	typedef enum StackPanelTupleGet
	{
		OBJECT, TYPE, SIZE, POS, MARGIN
	}StackPanelTupleGet;

class StackPanel : public GUI
	{
	public:
		StackPanel();
		StackPanel(StackPanelInit &init);
		StackPanel(StackPanelInit &&init);
		StackPanel(Orientation orientation): StackPanel() {this->StackPanelOrientation = orientation;}
		~StackPanel() {delete normalView; delete StackPanelCropedView;}
		void Add(sf::Shape *object, sf::Vector2f objectMargin = { 0, 0 });
		void Add(sf::Sprite *object, sf::Vector2f objectMargin = { 0, 0 });
		void Add(sf::Text *object, sf::Vector2f objectMargin = { 0, 0 });
		void Add(ez::GUI *object, sf::Vector2f objectMargin = { 0, 0 });
		void setMargin(sf::Vector2f margin);
		void setMargin(float width, float height);
		void setPosition(sf::Vector2f pos) override final;
		void setPosition(int x, int y) override final;
		sf::Vector2f getPosition() const override final;
		sf::Vector2f getMargin() const;
		sf::Vector2f getSize() const override final;
		void Actualize(sf::Event &event, sf::RenderWindow &window) override final;
		void setNoEffectZone(hitbox_t NewNoEffectZone) override final;
		void Draw(sf::RenderWindow &window);
		void RemoveElement(int atIndex);
		void staticIt(sf::Vector2f size, sf::Vector2f where, sf::RenderWindow &windowSize);
		void moveHitbox(sf::Vector2f pos) override final;
		void setViewPercent(float percentX, float percentY);
		void setOrientation(ez::Orientation orientation);
		void clear();
	private:
		std::list<std::tuple<void *, StackPanelObjectType, sf::Vector2f, sf::Vector2f, sf::Vector2f>> elements;
		sf::Vector2f margin;
		sf::Vector2f size;
		sf::Vector2f staticSize;
		sf::Vector2f pos;
		Orientation StackPanelOrientation;
		sf::Vector2f evaluateNewElementPosition(sf::Vector2f objectMargin) const;
		void(ez::StackPanel::*DrawAs[4])(void *object, sf::RenderWindow &window);
		void(ez::StackPanel::*SetPosAs[4])(void *object, sf::Vector2f &pos);
		void SetPosAsEzGUI(void *object, sf::Vector2f &pos);
		void SetPosAsSfShape(void *object, sf::Vector2f &pos);
		void SetPosAsSfText(void *object, sf::Vector2f &pos);
		void SetPosAsSfSprite(void *object, sf::Vector2f &pos);
		void DrawAsEzGUI(void *object, sf::RenderWindow &window);
		void DrawAsSfShape(void *object, sf::RenderWindow &window);
		void DrawAsSfText(void *object, sf::RenderWindow &window);
		void DrawAsSfSprite(void *object, sf::RenderWindow &window);
		void resetToOldPosition(ez::GUI *obj);
		sf::View *normalView;
		sf::View *StackPanelCropedView;
		sf::Vector2f actualMaxX;
		sf::Vector2f actualMaxY;
		sf::Vector2f previousStaticPosition;
		/*public:
			StackElements(StackElementInitStruct initStruct);
			StackElements();
			~StackElements();
			void Create(StackElementInitStruct initStruct);
			void addToStack(void *element, unsigned int position = 1);
			void Draw(sf::RenderWindow &window);
			void Actualize(sf::Event &event, sf::RenderWindow &window);
			bool Released(sf::Event &event, sf::RenderWindow &window);
		private:
			std::list<void *> stack;
			hitbox_t elementsHitbox;
			unsigned int elementToIgnore;
			unsigned int elementsToShow;
			int selectedElement;
			unsigned int width;
			unsigned int height;
			double posX;
			double posY;
			unsigned int size;
			int untilNewLine;
			sf::RectangleShape background;
			SingleStateButton up;
			SingleStateButton down;*/
	};
}
#endif
