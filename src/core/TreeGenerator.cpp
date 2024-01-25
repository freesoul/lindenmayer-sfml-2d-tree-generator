
#include "../include/core/TreeGenerator.h"
#include <debug.h>
#include <stack>

namespace Tree {
TreeGenerator::TreeGenerator()
    : gen(rd())
{
}

void TreeGenerator::setParams(TreeParams& params) { m_params = params; }

void TreeGenerator::generateTree(std::vector<Operation>& operations)
{
    m_canvas.create(m_params.canvasSize.x, m_params.canvasSize.y);
    m_canvas.clear(sf::Color(0, 0, 0, 0));

    m_turtle.depth = 0;
    m_turtle.angle = 270;
    m_turtle.branchLength = m_params.baseBranchLength;
    m_turtle.branchWidth = m_params.baseBranchWidth;
    m_turtle.barkLength = m_params.baseBarkLength;
    m_turtle.barkWidth = m_params.baseBarkWidth;
    m_turtle.position = sf::Vector2f(m_params.canvasSize.x / 2, m_params.canvasSize.y);

    std::uniform_real_distribution<> disAngle(m_params.angle.x, m_params.angle.y);

    unsigned int numOperations = operations.size();

    for (const auto& op : operations) {
        switch (op) {
        case Push:
            m_turtleStack.push(m_turtle);
            m_turtle.depth++;
            m_turtle.branchWidth *= m_params.branchPushWidthReduction;
            m_turtle.branchLength *= m_params.branchPushLengthReduction;
            m_turtle.barkWidth *= m_params.barkPushWidthReduction;
            m_turtle.barkLength *= m_params.barkPushLengthReduction;
            break;

        case Pop:
            m_turtle = m_turtleStack.top();
            m_turtleStack.pop();
            break;

        case MoveLeft:
            // TODO: take into account the angle!
            m_turtle.position.x -= m_turtle.branchWidth * 0.5;
            break;

        case MoveRight:
            // TODO: take into account the angle!
            m_turtle.position.x += m_turtle.branchWidth * 0.5;
            break;

        case RotateLeft: {
            m_turtle.angle -= disAngle(gen);
        } break;

        case RotateRight: {
            m_turtle.angle += disAngle(gen);
            break;
        }

        case AdvanceBranch: {
            // TODO: Draw leaves and flowers

            bool doShrink = false;
            for (int i = 0; i < 4; i++) {
                if (m_turtle.depth + i >= numOperations) {
                    break;
                }
                if (operations.at(m_turtle.depth + i) == AdvanceBranch) {
                    doShrink = true;
                    break;
                }
            }

            float widthMargin = 0.f;
            if (doShrink) {
                widthMargin = m_turtle.branchWidth * (1 - m_params.branchAdvanceWidthReduction) * 0.5;
            }

            sf::ConvexShape polygon(4);

            polygon.setPoint(0, sf::Vector2f(0, 0));
            polygon.setPoint(1, sf::Vector2f(m_turtle.branchLength, 0 + widthMargin));
            polygon.setPoint(2, sf::Vector2f(m_turtle.branchLength, m_turtle.branchWidth - widthMargin));
            polygon.setPoint(3, sf::Vector2f(0, m_turtle.branchWidth));

            polygon.setOrigin(0, m_turtle.branchWidth / 2);
            polygon.setPosition(m_turtle.position);
            polygon.setRotation(m_turtle.angle);

            polygon.setTexture(m_params.woodTexture.get());
            polygon.setTextureRect(sf::IntRect(0, 0, m_turtle.branchLength, m_turtle.branchWidth));

            m_canvas.draw(polygon);

            float angleInRadians = (m_turtle.angle - 90) * 3.14159 / 180.0;
            float offsetX = std::sin(angleInRadians) * m_turtle.branchLength;
            float offsetY = std::cos(angleInRadians) * m_turtle.branchLength;
            m_turtle.position += sf::Vector2f(-offsetX, offsetY);

            m_turtle.branchWidth *= m_params.branchAdvanceWidthReduction;
            m_turtle.branchLength *= m_params.branchAdvanceLengthReduction;
        } break;

        case AdvanceBark: {
            // Test if in the next 4 operations there's a AdvanceBark operation, to start shrinking in advance
            bool doShrink = false;
            for (int i = 0; i < 4; i++) {
                if (m_turtle.depth + i >= numOperations) {
                    break;
                }
                if (operations.at(m_turtle.depth + i) == AdvanceBark) {
                    doShrink = true;
                    break;
                }
            }

            float widthMargin = 0.f;
            if (doShrink) {
                widthMargin = m_turtle.barkWidth * (1 - m_params.barkAdvanceWidthReduction) * 0.5;
            }

            sf::ConvexShape polygon(4);

            polygon.setPoint(0, sf::Vector2f(0, 0));
            polygon.setPoint(1, sf::Vector2f(m_turtle.barkLength, 0 + widthMargin));
            polygon.setPoint(2, sf::Vector2f(m_turtle.barkLength, m_turtle.barkWidth - widthMargin));
            polygon.setPoint(3, sf::Vector2f(0, m_turtle.barkWidth));

            polygon.setOrigin(0, m_turtle.barkWidth / 2);
            polygon.setPosition(m_turtle.position);
            polygon.setRotation(m_turtle.angle);

            polygon.setTexture(m_params.woodTexture.get());
            polygon.setTextureRect(sf::IntRect(0, 0, m_turtle.barkLength, m_turtle.barkWidth));

            m_canvas.draw(polygon);

            float angleInRadians = (m_turtle.angle - 90) * 3.14159 / 180.0;
            float offsetX = std::sin(angleInRadians) * m_turtle.barkLength;
            float offsetY = std::cos(angleInRadians) * m_turtle.barkLength;
            m_turtle.position += sf::Vector2f(-offsetX, offsetY);

            m_turtle.barkWidth *= m_params.barkAdvanceWidthReduction;
            m_turtle.barkLength *= m_params.barkAdvanceLengthReduction;
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