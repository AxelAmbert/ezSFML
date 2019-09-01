#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <thread>
#include "structs.h"
#include "QuickCreate.h"
#include "GUI.h"

namespace ez
{
  class Graph : public GUI
  {
  public:
    Graph(float minValue, float maxValue, sf::Vector2f size);
    void addValue(float toAdd);
    void Draw(sf::RenderWindow &window);
    void setPosition(sf::Vector2f pos);
    void setGraphicBarSize(float size);
	void setMax(float max) {_max = max;}
	float getMax() {return _max;}
  private:
    std::vector<float> graphValue;
    sf::RectangleShape graphicBar;
    sf::RectangleShape graphRec;
    float _min;
    float _max;
    float graphicBarX;
  };
}

#endif
