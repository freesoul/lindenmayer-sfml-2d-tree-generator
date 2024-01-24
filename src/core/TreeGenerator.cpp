
#include "../include/core/TreeGenerator.h"
#include <debug.h>
#include <stack>

namespace Tree {
TreeGenerator::TreeGenerator()
{
    rules['a'] = { { { Advance, Push, RotateRight, 'a', Pop, Push, RotateLeft, 'a', Pop, 'a' }, 3.0 },
        { { Advance, Push, RotateRight, 'a', Pop, 'a' }, 1.0 }, { { Advance, Push, RotateLeft, 'a', Pop, 'a' }, 1.0 } };
}

void TreeGenerator::setParams(TreeParams& params) { m_params = params; }

void TreeGenerator::generateTree(std::vector<Operation>& operation)
{
    m_canvas.create(m_params.canvasSize.x, m_params.canvasSize.y);
    m_canvas.clear(sf::Color(0, 0, 0, 0));

    // sf::Sprite barkSprite(*m_params.barkTexture);
    // barkSprite.setOrigin(barkSprite.getTextureRect().width / 2, barkSprite.getTextureRect().height);

    for (const auto& op : operation) {
        switch (op) {
        case Push:
            m_turtleStack.push(m_turtle);
            break;

        case Pop:
            m_turtle = m_turtleStack.top();
            m_turtleStack.pop();
            break;

        case RotateLeft:
            // m_turtle.angle -= m_params.baseBranchAngle;
            break;

        case RotateRight:
            // m_turtle.angle += m_params.baseBranchAngle;
            break;

        case Shrink:
            // m_turtle.length *= m_params.baseScaleDown;
            // m_turtle.width *= m_params.baseScaleDown;
            break;

        case Advance: {
            // branchSprite.setTextureRect(sf::IntRect(0, 0, m_turtle.width, m_turtle.length));
            // branchSprite.setPosition(m_turtle.position);
            // branchSprite.setOrigin(sf::Vector2f(m_turtle.width / 2, m_turtle.length));
            // branchSprite.setRotation(m_turtle.angle);

            // m_canvas.draw(branchSprite);

            // float angleInRadians = (m_turtle.angle - 90) * 3.14159 / 180.0;
            // float offsetY = std::sin(angleInRadians) * m_turtle.length;
            // float offsetX = std::cos(angleInRadians) * m_turtle.length;
            // m_turtle.position += sf::Vector2f(offsetX, offsetY);
        } break;

        default:
            break;
        }
    }
}

sf::Sprite TreeGenerator::getSprite()
{
    m_canvas.display();
    sf::Sprite sprite(m_canvas.getTexture());
    sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height);
    return sprite;
}
}