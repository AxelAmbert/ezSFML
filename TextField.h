#ifndef TEXTFIELD
#define TEXTFIELD
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "GUI.h"

typedef struct TextFieldInitStruct
{
	sf::Vector2f size;
	sf::Vector2f pos;
	int untilNewLine = -1;
	unsigned int windowSizeX = 1920;
	unsigned int windowSizeY = 1080;
	std::string emptyText = "Enter Text Here";
}TextFieldInitStruct;

namespace ez
{
	class TextField : public GUI
	{
	public:
		TextField();
		TextField(TextFieldInitStruct initStruct);
		~TextField();
		void Create(TextFieldInitStruct initStruct);
		void Draw(sf::RenderWindow &window);
		void isTextFieldAPassword(bool Password);
		void(*textIsEntered)(sf::Event &, sf::RenderWindow &);
		void(*textHasChanged)(TextField *sender, sf::Event &, sf::RenderWindow &);
		unsigned int length(void);
		std::string GetKeyboardText(void);
		sf::Vector2f getPosition() const override final;
		sf::Vector2f getSize() const override final;
		void setPosition(int posX, int posY) override final;
		void setPosition(sf::Vector2f pos) override final;
		void clear(sf::RenderWindow &window);
		void link(ez::TextField *toLink);
	private:
		sf::RectangleShape blinkingBar;
		sf::Text toPrint;
		sf::Text emptyTextToPrint;
		std::string realText;
		sf::Clock blinkClock;
		bool isAPassword;
		bool isVisible;
		unsigned int textLength;
		unsigned int blinkingBarPosition;
		float sizeX;
		float sizeY;
		sf::Vector2f pos;
		ez::TextField *linked;
		void GetKeyboardData(sf::Event &event, sf::RenderWindow &window);
		void EnableBlinkingBar(sf::RenderWindow &window);
		void DeplaceBlinkingBar();
		void GUIEffect(sf::Event &event, sf::RenderWindow &window);
		void setBarToEnd(sf::RenderWindow &window);
		void DecideHowMuchTextToShow(sf::RenderWindow &window);
	};
}
#endif
