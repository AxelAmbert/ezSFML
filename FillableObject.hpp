//
// Created by axelambert on 16/04/19.
//

#ifndef LIBSFML_FILLABLEOBJECT_HPP
#define LIBSFML_FILLABLEOBJECT_HPP

#include "GUI.h"

namespace ez {
    class FillableObject {
        virtual void Add(ez::GUI *object) = 0;
        virtual void Draw(sf::RenderWindow &window) = 0;
        virtual void Actualize(sf::Event &event, sf::RenderWindow &window) = 0;
    };
}

#endif //LIBSFML_FILLABLEOBJECT_HPP
