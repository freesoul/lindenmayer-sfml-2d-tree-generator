
#include <TreeGenerator.h>
#include <debug.h>
#include <stack>

namespace Tree
{
    TreeGenerator::TreeGenerator()
    {
        rules[Push] = {{{Push}, 1.0}};
        rules[Pop] = {{{Pop}, 1.0}};

        rules[RotateLeft] = {{{RotateLeft}, 1.0}};
        rules[RotateRight] = {{{RotateRight}, 1.0}};
        rules[Scale] = {{{Scale}, 1.0}};

        rules[Bark] = {{{Push, RotateLeft, Bark, Pop, Push, RotateRight, Bark, Pop, Bark, Bark}, 1.0}};
        rules[Branch] = {{{Branch}, 0.5}, {{Leaf}, 0.25}, {{Leaf}, 0.25}};

        rules[Leaf] = {{{Leaf}, 1.0}};
    }

    void TreeGenerator::setParams(TreeParams &params)
    {
        m_params = params;
    }

    std::vector<Operations> TreeGenerator::generateRules(unsigned int numIterations)
    {
        std::vector<Operations> operations = {Bark};

        m_turtle.angle = 0;
        m_turtle.position = m_params.origin;
        m_turtle.length = m_params.baseBranchLength;
        m_turtle.width = m_params.baseBranchWidth;

        for (int i = 0; i < numIterations; ++i)
        {
            operations = amplifyRules(operations);

#if DEBUG_LINDERNMAYER
            for (auto op : operations)
            {
                printf("%d ", op);
            }
            printf("\n");
#endif
        }

        return operations;
    }

    std::vector<Operations> TreeGenerator::amplifyRules(const std::vector<Operations> &system)
    {
        std::vector<Operations> newSystem;
        for (auto op : system)
        {
            if (rules.find(op) != rules.end())
            {
                auto replacementOperations = chooseOperations(rules.at(op));
                newSystem.insert(newSystem.end(), replacementOperations.begin(), replacementOperations.end());
            }
        }
        return newSystem;
    }

    std::vector<Operations> TreeGenerator::chooseOperations(const std::vector<RuleWithProbability> &outcomes)
    {
        double totalProbability = 0;
        for (const auto &outcome : outcomes)
        {
            totalProbability += outcome.probability;
        }

        double randomValue = (std::rand() / static_cast<double>(RAND_MAX)) * totalProbability;
        double cumulativeProbability = 0;
        for (const auto &outcome : outcomes)
        {
            cumulativeProbability += outcome.probability;
            if (randomValue <= cumulativeProbability)
            {
                return outcome.operations;
            }
        }

        // Fallback in case of rounding errors
        return outcomes.back().operations;
    }

    void TreeGenerator::generateTree(std::vector<Operations> &operations)
    {
        m_canvas.create(m_params.canvasSize.x, m_params.canvasSize.y);
        m_canvas.clear(sf::Color(0, 0, 0, 0));

        sf::Sprite barkSprite(*m_params.barkTexture);
        barkSprite.setOrigin(barkSprite.getTextureRect().width / 2, barkSprite.getTextureRect().height);

        sf::Sprite flowerSprite(*m_params.flowerTexture);
        flowerSprite.setOrigin(flowerSprite.getTextureRect().width / 2, flowerSprite.getTextureRect().height);

        sf::Sprite branchSprite(*m_params.branchTexture);
        branchSprite.setOrigin(branchSprite.getTextureRect().width / 2, branchSprite.getTextureRect().height);

        sf::Sprite leafSprite(*m_params.leafTexture);
        leafSprite.setOrigin(leafSprite.getTextureRect().width / 2, leafSprite.getTextureRect().height);

        for (auto op : operations)
        {
            switch (op)
            {
            case Push:
                m_turtleStack.push(m_turtle);
                break;

            case Pop:
                m_turtle = m_turtleStack.top();
                m_turtleStack.pop();
                break;

            case RotateLeft:
                m_turtle.angle -= m_params.baseBranchAngle;
                break;

            case RotateRight:

                m_turtle.angle += m_params.baseBranchAngle;
                break;

            case Scale:
                m_turtle.length *= m_params.baseScaleDown;
                m_turtle.width *= m_params.baseScaleDown;
                break;

            case Bark:
            {
                barkSprite.setTextureRect(sf::IntRect(0, 0, m_turtle.width, m_turtle.length));
                barkSprite.setPosition(m_turtle.position);
                barkSprite.setOrigin(sf::Vector2f(m_turtle.width / 2, m_turtle.length));
                barkSprite.setRotation(m_turtle.angle);
                m_canvas.draw(barkSprite);

                // sf::CircleShape circle(50.f);
                // circle.setFillColor(sf::Color::Green);
                // circle.setPosition(m_turtle.position);
                // circle.setOrigin(sf::Vector2f(25.f, 25.f));
                // m_canvas.draw(circle);

                // Update the turtle position
                float angleInRadians = (m_turtle.angle - 90) * 3.14159 / 180.0;
                float offsetY = std::sin(angleInRadians) * m_turtle.length;
                float offsetX = std::cos(angleInRadians) * m_turtle.length;
                m_turtle.position += sf::Vector2f(offsetX, offsetY);
            }
            break;

            case Branch:
            {
                branchSprite.setTextureRect(sf::IntRect(0, 0, m_turtle.width, m_turtle.length));
                branchSprite.setPosition(m_turtle.position);
                branchSprite.setOrigin(sf::Vector2f(m_turtle.width / 2, m_turtle.length));
                branchSprite.setRotation(m_turtle.angle - 90);

                m_canvas.draw(branchSprite);

                // Update the turtle position
                float angleInRadians = (m_turtle.angle - 90) * 3.14159 / 180.0;
                float offsetX = std::sin(angleInRadians) * m_turtle.length;
                float offsetY = std::cos(angleInRadians) * m_turtle.length;
                m_turtle.position += sf::Vector2f(offsetX, offsetY);
            }
            break;

            case Leaf:
                leafSprite.setPosition(m_turtle.position);
                leafSprite.setRotation(m_turtle.angle);
                m_canvas.draw(leafSprite);
                break;

            case Flower:
                flowerSprite.setPosition(m_turtle.position);
                flowerSprite.setRotation(m_turtle.angle);
                m_canvas.draw(flowerSprite);
                break;

            default:
                break;
            }
        }
    }

    sf::Sprite TreeGenerator::getSprite()
    {
        m_canvas.display();
        sf::Sprite sprite(m_canvas.getTexture());
        sprite.setOrigin(m_params.origin);
        return sprite;
    }

}