#include "Graph.hpp"

ez::Graph::Graph(float minValue, float maxValue, sf::Vector2f size)
{
  _min = minValue;
  _max = maxValue;
  graphRec = sf::RectangleShape(size);
  graphRec.setFillColor(sf::Color::White);
  graphicBar = sf::RectangleShape(sf::Vector2f(10, 0));
  graphicBar.setFillColor(sf::Color::Blue);
  graphicBarX = 10;
}

void ez::Graph::addValue(float toAdd)
{
  if (graphValue.size() >= (graphRec.getSize().x / graphicBarX))
    graphValue.erase(graphValue.begin());
  graphValue.push_back(toAdd);
}

void ez::Graph::setPosition(sf::Vector2f pos)
{
  graphRec.setPosition(pos);
  hitbox.minX = pos.x;
  hitbox.minY = pos.y;
  hitbox.maxX = pos.x + graphRec.getSize().x;
  hitbox.maxY = pos.y + graphRec.getSize().y;
}

void ez::Graph::Draw(sf::RenderWindow &window)
{
  sf::Vector2f basePos = sf::Vector2f{graphRec.getPosition().x, graphRec.getPosition().y + graphRec.getSize().y};
  window.draw(graphRec);
  for (unsigned int i = 0; i < graphValue.size(); i++) {

      graphicBar.setSize(sf::Vector2f{graphicBarX, graphValue[i] * graphRec.getSize().y / _max});
      basePos.y = (graphRec.getPosition().y + graphRec.getSize().y) -  graphicBar.getSize().y;
      graphicBar.setPosition(basePos);
      basePos.x += graphicBarX;
      window.draw(graphicBar);
  }
}

void ez::Graph::setGraphicBarSize(float size)
{
  graphicBarX = size;
}
