#pragma once

#include <stack>
#include <vector>
#include <unordered_map>
#include "../data/TreeParams.h"
#include "../data/TreeTurtle.h"
#include "../data/TreeRules.h"
#include <SFML/Graphics.hpp>

namespace Tree
{
    class TreeGenerator
    {

    public:
        TreeGenerator();

        void setParams(TreeParams &params);

        std::vector<OperationOrRule> generateRules(const std::vector<OperationOrRule> &axiom, unsigned int numIterations);

        std::vector<Operation> cleanNOOPs(const std::vector<OperationOrRule> &axiom);

        void generateTree(std::vector<Operation> &Operation);

        sf::Sprite getSprite();

    private:
        std::vector<OperationOrRule> TreeGenerator::amplifyRules(const std::vector<OperationOrRule> &system);
        std::vector<Operation> chooseOperation(const std::vector<RuleDefinition> &outcomes);

        RuleMap rules;

        TreeParams m_params;
        std::vector<Operation> m_Operation;
        sf::RenderTexture m_canvas;
        Turtle m_turtle;
        std::stack<Turtle> m_turtleStack;
    };
}