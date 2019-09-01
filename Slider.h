#ifndef SLIDER
#define SLIDER
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "SingleStateButton.h"

namespace ez
{
	typedef enum SliderLimit
	{
		ABSOLUTEE, RELATIVEE
	}SliderLimit;
}

namespace ez
{
	typedef struct SliderCreation
	{
		std::string path;
		sf::IntRect sliderPlaceOnSpritesheet;
		sf::Vector2f sliderPos;
		sf::IntRect buttonPlaceOnSpritesheet;
		ez::SliderLimit limits;
	}SliderCreation;
}

namespace ez {
	class Slider : public GUI
	{
	public:
		Slider();
		Slider(SliderCreation properties);
		void Draw(sf::RenderWindow &window);
		void GUIEffect(sf::Event &event, sf::RenderWindow &window);
		void Block();
		void Deblock();
		float getValue() const;	
		void setValue(float value);
		sf::Vector2f getSize() const;
		sf::Vector2f getPosition() const;
		void setPosition(sf::Vector2f pos);
        void Create(SliderCreation properties);
		~Slider();
	private:
		ez::SingleStateButton button;
		sf::RectangleShape slider;
		sf::Texture sliderTexture;
		sf::Vector2f size;
		SliderLimit limits;
		float value;
		float valueMargin;
		void MoveHorizontaly(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &sliderSize);
		void MoveVerticaly(sf::Event &event, sf::RenderWindow &window, sf::Vector2f &sliderSize);
		void VerifyHorizontalLimits(sf::Vector2f sliderPos, sf::Vector2f sliderSize, sf::Vector2f buttonPos, sf::Vector2f buttonSize);
		void VerifyVerticalLimits(sf::Vector2f sliderPos, sf::Vector2f sliderSize, sf::Vector2f buttonPos, sf::Vector2f buttonSize);
		float GetPercentageValue(float min, float max, float value);
	};
}
#endif
