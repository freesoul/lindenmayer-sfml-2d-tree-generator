#pragma once

#include <SFML/System/Vector2.hpp>

namespace Tree {
struct Turtle {
    unsigned int depth;

    sf::Vector2f position;

    float angle;

    float length;

    float width;

    float shrinkWidthRate;

    float shrinkLengthRate;
};

}