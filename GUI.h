#ifndef GUI_HP
#define GUI_HP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "structs.h"
#include "QuickCreate.h"
#include <functional>

namespace ez
{
	class GUI
	{
	public:
		GUI();
		virtual ~GUI();
		void ChangeWindowValue(sf::RenderWindow &window);
		void ActualizeHitbox(sf::RenderWindow &window);
		virtual void Actualize(sf::Event &event, sf::RenderWindow &window);
		virtual void GUIEffect([[maybe_unused]] sf::Event &event, [[maybe_unused]] sf::RenderWindow &window);
		virtual sf::Vector2f getPosition() const;
		virtual sf::Vector2f getSize() const;
		virtual void setPosition(int posX, int posY);
		virtual void setPosition(sf::Vector2f pos);
		virtual void setSize(int x, int y);
		bool Selected();
		ez::GuiState getState(void);
		hitbox_t getHitbox(void);
		void resetHitbox();
		void setHitbox(hitbox_t hitbox);
		virtual void setGUIPosition(int posX, int posY);
		virtual void Draw(sf::RenderWindow &window);
		virtual void moveHitbox(sf::Vector2f pos);
		virtual void setNoEffectZone(hitbox_t NewNoEffectZone);
	//	void addOneElementInEventList(ez::GuiState eventKind, std::function<void(ez::GUI *)> func);

        template <typename Function, typename... Args>
		void addOneElementInEventList(ez::GuiState eventKind, Function &&func, Args&&... args)
		{
			auto lambda =
					[&func, &args...]
					{
						std::invoke(func, args...);
					};
			this->eventFuncs[eventKind].push_back(lambda);
		}
	protected:
		ez::GuiState state;
		bool selected;
		bool ignoreActualisation;
		hitbox_t hitbox;
		hitbox_t *NoEffectZone;
		void verifyIfObjectIsNotInZone();
		std::vector<std::list<std::function<void(void)>>> eventFuncs;
        void execEventList();
	private:
		bool Hovered(sf::Event event, sf::RenderWindow &window);
		bool Pressed(sf::Event event, sf::RenderWindow &window);
		bool Released(sf::Event event, sf::RenderWindow &window);
	};
}
#endif
