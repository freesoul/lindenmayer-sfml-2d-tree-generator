#include <SFML/Graphics.hpp>
#include <TreeParams.h>
#include <TreeOperations.h>
#include <TreeTurtle.h>
#include <stack>
#include <vector>
#include <unordered_map>

namespace Tree
{
    struct RuleWithProbability
    {
        std::vector<Operations> operations;
        double probability;
    };

    class TreeGenerator
    {

    public:
        TreeGenerator();

        void setParams(TreeParams &params);

        std::vector<Operations> generateRules(unsigned int numIterations);

        void generateTree(std::vector<Operations> &operations);

        sf::Sprite getSprite();

    private:
        std::vector<Operations> TreeGenerator::amplifyRules(const std::vector<Operations> &system);
        std::vector<Operations> chooseOperations(const std::vector<RuleWithProbability> &outcomes);

        std::unordered_map<Operations, std::vector<RuleWithProbability>> rules;

        TreeParams m_params;
        std::vector<Operations> m_operations;
        sf::RenderTexture m_canvas;
        Turtle m_turtle;
        std::stack<Turtle> m_turtleStack;
    };
}