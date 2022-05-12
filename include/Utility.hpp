#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Graphics/Rect.hpp>
#include <cmath>

template <typename Object>
void centerOrigin(Object &object)
{
    sf::FloatRect bounds = object.getLocalBounds();
    object.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

#endif // UTILITY_HPP
