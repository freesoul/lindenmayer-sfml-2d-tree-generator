#pragma once

#include <SFML/System/Vector2.hpp>

namespace Tree {
struct Turtle {
    unsigned int depth;

    sf::Vector2f position;

    float angle;

    float branchLength;

    float branchWidth;

    float barkLength;

    float barkWidth;
};

}