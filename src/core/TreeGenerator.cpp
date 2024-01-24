
#include "../include/core/TreeGenerator.h"
#include <debug.h>
#include <stack>

namespace Tree {
TreeGenerator::TreeGenerator()
    : gen(rd())
{
}

void TreeGenerator::setParams(TreeParams& params) { m_params = params; }

void TreeGenerator::generateTree(std::vector<Operation>& operation)
{
    m_canvas.create(m_params.canvasSize.x, m_params.canvasSize.y);
    m_canvas.clear(sf::Color(0, 0, 0, 0));

    m_turtle.depth = 0;
    m_turtle.angle = 270;
    m_turtle.length = m_params.baseBranchLength;
    m_turtle.width = m_params.baseBranchWidth;
    m_turtle.position = sf::Vector2f(m_params.canvasSize.x / 2, m_params.canvasSize.y);

    std::uniform_real_distribution<> disAngle(m_params.angle.x, m_params.angle.y);

    for (const auto& op : operation) {
        switch (op) {
        case Push:
            m_turtleStack.push(m_turtle);
            m_turtle.depth++;
            m_turtle.width *= m_params.widthReduction;
            m_turtle.length *= m_params.lengthReduction;
            break;

        case Pop:
            m_turtle = m_turtleStack.top();
            m_turtleStack.pop();
            break;

        case MoveLeft:
            m_turtle.position.x -= m_turtle.width * 0.5;
            break;

        case MoveRight:
            m_turtle.position.x += m_turtle.width * 0.5;
            break;

        case RotateLeft: {
            m_turtle.angle -= disAngle(gen);
        } break;

        case RotateRight: {
            m_turtle.angle += disAngle(gen);
            break;
        }

        case Advance: {
            // TODO: shrink length/width
            // Draw vertex instead of rectangle
            // Draw leaves and flowers

            sf::Sprite woodSprite(*m_params.woodTexture);
            woodSprite.setOrigin(0, m_turtle.width / 2);
            woodSprite.setTextureRect(sf::IntRect(0, 0, m_turtle.length, m_turtle.width));
            woodSprite.setPosition(m_turtle.position);
            woodSprite.setRotation(m_turtle.angle);

            m_canvas.draw(woodSprite);

            float angleInRadians = (m_turtle.angle - 90) * 3.14159 / 180.0;
            float offsetX = std::sin(angleInRadians) * m_turtle.length;
            float offsetY = std::cos(angleInRadians) * m_turtle.length;
            m_turtle.position += sf::Vector2f(-offsetX, offsetY);
        } break;

        default:
            break;
        }
    }
}

std::optional<TreeParams::LeafOrFlowerData> TreeGenerator::getRandomTexture(
    std::vector<TreeParams::LeafOrFlowerData>& textures)
{
    std::vector<TreeParams::LeafOrFlowerData> candidates;
    for (const auto& flower : textures) {
        if (flower.minDepth <= m_turtle.depth) {
            candidates.push_back(flower);
        }
    }

    if (candidates.size() == 1) {
        return candidates.at(0);
    } else if (candidates.size() > 1) {
        return candidates.at(rand() % candidates.size());
    }

    return std::nullopt;
}

sf::Sprite TreeGenerator::getSprite()
{
    m_canvas.display();
    sf::Sprite sprite(m_canvas.getTexture());
    sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height);
    return sprite;
}
}