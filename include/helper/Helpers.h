#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace Tree {

// inline sf::Vector2f rotatePointAroundOrigin(const sf::Vector2f& A, const sf::Vector2f& B, float angleDegrees)
// {
//     // Convert the angle to radians
//     float angleRadians = angleDegrees * 3.14159265358 / 180.0;

//     // Translate B to origin A
//     sf::Vector2f translatedB = B - A;

//     // Rotate the point
//     sf::Vector2f rotatedB;
//     rotatedB.x = translatedB.x * cos(angleRadians) - translatedB.y * sin(angleRadians);
//     rotatedB.y = translatedB.x * sin(angleRadians) + translatedB.y * cos(angleRadians);

//     // Translate back
//     rotatedB += A;

//     return rotatedB;
// }

inline sf::Vector2f movePointAlongDirection(const sf::Vector2f& point, float angleDegrees, float distance)
{
    float angleRadians = angleDegrees * 3.14159265358 / 180.0;

    sf::Vector2f movedPoint;
    movedPoint.x = point.x - distance * std::sin(angleRadians);
    movedPoint.y = point.y + distance * std::cos(angleRadians);

    return movedPoint;
}

}