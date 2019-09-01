//
// Created by axel on 5/3/19.
//

#ifndef EZSFML_CHECKBOX_HPP
#define EZSFML_CHECKBOX_HPP

#include "ButtonClass.h"

namespace ez {
    class Checkbox : public Button {
    public:
        Checkbox(std::string texturePath, sf::Vector2f buttonSize, sf::Vector2f buttonPos, sf::Vector2f buttonPlaceOnSpritesheet);
        void GUIEffect(sf::Event &event, sf::RenderWindow &window) override;
        void GUIEffectChecked();
        void GUIEffectUnchecked();
        bool getChecked();
    public:
        bool checked;
    };
}


#endif //EZSFML_CHECKBOX_HPP
