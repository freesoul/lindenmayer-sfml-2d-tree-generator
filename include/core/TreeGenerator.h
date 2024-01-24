#pragma once

#include "../data/TreeParams.h"
#include "../data/TreeRules.h"
#include "../data/TreeTurtle.h"
#include <SFML/Graphics.hpp>
#include <stack>
#include <unordered_map>
#include <vector>

namespace Tree {
class TreeGenerator {

public:
    TreeGenerator();

    void setParams(TreeParams& params);

    void generateTree(std::vector<Operation>& Operation);

    sf::Sprite getSprite();

private:
    RuleMap rules;

    TreeParams m_params;
    std::vector<Operation> m_Operation;
    sf::RenderTexture m_canvas;
    Turtle m_turtle;
    std::stack<Turtle> m_turtleStack;
};
}