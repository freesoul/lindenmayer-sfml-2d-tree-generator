#pragma once

#include "../data/TreeParams.h"
#include "../data/TreeRules.h"
#include "../data/TreeTurtle.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include <stack>
#include <unordered_map>
#include <vector>
#include <random>

namespace Tree {
class TreeGenerator {

public:
    TreeGenerator();

    void setParams(TreeParams& params);

    void generateTree(std::vector<Operation>& operations);

    sf::Sprite getSprite();

private:
    std::optional<TreeParams::LeafOrFlowerData> getRandomTexture(std::vector<TreeParams::LeafOrFlowerData>& textures);

    RuleMap rules;

    TreeParams m_params;
    std::vector<Operation> m_Operation;
    sf::RenderTexture m_canvas;
    Turtle m_turtle;
    std::stack<Turtle> m_turtleStack;

    std::random_device rd;
    std::mt19937 gen;
};
}